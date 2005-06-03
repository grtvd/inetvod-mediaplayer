/* INetVODPlayerRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef INetVODPlayerRqstH
#define INetVODPlayerRqstH

#include "RequestData.h"

namespace asi
{

/******************************************************************************/

class INetVODPlayerRqst : public Streamable
{
protected:
	CStr16 fVersion;
	CStr64 fRequestID;
	CStrVar fSessionData;
	RequestDataPtr fRequestDataPtr;

protected:
	INetVODPlayerRqst() {}
	virtual ~INetVODPlayerRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new INetVODPlayerRqst()); }

	virtual const char* className() const { return "INetVODPlayerRqst"; }

	void setVersion(const char* version) { fVersion.copy(version); }
	void setRequestID(const char* requestID) { fRequestID.copy(requestID); }
	const char* getRequestID() const { return fRequestID.c_str(); }
	void setSessionData(const char* sessionData) { fSessionData.copy(sessionData); }
	void setRequestData(RequestDataPtr requestDataPtr) { fRequestDataPtr = requestDataPtr; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<INetVODPlayerRqst>;
};

class INetVODPlayerRqstPtr : public RefCountPtr<INetVODPlayerRqst>
{
public:
	INetVODPlayerRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<INetVODPlayerRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<INetVODPlayerRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class INetVODPlayerResp : public Streamable
{
protected:
	CStr64 fRequestID;
	StatusCode fStatusCode;
	CStrVar fStatusMessage;
	ResponseDataPtr fResponseDataPtr;

protected:
	INetVODPlayerResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~INetVODPlayerResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new INetVODPlayerResp(filerPtr)); }

	virtual const char* className() const { return "INetVODPlayerResp"; }

	const char* getRequestID() const { return fRequestID.c_str(); }
	StatusCode getStatusCode() const { return fStatusCode; }
	const char* getStatusMessage() const { return fStatusMessage.c_str(); }
	ResponseDataPtr getResponseDataPtr() const { return fResponseDataPtr; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<INetVODPlayerResp>;
};

class INetVODPlayerRespPtr : public RefCountPtr<INetVODPlayerResp>
{
public:
	INetVODPlayerRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<INetVODPlayerResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<INetVODPlayerResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class INetVODPlayerRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return INetVODPlayerResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//INetVODPlayerRqstH
/******************************************************************************/
/******************************************************************************/
