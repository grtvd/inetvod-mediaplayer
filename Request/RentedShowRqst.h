/* RentedShowRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RentedShowRqstH
#define RentedShowRqstH

//#include "ShowDetail.h"
#include "RentedShow.h"

namespace asi
{

/******************************************************************************/

class RentedShowRqst : public Streamable
{
protected:
	RentedShowID fRentedShowID;

protected:
	RentedShowRqst() {}
	virtual ~RentedShowRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new RentedShowRqst()); }

	virtual const char* className() const { return "RentedShowRqst"; }

	void setRentedShowID(const RentedShowID& rentedShowID) { fRentedShowID = rentedShowID; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<RentedShowRqst>;
};

class RentedShowRqstPtr : public RefCountPtr<RentedShowRqst>
{
public:
	RentedShowRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<RentedShowRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<RentedShowRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class RentedShowResp : public Streamable
{
protected:
	RentedShowPtr fRentedShowPtr;

protected:
	RentedShowResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~RentedShowResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new RentedShowResp(filerPtr)); }

	virtual const char* className() const { return "RentedShowResp"; }

	RentedShowPtr getRentedShow() { return fRentedShowPtr; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<RentedShowResp>;
};

class RentedShowRespPtr : public RefCountPtr<RentedShowResp>
{
public:
	RentedShowRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<RentedShowResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<RentedShowResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class RentedShowRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return RentedShowResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//RentedShowRqstH
/******************************************************************************/
/******************************************************************************/
