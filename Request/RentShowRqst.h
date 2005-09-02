/* RentShowRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RentShowRqstH
#define RentShowRqstH

#include "License.h"

namespace asi
{

/******************************************************************************/

class RentShowRqst : public Streamable
{
protected:
	ShowID fShowID;
	ProviderID fProviderID;
	ShowCostPtr fApprovedCostPtr;

protected:
	RentShowRqst() {}
	virtual ~RentShowRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new RentShowRqst()); }

	virtual const char* className() const { return "RentShowRqst"; }

	void setShowID(const ShowID& showID) { fShowID = showID; }
	void setProviderID(const ProviderID& providerID) { fProviderID = providerID; }
	void setApprovedCost(const ShowCostPtr& approvedCostPtr) { fApprovedCostPtr = approvedCostPtr; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<RentShowRqst>;
};

class RentShowRqstPtr : public RefCountPtr<RentShowRqst>
{
public:
	RentShowRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<RentShowRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<RentShowRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class RentShowResp : public Streamable
{
protected:
	RentedShowID fRentedShowID;
	LicensePtr fLicensePtr;

protected:
	RentShowResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~RentShowResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new RentShowResp(filerPtr)); }

	virtual const char* className() const { return "RentShowResp"; }

	const RentedShowID& getRentedShowID() const { return(fRentedShowID); }
	LicensePtr getLicensePtr() const { return fLicensePtr; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<RentShowResp>;
};

class RentShowRespPtr : public RefCountPtr<RentShowResp>
{
public:
	RentShowRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<RentShowResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<RentShowResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class RentShowRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return RentShowResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//RentShowRqstH
/******************************************************************************/
/******************************************************************************/
