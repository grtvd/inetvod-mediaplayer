/* ShowDetailRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ShowDetailRqstH
#define ShowDetailRqstH

#include "ShowDetail.h"

namespace asi
{

/******************************************************************************/

class ShowDetailRqst : public Streamable
{
protected:
	ShowID fShowID;

protected:
	ShowDetailRqst() {}
	virtual ~ShowDetailRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new ShowDetailRqst()); }

	virtual const char* className() const { return "ShowDetailRqst"; }

	void setShowID(const ShowID& showID) { fShowID = showID; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ShowDetailRqst>;
};

class ShowDetailRqstPtr : public RefCountPtr<ShowDetailRqst>
{
public:
	ShowDetailRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ShowDetailRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ShowDetailRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ShowDetailResp : public Streamable
{
protected:
	ShowDetailPtr fShowDetailPtr;

protected:
	ShowDetailResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~ShowDetailResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new ShowDetailResp(filerPtr)); }

	virtual const char* className() const { return "ShowDetailResp"; }

	ShowDetailPtr getShowDetail() { return fShowDetailPtr; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ShowDetailResp>;
};

class ShowDetailRespPtr : public RefCountPtr<ShowDetailResp>
{
public:
	ShowDetailRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ShowDetailResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ShowDetailResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ShowDetailRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return ShowDetailResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//ShowDetailRqstH
/******************************************************************************/
/******************************************************************************/
