/* EnableAdultAccessRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef EnableAdultAccessRqstH
#define EnableAdultAccessRqstH

namespace asi
{

/******************************************************************************/

class EnableAdultAccessRqst : public Streamable
{
protected:
	CStr32 fPassword;

protected:
	EnableAdultAccessRqst() {}
	virtual ~EnableAdultAccessRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new EnableAdultAccessRqst()); }

	virtual const char* className() const { return "EnableAdultAccessRqst"; }

	void setPassword(const char* password) { fPassword.copy(password); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<EnableAdultAccessRqst>;
};

class EnableAdultAccessRqstPtr : public RefCountPtr<EnableAdultAccessRqst>
{
public:
	EnableAdultAccessRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<EnableAdultAccessRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<EnableAdultAccessRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class EnableAdultAccessResp : public Streamable
{
protected:
	EnableAdultAccessResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~EnableAdultAccessResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new EnableAdultAccessResp(filerPtr)); }

	virtual const char* className() const { return "EnableAdultAccessResp"; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<EnableAdultAccessResp>;
};

class EnableAdultAccessRespPtr : public RefCountPtr<EnableAdultAccessResp>
{
public:
	EnableAdultAccessRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<EnableAdultAccessResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<EnableAdultAccessResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class EnableAdultAccessRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return EnableAdultAccessResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//EnableAdultAccessRqstH
/******************************************************************************/
/******************************************************************************/
