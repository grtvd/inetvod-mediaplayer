/* RentedShowSearch.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RentedShowSearchH
#define RentedShowSearchH

#include "DataID.h"
#include "Object.h"
#include "ShowCost.h"
#include "ShowProvider.h"

namespace asi
{

/******************************************************************************/

class RentedShowSearch : public Streamable
{
protected:
	RentedShowID fRentedShowID;

	ShowID fShowID;
	ProviderID fProviderID;
	CStr128 fName;
	CStr64 fEpisodeName;
	CStrVar fPictureURL;

	TDateTime fAvailableUntil;

protected:
	RentedShowSearch() {}
	virtual ~RentedShowSearch() {}

private:
	RentedShowSearch(const RentedShowSearch&);						// don't allow copy constructor
	const RentedShowSearch& operator=(const RentedShowSearch&);		// or operator=

public:
	// Construction Methods
	static ObjectPtr newInstance();

	virtual const char* className() const { return "RentedShowSearch"; }

	virtual void clear() { Object::clear(); fShowID.clear(); fName.clear(); }	//TODO:

	// Data Get Methods
	const RentedShowID& getRentedShowID() const { return(fRentedShowID); }

	const ShowID& getShowID() const { return(fShowID); }
	const ProviderID& getProviderID() const { return(fProviderID); }
	const char* getName() const { return fName.c_str(); }
	const char* getEpisodeName() const { return fEpisodeName.c_str(); }

	TDateTime getAvailableUntil() const { return fAvailableUntil; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<RentedShowSearch>;
};

class RentedShowSearchPtr : public RefCountPtr<RentedShowSearch>
{
public:
	RentedShowSearchPtr(ObjectPtr objectPtr = ObjectPtr()) : 
		RefCountPtr<RentedShowSearch>(objectPtr.isNull() ? NULL :
		&dynamic_cast<RentedShowSearch&>(*objectPtr)) {}

	operator ObjectPtr() { return(ObjectPtr(fT)); }
};

/******************************************************************************/

class RentedShowSearchVector : public std::vector<RentedShowSearchPtr>
{
public:
	void copy(const RentedShowSearchVector& showSearchVector)
		{ clear(); insert(end(), showSearchVector.begin(), showSearchVector.end()); }

	RentedShowSearchPtr findByID(const RentedShowID& rentedShowID) const;
	RentedShowSearchPtr getByID(const RentedShowID& rentedShowID) const;
	void removeByID(const RentedShowID& rentedShowID);

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;

protected:
	struct findIDCompare
	{
	protected:
		RentedShowID fRentedShowID;

	public:
		findIDCompare(const RentedShowID& rentedShowID) { fRentedShowID = rentedShowID; }
		bool operator() (const RentedShowSearchPtr& lhs) const
			{ return(lhs->getRentedShowID() == fRentedShowID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//RentedShowSearchH
/******************************************************************************/
/******************************************************************************/
