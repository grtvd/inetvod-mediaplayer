/* ReleaseShowRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ReleaseShowRqstH
#define ReleaseShowRqstH

namespace asi
{

/******************************************************************************/

class ReleaseShowRqst : public Streamable
{
protected:
	RentedShowID fRentedShowID;

protected:
	ReleaseShowRqst() {}
	virtual ~ReleaseShowRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new ReleaseShowRqst()); }

	virtual const char* className() const { return "ReleaseShowRqst"; }

	void setRentedShowID(const RentedShowID& rentedShowID) { fRentedShowID = rentedShowID; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ReleaseShowRqst>;
};

class ReleaseShowRqstPtr : public RefCountPtr<ReleaseShowRqst>
{
public:
	ReleaseShowRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ReleaseShowRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ReleaseShowRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ReleaseShowResp : public Streamable
{
protected:
	ReleaseShowResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~ReleaseShowResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new ReleaseShowResp(filerPtr)); }

	virtual const char* className() const { return "ReleaseShowResp"; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ReleaseShowResp>;
};

class ReleaseShowRespPtr : public RefCountPtr<ReleaseShowResp>
{
public:
	ReleaseShowRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ReleaseShowResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ReleaseShowResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ReleaseShowRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return ReleaseShowResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//ReleaseShowRqstH
/******************************************************************************/
/******************************************************************************/
