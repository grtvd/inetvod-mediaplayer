/* ShowDetail.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ShowDetailH
#define ShowDetailH

#include "DataID.h"

namespace asi
{

/******************************************************************************/

class ShowDetail : public Streamable
{
protected:
	ShowID fShowID;
	CStr128 fName;
	CStr64 fEpisodeName;
	CStr32 fEpisodeNumber;

	TDate fReleasedOn;
	TInt16 fReleasedYear;
	CStrVar fDescription;
	TInt16 fRunningMins;
	CStrVar fPictureURL;

	CategoryIDVector fCategoryIDVector;
	RatingID fRatingID;
	bool fIsAdult;
	ShowProviderVector fShowProviderVector;

protected:
	ShowDetail(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~ShowDetail() {}

private:
	ShowDetail(const ShowDetail&);						// don't allow copy constructor
	const ShowDetail& operator=(const ShowDetail&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new ShowDetail(filerPtr)); }

	virtual const char* className() const { return "ShowDetail"; }

	// Data Get/Set Methods
	const ShowID& getShowID() const { return(fShowID); }
	const char* getName() const { return fName.c_str(); }
	const char* getEpisodeName() const { return fEpisodeName.c_str(); }
	const char* getEpisodeNumber() const { return fEpisodeNumber.c_str(); }

	TDate getReleasedOn() const { return fReleasedOn; }
	TInt16 getReleasedYear() const { return fReleasedYear; }
	const char* getDescription() const { return fDescription.c_str(); }
	TInt16 getRunningMins() const { return fRunningMins; }

	void getCategoryIDVector(CategoryIDVector& categoryIDVector) const
		{ categoryIDVector.copy(fCategoryIDVector); }
	const RatingID& getRatingID() const { return fRatingID; }
	bool getIsAdult() const { return fIsAdult; }
	void getShowProviderVector(ShowProviderVector& showProviderVector) const
		{ showProviderVector.copy(fShowProviderVector); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ShowDetail>;
};

class ShowDetailPtr : public RefCountPtr<ShowDetail>
{
public:
	ShowDetailPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ShowDetail>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ShowDetail&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ShowDetailConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return ShowDetail::newInstance(filerPtr); }
};

/******************************************************************************/

class ShowDetailVector : public std::vector<ShowDetailPtr>
{
public:
	ShowDetailPtr findByID(const ShowID& showID) const;
	ShowDetailPtr getByID(const ShowID& showID) const;
	void removeByID(const ShowID& showID);

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;

protected:
	struct findIDCompare
	{
	protected:
		ShowID fShowID;

	public:
		findIDCompare(const ShowID& showID) { fShowID = showID; }
		bool operator() (const ShowDetailPtr& lhs) const
			{ return(lhs->getShowID() == fShowID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//ShowDetailH
/******************************************************************************/
/******************************************************************************/
