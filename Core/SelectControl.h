/* SelectControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SelectControlH
#define SelectControlH

namespace asi
{

/******************************************************************************/

class SelectControl : public Control
{
protected:
	int fHorzPadWidth;
	int fChangeIconWidth;		// total with of icon area, including pad
	int fChangeIconPadWidth;
	int fChangeIconPadHeight;
	int fMoreIconHeight;		// height of more icons
	int fMoreIconWidth;			// width of more icons
	int fMoreIconPad;			// pad around inner icon from border

	CStrVarVector fItemVector;
	int fCurItem;
	bool fFocusedUpIcon;		// true if the more up icon is focued
	bool fFocusedDownIcon;		// true if the more down icon is focued

protected:
	SelectControl(const ControlID& controlID, const ScreenID& screenID);
	virtual ~SelectControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect)
		{ return Control::newInstance(new SelectControl(controlID, screenID), rect); }

	CStrVarVector& getItemVector() { return fItemVector; }

	void setCurItem(int curItem);
	int getCurItem() const { return fCurItem; }

	virtual void draw(bool showFocus);
protected:
	virtual Rect calcUpMoreIconRect() const;
	virtual bool hilightUpMoreIcon() const { return (fCurItem > 0); }
	virtual Rect calcDownMoreIconRect() const;
	virtual bool hilightDownMoreIcon() const { return (fCurItem < (int)fItemVector.size() - 1); }
	virtual void drawChangeIcons(bool showFocus) const;
public:
	virtual bool key(int key);
	virtual bool mouseClick(bool leftbutton, bool buttonDown, int x, int y);
	virtual void mouseMove(bool buttonDown, int x, int y);

	friend RefCountPtr<SelectControl>;
};

class SelectControlPtr : public RefCountPtr<SelectControl>
{
public:
	SelectControlPtr(ControlPtr controlPtr = ControlPtr()) : 
		RefCountPtr<SelectControl>(controlPtr.isNull() ? NULL :
		&dynamic_cast<SelectControl&>(*controlPtr)) {}

	operator ControlPtr() { return(ControlPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//SelectControlH
/******************************************************************************/
/******************************************************************************/
