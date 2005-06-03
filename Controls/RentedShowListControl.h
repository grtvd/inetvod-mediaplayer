/* RentedShowListControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RentedShowListControlH
#define RentedShowListControlH

#include "RentedShowSearch.h"

namespace asi
{

/******************************************************************************/

class RentedShowListControl : public ListControl
{
protected:
	RentedShowSearchVector fRentedShowSearchVector;

	RentedShowListControl(const ControlID& controlID, const ScreenID& screenID)
		: ListControl(controlID, screenID) {}
	virtual ~RentedShowListControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect)
		{ return ListControl::newInstance(new RentedShowListControl(controlID, screenID), rect); }

	void setRentedShowSearchVector(const RentedShowSearchVector& rentedShowSearchVector);

	RentedShowSearchPtr getFocusedItemValue() const;

protected:
	virtual void drawHeader(bool showFocus) const;
	virtual int getItemCount() const;
	//virtual int getItemHeight(int item) const;
	virtual void drawItem(int item) const;

	friend class RefCountPtr<RentedShowListControl>;
};

class RentedShowListControlPtr : public RefCountPtr<RentedShowListControl>
{
public:
	RentedShowListControlPtr(ControlPtr controlPtr = ControlPtr()) : 
		RefCountPtr<RentedShowListControl>(controlPtr.isNull() ? NULL :
		&dynamic_cast<RentedShowListControl&>(*controlPtr)) {}

	operator ControlPtr() { return(ControlPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//RentedShowListControlH
/******************************************************************************/
/******************************************************************************/
