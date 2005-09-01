/* RentedShow.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RentedShowH
#define RentedShowH

#include "DataID.h"

namespace asi
{

/******************************************************************************/

class RentedShow : public Streamable
{
protected:
	RentedShowID fRentedShowID;

	ShowID fShowID;
	ProviderID fProviderID;
	CStr128 fName;
	CStr128 fEpisodeName;
	CStr32 fEpisodeNumber;

	TDate fReleasedOn;
	TInt16 fReleasedYear;
	CStrVar fDescription;
	TInt16 fRunningMins;
	CStrVar fPictureURL;

	CategoryIDVector fCategoryIDVector;
	RatingID fRatingID;
	bool fIsAdult;

	ShowCostPtr fShowCostPtr;
	TDateTime fRentedOn;
	TDateTime fAvailableUntil;

protected:
	RentedShow(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~RentedShow() {}

private:
	RentedShow(const RentedShow&);						// don't allow copy constructor
	const RentedShow& operator=(const RentedShow&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new RentedShow(filerPtr)); }

	virtual const char* className() const { return "RentedShow"; }

	// Data Get/Set Methods
	const RentedShowID& getRentedShowID() const { return(fRentedShowID); }

	const ShowID& getShowID() const { return(fShowID); }
	const ProviderID& getProviderID() const { return(fProviderID); }
	const char* getName() const { return fName.c_str(); }
	const char* getEpisodeName() const { return fEpisodeName.c_str(); }
	const char* getEpisodeNumber() const { return fEpisodeNumber.c_str(); }

	TDate getReleasedOn() const { return fReleasedOn; }
	TInt16 getReleasedYear() const { return fReleasedYear; }
	const char* getDescription() const { return fDescription.c_str(); }
	TInt16 getRunningMins() const { return fRunningMins; }
	const char* getPictureURL() const { return fPictureURL.c_str(); }

	void getCategoryIDVector(CategoryIDVector& categoryIDVector) const
		{ categoryIDVector.copy(fCategoryIDVector); }
	const RatingID& getRatingID() const { return fRatingID; }
	bool getIsAdult() const { return fIsAdult; }
	ShowCostPtr getShowCost() const { return fShowCostPtr; }
	TDateTime getRentedOn() const { return fRentedOn; }
	TDateTime getAvailableUntil() const { return fAvailableUntil; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<RentedShow>;
};

class RentedShowPtr : public RefCountPtr<RentedShow>
{
public:
	RentedShowPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<RentedShow>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<RentedShow&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class RentedShowConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return RentedShow::newInstance(filerPtr); }
};

/******************************************************************************/

}; //namespace asi

#endif	//RentedShowH
/******************************************************************************/
/******************************************************************************/
