/* ShowProviderListControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ShowProviderListControlH
#define ShowProviderListControlH

namespace asi
{

/******************************************************************************/

class ShowProviderListControl : public ListControl
{
protected:
	ShowProviderVector fShowProviderVector;

	ShowProviderListControl(const ControlID& controlID, const ScreenID& screenID)
		: ListControl(controlID, screenID) {}
	virtual ~ShowProviderListControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect)
		{ return ListControl::newInstance(new ShowProviderListControl(controlID, screenID), rect); }

	void setShowProviderVector(const ShowProviderVector& showProviderVector)
		{ fShowProviderVector.copy(showProviderVector); }

	ShowProviderPtr getFocusedItemValue() const;

protected:
	virtual void drawHeader(bool showFocus) const;
	virtual int getItemCount() const;
	//virtual int getItemHeight(int item) const;
	virtual void drawItem(int item) const;

	friend class RefCountPtr<ShowProviderListControl>;
};

class ShowProviderListControlPtr : public RefCountPtr<ShowProviderListControl>
{
public:
	ShowProviderListControlPtr(ControlPtr controlPtr = ControlPtr()) : 
		RefCountPtr<ShowProviderListControl>(controlPtr.isNull() ? NULL :
		&dynamic_cast<ShowProviderListControl&>(*controlPtr)) {}

	operator ControlPtr() { return(ControlPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//ShowProviderListControlH
/******************************************************************************/
/******************************************************************************/
