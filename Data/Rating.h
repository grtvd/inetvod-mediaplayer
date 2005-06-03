/* Rating.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RatingH
#define RatingH

#include "DataID.h"

namespace asi
{

/******************************************************************************/

class Rating : public Streamable
{
protected:
	RatingID fRatingID;
	CStr32 fName;

public:
	static const RatingID AllRatingsID;
	static const CStr32 AllRatingsName;

protected:
	Rating() {}
	virtual ~Rating() {}

private:
	Rating(const Rating&);						// don't allow copy constructor
	const Rating& operator=(const Rating&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance() { return StreamablePtr(new Rating()); }

	virtual const char* className() const { return "Rating"; }

	virtual void clear() { Streamable::clear(); fRatingID.clear(); fName.clear(); }

	// Data Get/Set Methods
	const RatingID& getRatingID() const { return(fRatingID); }

	const char* getName() const { return fName.c_str(); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<Rating>;
};

class RatingPtr : public RefCountPtr<Rating>
{
public:
	RatingPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<Rating>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<Rating&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class RatingVector : public std::vector<RatingPtr>
{
public:
	void copy(const RatingVector& ratingVector)
		{ clear(); insert(end(), ratingVector.begin(), ratingVector.end()); }

	RatingPtr findByID(const RatingID& ratingID) const;
	RatingPtr getByID(const RatingID& ratingID) const;
	void removeByID(const RatingID& ratingID);

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;

protected:
	struct findIDCompare
	{
	protected:
		RatingID fRatingID;

	public:
		findIDCompare(const RatingID& ratingID) { fRatingID = ratingID; }
		bool operator() (const RatingPtr& lhs) const
			{ return(lhs->getRatingID() == fRatingID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//RatingH
/******************************************************************************/
/******************************************************************************/
