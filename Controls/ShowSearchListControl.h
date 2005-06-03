/* ShowSearchListControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ShowSearchListControlH
#define ShowSearchListControlH

#include "RentedShow.h"

namespace asi
{

/******************************************************************************/

class ShowSearchListControl : public ListControl
{
protected:
	static const int fItemLine2Height;

	ShowSearchVector fShowSearchVector;

	ShowSearchListControl(const ControlID& controlID, const ScreenID& screenID)
		: ListControl(controlID, screenID) {}
	virtual ~ShowSearchListControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect)
		{ return ListControl::newInstance(new ShowSearchListControl(controlID, screenID), rect); }

	void setShowSearchVector(const ShowSearchVector& showSearchVector)
		{ fShowSearchVector.copy(showSearchVector); }

	ShowSearchPtr getFocusedItemValue() const;

protected:
	virtual void drawHeader(bool showFocus) const;
	virtual int getItemCount() const;
	virtual int getItemHeight(int item) const;
	virtual void drawItem(int item) const;

	friend class RefCountPtr<ShowSearchListControl>;
};

class ShowSearchListControlPtr : public RefCountPtr<ShowSearchListControl>
{
public:
	ShowSearchListControlPtr(ControlPtr controlPtr = ControlPtr()) : 
		RefCountPtr<ShowSearchListControl>(controlPtr.isNull() ? NULL :
		&dynamic_cast<ShowSearchListControl&>(*controlPtr)) {}

	operator ControlPtr() { return(ControlPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//ShowSearchListControlH
/******************************************************************************/
/******************************************************************************/
