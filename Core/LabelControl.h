/* LabelControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef LabelControlH
#define LabelControlH

namespace asi
{

/******************************************************************************/

class LabelControl : public Control
{
protected:
	CStr256 fText;				// text displayed
	FontPtr fFontPtr;			// font for text

	HorzAlign fHorzAlign;
	VertAlign fVertAlign;

protected:
	LabelControl(const ControlID& controlID, const ScreenID& screenID, const char* text);
	virtual ~LabelControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect, const char* text);

	void setText(const char* text) { fText.copy(text); }
	const char* getText() const { return fText.c_str(); }

	void setFontID(const FontID& fontID);
	const FontID& getFontID() const { return fFontPtr->getFontID(); }

	void setHorzAlign(const HorzAlign horzAlign) { fHorzAlign = horzAlign; }
	HorzAlign getHorzAlign() const { return fHorzAlign; }

	void setVertAlign(const VertAlign vertAlign) { fVertAlign = vertAlign; }
	VertAlign getVertAlign() const { return fVertAlign; }

	virtual bool canFocus() const { return false; }
	virtual void draw(bool showFocus);

	friend class RefCountPtr<LabelControl>;
};

class LabelControlPtr : public RefCountPtr<LabelControl>
{
public:
	LabelControlPtr(ControlPtr controlPtr = ControlPtr()) : 
		RefCountPtr<LabelControl>(controlPtr.isNull() ? NULL :
		&dynamic_cast<LabelControl&>(*controlPtr)) {}

	operator ControlPtr() { return(ControlPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//LabelControlH
/******************************************************************************/
/******************************************************************************/
