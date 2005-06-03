/* RequestData.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RequestDataH
#define RequestDataH

namespace asi
{

/******************************************************************************/

class RequestData : public Streamable
{
protected:
	CStr64 fRequestType;
	StreamablePtr fRequestPtr;

protected:
	RequestData() {}
	virtual ~RequestData() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new RequestData()); }

	virtual const char* className() const { return "RequestData"; }

	void setRequest(StreamablePtr requestPtr);

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<RequestData>;
};

class RequestDataPtr : public RefCountPtr<RequestData>
{
public:
	RequestDataPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<RequestData>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<RequestData&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ResponseData : public Streamable
{
protected:
	CStr64 fResponseType;
	StreamablePtr fResponsePtr;

protected:
	ResponseData(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~ResponseData() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr) { return StreamablePtr(new ResponseData(filerPtr)); }

	virtual const char* className() const { return "ResponseData"; }

	StreamablePtr getResponse() const { return fResponsePtr; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ResponseData>;
};

class ResponseDataPtr : public RefCountPtr<ResponseData>
{
public:
	ResponseDataPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ResponseData>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ResponseData&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ResponseDataConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return ResponseData::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//RequestDataH
/******************************************************************************/
/******************************************************************************/
