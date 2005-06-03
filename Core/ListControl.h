/* ListControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ListControlH
#define ListControlH

namespace asi
{

/******************************************************************************/

class ListControl : public Control
{
protected:
	bool fShowHeader;			// boolean stating whether to show header
	int fHeaderHeight;			// height of header area (entire width of control)
	bool fShowMoreIcons;		// boolean stating whether to show 'more' icons
	int fMoreIconHeight;		// height of more icons, at bottom (entire width of control)
	int fMoreIconWidth;			// width of more icons
	int fMoreIconPad;			// pad around inner icon from border
	int fItemTopPadHeight;		// height above each item (entire width of control)
	int fItemBottomPadHeight;	// height below each item (entire width of control)

	int fTopItem;				// first visible item, 0 if no items
	int fBottomItem;			// last visible item, -1 if no items
	int fFocusedItem;			// focused item, -1 if no focused item
	bool fFocusedUpIcon;		// true if the more up icon is focued
	bool fFocusedDownIcon;		// true if the more down icon is focued
	 
protected:
	ListControl(const ControlID& controlID,const ScreenID& screenID);
	virtual ~ListControl() {}

private:
	ListControl(const ListControl&);						// don't allow copy constructor
	const ListControl& operator=(const ListControl&);		// or operator=

protected:
	void recalcTopItemFromBottomItem();
	void recalcBottomItemFromTopItem();
public:
	virtual void setFocus(bool set);
	virtual void setFocusedItem(int focusedItem);
	virtual int getFocusedItem() const { return fFocusedItem; }
	virtual void draw(bool showFocus);
protected:
	virtual int calcHeaderHeight() const { return (fShowHeader ? fHeaderHeight : 0); }
	virtual void drawHeader(bool /*showFocus*/) const {}
	virtual int calcMoreIconHeight() const { return (fShowMoreIcons ? fMoreIconHeight : 0); }
	virtual Rect calcUpMoreIconRect() const;
	virtual bool hilightUpMoreIcon() const { return (fTopItem > 0); }
	virtual Rect calcDownMoreIconRect() const;
	virtual bool hilightDownMoreIcon() const { return (fBottomItem < getItemCount() - 1); }
	virtual void drawMoreIcons(bool showFocus) const;
	virtual void drawItems(bool showFocus);

	virtual int getItemCount() const = 0;
	virtual int getItemHeight(int /*item*/) const { return 36; }
	virtual void drawItem(int item) const = 0;
public:
	virtual bool key(int key);
	virtual bool mouseClick(bool leftbutton, bool buttonDown, int x, int y);
	virtual void mouseMove(bool buttonDown, int x, int y);
};

/******************************************************************************/

}; //namespace asi

#endif	//ListControlH
/******************************************************************************/
/******************************************************************************/
