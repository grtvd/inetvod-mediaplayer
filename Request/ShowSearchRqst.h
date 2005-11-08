/* ShowSearchRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ShowSearchRqstH
#define ShowSearchRqstH

#include "ShowSearch.h"
#include "ShowDetail.h"

namespace asi
{

/******************************************************************************/

class ShowSearchRqst : public Streamable
{
protected:
	CStr64 fPartialName;

	ProviderIDVector fProviderIDVector;
	CategoryIDVector fCategoryIDVector;
	RatingIDVector fRatingIDVector;

	TInt16 fMaxResults;

protected:
	ShowSearchRqst() { fMaxResults = SHRT_MAX; }
	virtual ~ShowSearchRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new ShowSearchRqst()); }

	virtual const char* className() const { return "ShowSearchRqst"; }

	void setPartialName(const char* partialName) { fPartialName.copy(partialName); }

	void setProviderIDVector(const ProviderIDVector& providerIDVector)
		{ fProviderIDVector.copy(providerIDVector); }
	void setCategoryIDVector(const CategoryIDVector& categoryIDVector)
		{ fCategoryIDVector.copy(categoryIDVector); }
	void setRatingIDVector(const RatingIDVector& ratingIDVector)
		{ fRatingIDVector.copy(ratingIDVector); }
	TInt16 getMaxResults() const { return fMaxResults; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ShowSearchRqst>;
};

class ShowSearchRqstPtr : public RefCountPtr<ShowSearchRqst>
{
public:
	ShowSearchRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ShowSearchRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ShowSearchRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ShowSearchResp : public Streamable
{
protected:
	ShowSearchVector fShowSearchVector;
	bool fReachedMax;

protected:
	ShowSearchResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~ShowSearchResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new ShowSearchResp(filerPtr)); }

	virtual const char* className() const { return "ShowSearchResp"; }

	void getShowSearchVector(ShowSearchVector& showSearchVector) const
		{ showSearchVector.copy(fShowSearchVector); }
	bool getReachedMax() const { return fReachedMax; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ShowSearchResp>;
};

class ShowSearchRespPtr : public RefCountPtr<ShowSearchResp>
{
public:
	ShowSearchRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ShowSearchResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ShowSearchResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ShowSearchRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return ShowSearchResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//ShowSearchRqstH
/******************************************************************************/
/******************************************************************************/
