/* Draw.h */

/******************************************************************************/
/******************************************************************************/
#ifndef DrawH
#define DrawH

#include <GL/gl.h>
#if defined(USE_GLUT)
#include <glut.h>
#endif

//#define TITLE_ONE
#define TITLE_TWO

namespace asi
{

/******************************************************************************/

// generic colors (RGBA)
extern GLubyte gBlackColor[];
extern GLubyte gWhiteColor[];
extern GLubyte gRedColor[];
extern GLubyte gGreenColor[];
extern GLubyte gBlueColor[];
extern GLubyte gOrangeColor[];
extern GLubyte gYellowColor[];
extern GLubyte gGrayColor[];
extern GLubyte gLightGrayColor[];

// application colors (RGBA)
extern GLubyte gBackgroundColor[];
extern GLubyte gBackgroundTextColor[];
extern GLubyte gScreenBackgroundSolidColor[];
extern GLubyte gScreenBackgroundTransColor[];

extern GLubyte gUnfocusedBackgroundColor[];
extern GLubyte gUnfocusedBorderColor[];
extern GLubyte gFocusedBackgroundColor[];
extern GLubyte gFocusedBorderColor[];

/* Horizontal Alignment */
enum HorzAlign
{
	ha_Left = 0,
	ha_Center = 1,
	ha_Right = 2
};

/* Vertical Alignment */
enum VertAlign
{
	va_Top = 0,
	va_Middle = 1,
	va_Bottom = 2
};

/* Dither Direction */
enum DitherDirection
{
	dd_Left2Right,
	dd_Right2Left,
	dd_Top2Bottom,
	dd_Bottom2Top
};

/******************************************************************************/

void SetDrawCoord(Rect drawCoord, Rect orthoCoord);
void AdjustDrawCoordOffset(int dh, int dv);
void GetDrawCoordOffset(int& dh, int& dv);
void SetDrawCoordOffset(int h, int v);
void DrawText(int x,int y,const char* string,const FontPtr& fontPtr);
void DrawTextAligned(const Rect& rect,HorzAlign horzAlign,VertAlign vertAlign,
	const char* string,const FontID& fontID);
void DrawTextAligned(const Rect& rect,HorzAlign horzAlign,VertAlign vertAlign,
	const char* string,const FontPtr& fontPtr);
void DrawRect(int left, int top, int width, int height, const GLubyte* color);
void DrawRect(const Rect& rect, const GLubyte* color);
void DrawRectDithered(int left, int top, int right, int bottom,
	const GLubyte* topColor, const GLubyte* bottomColor, DitherDirection dd);
void DrawRectDithered(const Rect& rect, const GLubyte* topColor, const GLubyte* bottomColor, DitherDirection dd);
void DrawBorder(int left, int top, int width, int height, int thick, GLubyte* color);
void DrawBorder2(const Rect& rect, int thick, GLubyte* color);
void DrawUpTriangle(const Rect& rect, const GLubyte* color);
void DrawDownTriangle(const Rect& rect, const GLubyte* color);
void DrawLeftTriangle(const Rect& rect, const GLubyte* color);
void DrawRightTriangle(const Rect& rect, const GLubyte* color);

/******************************************************************************/

}; //namespace asi

#endif	//DrawH
/******************************************************************************/
/******************************************************************************/
