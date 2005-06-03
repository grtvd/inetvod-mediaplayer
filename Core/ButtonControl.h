/* ButtonControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ButtonControlH
#define ButtonControlH

namespace asi
{

/******************************************************************************/

class ButtonControl : public Control
{
protected:
	CStr64 fText;
	HorzAlign fHorzAlign;
	VertAlign fVertAlign;
	int fHorzPadWidth;

protected:
	ButtonControl(const ControlID& controlID,const ScreenID& screenID,const char* text);
	virtual ~ButtonControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID,const ScreenID& screenID,
		const Rect& rect,const char* text)
		{ return Control::newInstance(new ButtonControl(controlID,screenID,text),rect); }

	const char* getText() { return fText.c_str(); }
	void setText(const char* text) { fText.copy(text); }

	void setHorzAlign(const HorzAlign horzAlign) { fHorzAlign = horzAlign; }
	HorzAlign getHorzAlign() const { return fHorzAlign; }

	void setVertAlign(const VertAlign vertAlign) { fVertAlign = vertAlign; }
	VertAlign getVertAlign() const { return fVertAlign; }

	void setHorzPadWidth(const int horzPadWidth) { fHorzPadWidth = horzPadWidth; }
	int getHorzPadWidth() const { return fHorzPadWidth; }

	virtual void draw(bool showFocus);
	virtual bool key(int key);
	virtual bool mouseClick(bool leftButton, bool buttonDown, int x, int y);

	friend class RefCountPtr<ButtonControl>;
};

class ButtonControlPtr : public RefCountPtr<ButtonControl>
{
public:
	ButtonControlPtr(ControlPtr controlPtr = ControlPtr()) : 
		RefCountPtr<ButtonControl>(controlPtr.isNull() ? NULL :
		&dynamic_cast<ButtonControl&>(*controlPtr)) {}

	operator ControlPtr() { return(ControlPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//ButtonControlH
/******************************************************************************/
/******************************************************************************/
