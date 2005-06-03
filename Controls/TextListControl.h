/* TextListControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TextListControlH
#define TextListControlH

namespace asi
{

/******************************************************************************/

class TextListControl : public ListControl
{
protected:
	NameValuePairVector fItemVector;
	int fHorzPadWidth;

	TextListControl(const ControlID& controlID,const ScreenID& screenID);
	virtual ~TextListControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID,const ScreenID& screenID,
		const Rect& rect)
		{ return ListControl::newInstance(new TextListControl(controlID,screenID),rect); }

	const NameValuePairVector& getItemVector() const { return fItemVector; }
	NameValuePairVector& getItemVector() { return fItemVector; }

	void setHorzPadWidth(const int horzPadWidth) { fHorzPadWidth = horzPadWidth; }
	int getHorzPadWidth() const { return fHorzPadWidth; }

	void setFocusedItemByName(const char* name) { setFocusedItem(fItemVector.findPosByName(name)); }
	CStr64 getFocusedItemName() const;
	CStrVar getFocusedItemValue() const;

protected:
	virtual int getItemCount() const { return fItemVector.size(); }
	virtual void drawItem(int item) const;

	friend class RefCountPtr<TextListControl>;
};

class TextListControlPtr : public RefCountPtr<TextListControl>
{
public:
	TextListControlPtr(ControlPtr controlPtr = ControlPtr()) : 
		RefCountPtr<TextListControl>(controlPtr.isNull() ? NULL :
		&dynamic_cast<TextListControl&>(*controlPtr)) {}

	operator ControlPtr() { return(ControlPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//TextListControlH
/******************************************************************************/
/******************************************************************************/
