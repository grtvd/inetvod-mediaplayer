/* Draw.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

//#define DRAW_TEXT_OUTLINE

/******************************************************************************/

int fFontCharWidth = 14;
int fFontCharHeight = 24;
int fFontCharBaseLine = 17;

// generic colors (RGBA)
GLubyte gBlackColor[4] = { 0, 0, 0, 255 };
GLubyte gWhiteColor[4] = { 255, 255, 255, 255 };
GLubyte gRedColor[4] = { 255, 0, 0, 255 };
GLubyte gGreenColor[4] = { 0, 255, 0, 255 };
GLubyte gBlueColor[4] = { 0, 0, 255, 255 };
GLubyte gOrangeColor[4] = { 255, 128, 0, 255 };
GLubyte gYellowColor[4] = { 255, 255, 0, 255 };
GLubyte gGrayColor[4] = { 128, 128, 128, 255 };
GLubyte gLightGrayColor[4] = { 192, 192, 192, 255 };

// application colors (RGBA)
GLubyte gBackgroundColor[4] = { 16, 114, 196, 255 };
GLubyte gBackgroundTextColor[4] = { 91, 138, 208, 255 };
#if defined(TITLE_ONE)
GLubyte gScreenBackgroundSolidColor[4] = { 22, 91, 166, 255 };
GLubyte gScreenBackgroundTransColor[4] = { 28, 69, 137, 128 };
#elif defined(TITLE_TWO)
GLubyte gScreenBackgroundSolidColor[4] = { 22, 91, 166, 255 };
GLubyte gScreenBackgroundTransColor[4] = { 16, 114, 196, 128 };
#else
	#error Opps
#endif

GLubyte gUnfocusedBackgroundColor[4] = { 22, 91, 166, 255 };
GLubyte gUnfocusedBorderColor[4] = { 91, 138, 208, 255 };
GLubyte gFocusedBackgroundColor[4] = { 0, 128, 0, 255 };
GLubyte gFocusedBorderColor[4] = { 255, 255, 64, 255 };

Point fDrawCoordOffset;	//TODO: REMOVE
double fDrawCoordOffsetHorz = 0.0;
double fDrawCoordOffsetVert = 0.0;

double fDrawHorzScale = 1.0;	//(ortho_left - ortho_right) / (draw_left - draw_right)
double fDrawVertScale = 1.0;	//(ortho_top - ortho_bottom) / (draw_top - draw_bottom)

/******************************************************************************/
/******************************************************************************/

inline double CalcOrthoHorz(double drawHorz) { return (drawHorz + fDrawCoordOffsetHorz) * fDrawHorzScale; }
inline double CalcOrthoVert(double drawVert) { return (drawVert + fDrawCoordOffsetVert) * fDrawVertScale; }

/******************************************************************************/
/******************************************************************************/

void SetDrawCoord(Rect drawCoord, Rect orthoCoord)
{
	fDrawCoordOffset.h = 0;
	fDrawCoordOffset.v = 0;
	fDrawCoordOffsetHorz = 0;
	fDrawCoordOffsetVert = 0;

	fDrawHorzScale = ((double)orthoCoord.left - (double)orthoCoord.right) / ((double)drawCoord.left - (double)drawCoord.right);
	fDrawVertScale = ((double)orthoCoord.top - (double)orthoCoord.bottom) / ((double)drawCoord.top - (double)drawCoord.bottom);
}

/******************************************************************************/

void AdjustDrawCoordOffset(int dh, int dv)
{
	fDrawCoordOffset.offset(dh, dv);
	fDrawCoordOffsetHorz = fDrawCoordOffset.h;
	fDrawCoordOffsetVert = fDrawCoordOffset.v;
}

/******************************************************************************/

void GetDrawCoordOffset(int& h, int& v)
{
	h = fDrawCoordOffset.h;
	v = fDrawCoordOffset.v;
}

/******************************************************************************/

void SetDrawCoordOffset(int h, int v)
{
	fDrawCoordOffset.h = h;
	fDrawCoordOffset.v = v;
	fDrawCoordOffsetHorz = fDrawCoordOffset.h;
	fDrawCoordOffsetVert = fDrawCoordOffset.v;
}

/******************************************************************************/

void DrawText(int x, int y, const char* string, const FontPtr& fontPtr)
{
	double h = CalcOrthoHorz(x);
	double v = CalcOrthoVert(y);

	fontPtr->render(string, h, v);
}

/******************************************************************************/

void DrawTextAligned(const Rect& rect,HorzAlign horzAlign,VertAlign vertAlign,
	const char* string,const FontID& fontID)
{
	DrawTextAligned(rect,horzAlign,vertAlign,string,MainApp::getThe()->getFont(fontID));
}

/******************************************************************************/

void DrawTextAligned(const Rect& rect,HorzAlign horzAlign,VertAlign vertAlign,
	const char* text,const FontPtr& fontPtr)
{
	float rectWidth = rect.getWidth();
	CStrVar tempText;
	const char* drawText;
	int x;
	int y;

	if (fontPtr->getWidth(text) > rectWidth)
	{
		float textWidth = fontPtr->getWidth("...");
		int i;
		int len = STRLEN(text);

		for(i = 0; i < len; ++i)
		{
			//textWidth += fontPtr->getWidth(text[i]);
			//if (textWidth > rectWidth)
			tempText.concat(text[i]);
			if(fontPtr->getWidth(tempText.c_str()) + textWidth > rectWidth)
				break;
		}

		if (i > 0)
			tempText.ncopy(text, i);
		tempText.concat("...");

		drawText = tempText.c_str();
	}
	else
		drawText = text;

	if(horzAlign == ha_Left)
		x = rect.left;
	else
	{
		int textWidth = fontPtr->getWidth(drawText);

		if(horzAlign == ha_Right)
			x = rect.right - textWidth;
		else
			x = rect.left + (rectWidth / 2) - (textWidth / 2);
	}

	if(vertAlign == va_Top)
		y = rect.top + fontPtr->getCharBaseLine();
	else if(vertAlign == va_Bottom)
		y = rect.top + rect.getHeight() - fontPtr->getCharHeight() + fontPtr->getCharBaseLine();
	else
		y = rect.top + ((rect.getHeight() - fontPtr->getCharHeight()) / 2) + fontPtr->getCharBaseLine();

	DrawText(x, y, drawText, fontPtr);
	#if defined(DRAW_TEXT_OUTLINE)
	DrawBorder2(rect, 1, gWhiteColor);
	#endif
}

/******************************************************************************/

void DrawRect(int drawLeft, int drawTop, int drawRight, int drawBottom, const GLubyte* color)
{
	double left = CalcOrthoHorz(drawLeft);
	double top = CalcOrthoVert(drawTop);
	double right = CalcOrthoHorz(drawRight);
	double bottom = CalcOrthoVert(drawBottom);

	//left += fDrawCoordOffset.h;
	//top += fDrawCoordOffset.v;
	//right += fDrawCoordOffset.h;
	//bottom += fDrawCoordOffset.v;

	glColor4ubv(color);
	glBegin(GL_POLYGON);
	//glVertex2f(left, top);
	//glVertex2f(right, top);
	//glVertex2f(right, bottom);
	//glVertex2f(left, bottom);
	glVertex2d(left, top);
	glVertex2d(right, top);
	glVertex2d(right, bottom);
	glVertex2d(left, bottom);
	glEnd();
}

/******************************************************************************/

void DrawRect(const Rect& rect, const GLubyte* color)
{
	DrawRect(rect.left, rect.top, rect.right, rect.bottom, color);
}

/******************************************************************************/

void DrawRectDithered(int drawLeft, int drawTop, int drawRight, int drawBottom,
	const GLubyte* topColor, const GLubyte* bottomColor, DitherDirection dd)
{
	//left += fDrawCoordOffset.h;
	//top += fDrawCoordOffset.v;
	//right += fDrawCoordOffset.h;
	//bottom += fDrawCoordOffset.v;
	double left = CalcOrthoHorz(drawLeft);
	double top = CalcOrthoVert(drawTop);
	double right = CalcOrthoHorz(drawRight);
	double bottom = CalcOrthoVert(drawBottom);

	glBegin(GL_POLYGON);
	if(dd == dd_Left2Right)
	{
		glColor4ubv(topColor);
		glVertex2d(left, top);
		glColor4ubv(bottomColor);
		glVertex2d(right, top);
		glColor4ubv(bottomColor);
		glVertex2d(right, bottom);
		glColor4ubv(topColor);
		glVertex2d(left, bottom);
	}
	else if(dd == dd_Right2Left)
	{
		glColor4ubv(bottomColor);
		glVertex2d(left, top);
		glColor4ubv(topColor);
		glVertex2d(right, top);
		glColor4ubv(topColor);
		glVertex2d(right, bottom);
		glColor4ubv(bottomColor);
		glVertex2d(left, bottom);
	}
	else if(dd == dd_Top2Bottom)
	{
		glColor4ubv(topColor);
		glVertex2d(left, top);
		glVertex2d(right, top);
		glColor4ubv(bottomColor);
		glVertex2d(right, bottom);
		glVertex2d(left, bottom);
	}
	else if(dd == dd_Bottom2Top)
	{
		glColor4ubv(bottomColor);
		glVertex2d(left, top);
		glVertex2d(right, top);
		glColor4ubv(topColor);
		glVertex2d(right, bottom);
		glVertex2d(left, bottom);
	}
	glEnd();
}

/******************************************************************************/

void DrawRectDithered(const Rect& rect, const GLubyte* topColor, const GLubyte* bottomColor,
	DitherDirection dd)
{
	DrawRectDithered(rect.left, rect.top, rect.right, rect.bottom, topColor, bottomColor, dd);
}

/******************************************************************************/

void DrawBorder(int left, int top, int width, int height, int thick, int corner, GLubyte* color)
{
	int right = left + width;
	int bottom = top + height;

	//left += fDrawCoordOffset.h;
	//top += fDrawCoordOffset.v;
	//right += fDrawCoordOffset.h;
	//bottom += fDrawCoordOffset.v;

	glColor4ubv(color);

	//top
	glBegin(GL_POLYGON);
	glVertex2d(CalcOrthoHorz(left + thick - corner), CalcOrthoVert(top));
	glVertex2d(CalcOrthoHorz(right - thick + corner), CalcOrthoVert(top));
	glVertex2d(CalcOrthoHorz(right), CalcOrthoVert(top + thick - corner));
	glVertex2d(CalcOrthoHorz(right), CalcOrthoVert(top + thick));
	glVertex2d(CalcOrthoHorz(left), CalcOrthoVert(top + thick));
	glVertex2d(CalcOrthoHorz(left), CalcOrthoVert(top + thick - corner));
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glVertex2d(CalcOrthoHorz(left), CalcOrthoVert(top + thick));
	glVertex2d(CalcOrthoHorz(left + thick), CalcOrthoVert(top + thick));
	glVertex2d(CalcOrthoHorz(left + thick), CalcOrthoVert(bottom - thick));
	glVertex2d(CalcOrthoHorz(left), CalcOrthoVert(bottom - thick));
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glVertex2d(CalcOrthoHorz(right - thick), CalcOrthoVert(top + thick));
	glVertex2d(CalcOrthoHorz(right), CalcOrthoVert(top + thick));
	glVertex2d(CalcOrthoHorz(right), CalcOrthoVert(bottom - thick));
	glVertex2d(CalcOrthoHorz(right - thick), CalcOrthoVert(bottom - thick));
	glEnd();

	//bottom
	glBegin(GL_POLYGON);
	glVertex2d(CalcOrthoHorz(left), CalcOrthoVert(bottom - thick));
	glVertex2d(CalcOrthoHorz(right), CalcOrthoVert(bottom - thick));
	glVertex2d(CalcOrthoHorz(right), CalcOrthoVert(bottom - thick + corner));
	glVertex2d(CalcOrthoHorz(right - thick + corner), CalcOrthoVert(bottom));
	glVertex2d(CalcOrthoHorz(left + thick - corner), CalcOrthoVert(bottom));
	glVertex2d(CalcOrthoHorz(left), CalcOrthoVert(bottom - thick + corner));
	glEnd();
}

/******************************************************************************/

void DrawBorder(int left, int top, int width, int height, int thick, GLubyte* color)
{
	int corner = (int)((float)thick / 2.0);
	DrawBorder(left, top, width, height, thick, corner, color);
}

/******************************************************************************/

void DrawBorder2(const Rect& rect, int thick, GLubyte* color)
{
	DrawBorder(rect.left, rect.top, rect.getWidth(), rect.getHeight(), thick, 1, color);
}

/******************************************************************************/

void DrawUpTriangle(const Rect& rect, const GLubyte* color)
{
	double left = CalcOrthoHorz(rect.left);
	double top = CalcOrthoVert(rect.top);
	double right = CalcOrthoHorz(rect.right);
	double bottom = CalcOrthoVert(rect.bottom);
	double horzMid = CalcOrthoHorz(rect.left + (rect.getWidth() / 2));

	//int left = rect.left + fDrawCoordOffset.h;
	//int top = rect.top + fDrawCoordOffset.v;
	//int right = rect.right + fDrawCoordOffset.h;
	//int bottom = rect.bottom + fDrawCoordOffset.v;
	//int horzMid = left + ((right - left) / 2);

	glColor4ubv(color);

	glBegin(GL_POLYGON);
	//glVertex2f(horzMid, top);
	//glVertex2f(right, bottom);
	//glVertex2f(left, bottom);
	glVertex2d(horzMid, top);
	glVertex2d(right, bottom);
	glVertex2d(left, bottom);
	glEnd();
}

/******************************************************************************/

void DrawDownTriangle(const Rect& rect, const GLubyte* color)
{
	double left = CalcOrthoHorz(rect.left);
	double top = CalcOrthoVert(rect.top);
	double right = CalcOrthoHorz(rect.right);
	double bottom = CalcOrthoVert(rect.bottom);
	double horzMid = CalcOrthoHorz(rect.left + (rect.getWidth() / 2));

	//int left = rect.left + fDrawCoordOffset.h;
	//int top = rect.top + fDrawCoordOffset.v;
	//int right = rect.right + fDrawCoordOffset.h;
	//int bottom = rect.bottom + fDrawCoordOffset.v;
	//int horzMid = left + ((right - left) / 2);

	glColor4ubv(color);

	glBegin(GL_POLYGON);
	//glVertex2f(left, top);
	//glVertex2f(right, top);
	//glVertex2f(horzMid, bottom);
	glVertex2d(left, top);
	glVertex2d(right, top);
	glVertex2d(horzMid, bottom);
	glEnd();
}

/******************************************************************************/

void DrawLeftTriangle(const Rect& rect, const GLubyte* color)
{
	double left = CalcOrthoHorz(rect.left);
	double top = CalcOrthoVert(rect.top);
	double right = CalcOrthoHorz(rect.right);
	double bottom = CalcOrthoVert(rect.bottom);
	double vertMid = CalcOrthoVert(rect.top + (rect.getHeight() / 2));

	//int left = rect.left + fDrawCoordOffset.h;
	//int top = rect.top + fDrawCoordOffset.v;
	//int right = rect.right + fDrawCoordOffset.h;
	//int bottom = rect.bottom + fDrawCoordOffset.v;
	//int vertMid = top + ((bottom - top) / 2);

	glColor4ubv(color);

	glBegin(GL_POLYGON);
	//glVertex2f(left, vertMid);
	//glVertex2f(right, top);
	//glVertex2f(right, bottom);
	glVertex2d(left, vertMid);
	glVertex2d(right, top);
	glVertex2d(right, bottom);
	glEnd();
}

/******************************************************************************/

void DrawRightTriangle(const Rect& rect, const GLubyte* color)
{
	double left = CalcOrthoHorz(rect.left);
	double top = CalcOrthoVert(rect.top);
	double right = CalcOrthoHorz(rect.right);
	double bottom = CalcOrthoVert(rect.bottom);
	double vertMid = CalcOrthoVert(rect.top + (rect.getHeight() / 2));

	//int left = rect.left + fDrawCoordOffset.h;
	//int top = rect.top + fDrawCoordOffset.v;
	//int right = rect.right + fDrawCoordOffset.h;
	//int bottom = rect.bottom + fDrawCoordOffset.v;
	//int vertMid = top + ((bottom - top) / 2);

	glColor4ubv(color);

	glBegin(GL_POLYGON);
	//glVertex2f(left, top);
	//glVertex2f(right, vertMid);
	//glVertex2f(left, bottom);
	glVertex2d(left, top);
	glVertex2d(right, vertMid);
	glVertex2d(left, bottom);
	glEnd();
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
