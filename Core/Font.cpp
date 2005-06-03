/* Font.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#if defined(USE_GLUT)
#include <glut.h>
#endif

namespace asi
{

/******************************************************************************/
/******************************************************************************/

#if defined(USE_GLUT_FONT)
Font::Font(const FontID& fontID,const void* glutFont,int charHeight,int charBaseLine, GLubyte color[4])
{
	fFontID = fontID;
	fGlutFont = glutFont;
	fAvgCharWidth = 0;
	fMaxCharWidth = 0;
	fCharHeight = charHeight;
	fCharBaseLine = charBaseLine;

	for(int i = 0; i < 4; i++)
		fColor[i] = color[i];
}
#else
Font::Font(const FontID& fontID, const char* fontName, int faceSize, GLubyte color[4])
{
	fFontID = fontID;

	glColor4ubv(color);
	fFTGLFont = new FTGLPixmapFont(fontName);
	fFTGLFont->FaceSize(faceSize);

	char charMap[128];
	for(int c = 1; c <= 127; c++)
		charMap[c - 1] = c;
	charMap[127] = '\0';
	fFTGLFont->Advance(charMap);

	fAvgCharWidth = 0;
	fMaxCharWidth = 0;
	fCharHeight = 0;
	fCharBaseLine = 0;

	for(int i = 0; i < 4; i++)
		fColor[i] = color[i];
}
#endif

/******************************************************************************/

#if defined(USE_GLUT_FONT)
FontPtr Font::newInstance(const FontID& fontID,const void* glutFont,int charHeight,
	int charBaseLine, GLubyte color[4])
{
	FontPtr fontPtr(new Font(fontID, glutFont, charHeight, charBaseLine, color));
	fontPtr->init();

	return fontPtr;
}
#else
FontPtr Font::newInstance(const FontID& fontID, const char* fontName, int faceSize,
	GLubyte color[4])
{
	FontPtr fontPtr(new Font(fontID, fontName, faceSize, color));
	fontPtr->init();

	return fontPtr;
}
#endif

/******************************************************************************/

void Font::init()
{
	fAvgCharWidth = getWidth('X');
	fMaxCharWidth = ceil(getWidth('W'));

#if !defined(USE_GLUT_FONT)
	//fCharHeight = fFTGLFont->Ascender();
	//fCharBaseLine = fCharHeight + fFTGLFont->Descender();	//Descender is negative
	fCharBaseLine = fFTGLFont->Ascender();
	fCharHeight = fCharBaseLine - fFTGLFont->Descender();	//Descender is negative
#endif
}

/******************************************************************************/

float Font::getWidth(const char* str) const
{
#if defined(USE_GLUT_FONT)
	int width = 0;
	int len = STRLEN(str);

	for(int i = 0; i < len; i++)
		width += glutBitmapWidth((void*)fGlutFont, str[i]);

	return width;
#else
	//float llx, lly, llz, urx, ury, urz;

	//fFTGLFont->BBox(str, llx, lly, llz, urx, ury, urz);
	//width = urx - llx;

	return fFTGLFont->Advance(str);
	//TODO:
#endif
}

/******************************************************************************/

float Font::getWidth(const char ch) const
{
#if defined(USE_GLUT_FONT)
	return glutBitmapWidth((void*)fGlutFont, ch);
#else
	char str[2];

	str[0] = ch;
	str[1] = '\0';

	return getWidth(str);
#endif
}

/******************************************************************************/

void Font::render(const char* str, double x, double y) const
{
	glColor4ubv(fColor);
	glRasterPos2d(x, y);
#if defined(USE_GLUT_FONT)
	int len, i;

	len = (int)STRLEN(str);
	for(i = 0; i < len; i++)
	{
		glutBitmapCharacter((void*)fGlutFont, str[i]);
	}
#else
	fFTGLFont->Render(str);
#endif
}

/******************************************************************************/
/******************************************************************************/

FontPtr FontVector::getByID(const FontID& fontID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(fontID));
	if(iter != end())
		return(*iter);

	throw ASIException("FontVector::getByID","Invalid FontID(%s)", fontID.c_str());
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
