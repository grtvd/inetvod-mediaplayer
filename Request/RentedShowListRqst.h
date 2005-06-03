/* RentedShowListRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RentedShowListRqstH
#define RentedShowListRqstH

//#include "ShowDetail.h"
#include "RentedShowSearch.h"

namespace asi
{

/******************************************************************************/

class RentedShowListRqst : public Streamable
{
protected:
	RentedShowListRqst() {}
	virtual ~RentedShowListRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new RentedShowListRqst()); }

	virtual const char* className() const { return "RentedShowListRqst"; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<RentedShowListRqst>;
};

class RentedShowListRqstPtr : public RefCountPtr<RentedShowListRqst>
{
public:
	RentedShowListRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<RentedShowListRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<RentedShowListRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class RentedShowListResp : public Streamable
{
protected:
	RentedShowSearchVector fRentedShowSearchVector;

protected:
	RentedShowListResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~RentedShowListResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new RentedShowListResp(filerPtr)); }

	virtual const char* className() const { return "RentedShowListResp"; }

	void getRentedShowSearchVector(RentedShowSearchVector& rentedShowSearchVector) const
		{ rentedShowSearchVector.copy(fRentedShowSearchVector); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<RentedShowListResp>;
};

class RentedShowListRespPtr : public RefCountPtr<RentedShowListResp>
{
public:
	RentedShowListRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<RentedShowListResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<RentedShowListResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class RentedShowListRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return RentedShowListResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//RentedShowListRqstH
/******************************************************************************/
/******************************************************************************/
