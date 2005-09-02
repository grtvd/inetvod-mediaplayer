/* WatchShowRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef WatchShowRqstH
#define WatchShowRqstH

namespace asi
{

/******************************************************************************/

class WatchShowRqst : public Streamable
{
protected:
	RentedShowID fRentedShowID;

protected:
	WatchShowRqst() {}
	virtual ~WatchShowRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new WatchShowRqst()); }

	virtual const char* className() const { return "WatchShowRqst"; }

	void setRentedShowID(const RentedShowID& rentedShowID) { fRentedShowID = rentedShowID; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<WatchShowRqst>;
};

class WatchShowRqstPtr : public RefCountPtr<WatchShowRqst>
{
public:
	WatchShowRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<WatchShowRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<WatchShowRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class WatchShowResp : public Streamable
{
protected:
	LicensePtr fLicensePtr;

protected:
	WatchShowResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~WatchShowResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new WatchShowResp(filerPtr)); }

	virtual const char* className() const { return "WatchShowResp"; }

	LicensePtr getLicensePtr() const { return fLicensePtr; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<WatchShowResp>;
};

class WatchShowRespPtr : public RefCountPtr<WatchShowResp>
{
public:
	WatchShowRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<WatchShowResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<WatchShowResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class WatchShowRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return WatchShowResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//WatchShowRqstH
/******************************************************************************/
/******************************************************************************/
