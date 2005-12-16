/* ShowCost.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ShowCostH
#define ShowCostH

#include "DataID.h"
#include "Object.h"

namespace asi
{

/******************************************************************************/

enum ShowCostType
{
	sct_Free,
	sct_Subscription,
	sct_PayPerView
};

CStr32 ConvertShowCostTypeToString(ShowCostType sct);
ShowCostType ConvertStringToShowCostType(const char* sct);

/******************************************************************************/

class ShowCost : public Streamable
{
protected:
	ShowCostType fShowCostType;
	MoneyPtr fCostPtr;
	CStr32 fCostDisplay;
	TInt16 fRentalWindowDays;
	TInt16 fRentalPeriodHours;

protected:
	ShowCost(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~ShowCost() {}

private:
	ShowCost(const ShowCost&);						// don't allow copy constructor
	const ShowCost& operator=(const ShowCost&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new ShowCost(filerPtr)); }

	virtual const char* className() const { return "ShowCost"; }

	virtual void clear() { Object::clear(); fShowCostType = sct_Free; fCostPtr = MoneyPtr(); fCostDisplay.clear(); }

	// Data Get/Set Methods
	ShowCostType getShowCostType() const { return fShowCostType; }
	MoneyPtr getCost() const { return fCostPtr; }
	const char* getCostDisplay();
	TInt16 getRentalWindowDays() const { return fRentalWindowDays; }
	TInt16 getRentalPeriodHours() const { return fRentalPeriodHours; }

	CStr64 formatRental();

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ShowCost>;
};

class ShowCostPtr : public RefCountPtr<ShowCost>
{
public:
	ShowCostPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ShowCost>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ShowCost&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ShowCostConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return ShowCost::newInstance(filerPtr); }
};

/******************************************************************************/

class ShowCostVector : public std::vector<ShowCostPtr>
{
public:
	void copy(const ShowCostVector& showCostVector)
		{ clear(); insert(end(), showCostVector.begin(), showCostVector.end()); }

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;
};

/******************************************************************************/

}; //namespace asi

#endif	//ShowCostH
/******************************************************************************/
/******************************************************************************/
