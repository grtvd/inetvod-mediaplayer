/* TextControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TextControlH
#define TextControlH

namespace asi
{

/******************************************************************************/
//#define USE_SCROLL_BAR

class TextControl : public Control
{
protected:
	CStrVar fText;				// text displayed
	FontPtr fFontPtr;			// font for text

	bool fScrollable;			// if text exceeds viewable area, should text be scrollable
#if defined(USE_SCROLL_BAR)
	bool fShowScrollBar;		// boolean stating whether to show scroll bar
	int fScrollBarWidth;		// width of scroll bar (entire height of control)
#else
	bool fShowMoreIcons;		// boolean stating whether to show 'more' icons
	int fMoreIconHeight;		// height of more icons, at top and bottom (entire width of control)
#endif
	int fLineSpaceHeight;		// about of space between each line

	int fLineHeight;			// calculated line height from Font and fLineSpaceHeight
	vector<int> fLinesVector;	// calculated char starts for each line
	int fTopLine;				// first visible line
	int fVisibleLines;			// number of visible lines
	 
protected:
	TextControl(const ControlID& controlID, const ScreenID& screenID, const char* text);
	virtual ~TextControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect, const char* text);

protected:
	void init();

public:
	void setText(const char* text);

	void setFontID(const FontID& fontID);
	const FontID& getFontID() const { return fFontPtr->getFontID(); }

	void setVisibleLines(int visibleLines);

//	void setShowMoreIcons(bool showMoreIcons) { fShowMoreIcons = showMoreIcons; }
//	bool getShowMoreIcons() const { return fShowMoreIcons; }

#if defined(USE_SCROLL_BAR)
	virtual bool canFocus() const { return fShowScrollBar; }
#else
	virtual bool canFocus() const { return fShowMoreIcons; }
#endif
	virtual void draw(bool showFocus);
protected:
#if defined(USE_SCROLL_BAR)
	virtual void drawScrollBar(bool showFocus) const;
#else
	virtual void drawMoreIcons(bool showFocus) const;
#endif
	virtual void drawLines();
public:
	virtual bool key(int key);

	friend class RefCountPtr<TextControl>;
};

class TextControlPtr : public RefCountPtr<TextControl>
{
public:
	TextControlPtr(ControlPtr controlPtr = ControlPtr()) : 
		RefCountPtr<TextControl>(controlPtr.isNull() ? NULL :
		&dynamic_cast<TextControl&>(*controlPtr)) {}

	operator ControlPtr() { return(ControlPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//TextControlH
/******************************************************************************/
/******************************************************************************/
