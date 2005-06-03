/* Font.h */

/******************************************************************************/
/******************************************************************************/
#ifndef FontH
#define FontH

#if defined(USE_GLUT)
#include <glut.h>
#endif

#if !defined(USE_GLUT_FONT)
#include "FTGLPixmapFont.h"
#endif

namespace asi
{

/******************************************************************************/

class Font;	//forward reference
typedef RefCountPtr<Font> FontPtr;

class Font : public RefCountObject
{
protected:
	FontID fFontID;
	#if defined(USE_GLUT_FONT)
	const void* fGlutFont;
	#else
	FTGLPixmapFont* fFTGLFont;
	int fFaceSize;
	#endif
	int fAvgCharWidth;
	int fMaxCharWidth;
	int fCharHeight;
	int fCharBaseLine;
	GLubyte fColor[4];

protected:
	#if defined(USE_GLUT_FONT)
	Font(const FontID& fontID, const void* glutFont, int charHeight, int charBaseLine,
		GLubyte color[4]);
	virtual ~Font() {}
	#else
	Font(const FontID& fontID, const char* fontName, int faceSize, GLubyte color[4]);
	virtual ~Font() {} //delete fFTGLFont;
	#endif

private:
	Font(const Font&);						// don't allow copy constructor
	const Font& operator=(const Font&);		// or operator=

public:
	#if defined(USE_GLUT_FONT)
	static FontPtr newInstance(const FontID& fontID,const void* glutFont,int charHeight,int charBaseLine, GLubyte color[4]);
	#else
	static FontPtr newInstance(const FontID& fontID, const char* fontName, int faceSize, GLubyte color[4]);
	#endif

protected:
	void init();

public:
	const FontID& getFontID() const { return(fFontID); }
	#if defined(USE_GLUT_FONT)
	const void* getGlutFont() const { return fGlutFont; }
	#endif
	float getWidth(const char* str) const;
	float getWidth(const char ch) const;
	int getAveCharWidth() const { return fAvgCharWidth; }
	int getMaxCharWidth() const { return fMaxCharWidth; }
	int getCharHeight() const { return fCharHeight; }
	int getCharBaseLine() const { return fCharBaseLine; }

	void render(const char* str, double x, double y) const;

	friend class RefCountPtr<Font>;
};

/******************************************************************************/

class FontVector : public std::vector<FontPtr>
{
public:
	FontPtr getByID(const FontID& fontID) const;

protected:
	struct findIDCompare
	{
	protected:
		FontID fFontID;

	public:
		findIDCompare(const FontID& fontID) { fFontID = fontID; }
		bool operator() (const FontPtr& lhs) const
			{ return(lhs->getFontID() == fFontID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//FontH
/******************************************************************************/
/******************************************************************************/
