/* SetProviderRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SetProviderRqstH
#define SetProviderRqstH

namespace asi
{

/******************************************************************************/

class SetProviderRqst : public Streamable
{
protected:
	ProviderID fProviderID;

	CStr64 fUserID;
	CStr32 fPassword;

protected:
	SetProviderRqst() {}
	virtual ~SetProviderRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new SetProviderRqst()); }

	virtual const char* className() const { return "SetProviderRqst"; }

	void setProviderID(const ProviderID& providerID) { fProviderID = providerID; }

	void setUserID(const char* userID) { fUserID = userID; }
	void setPassword(const char* password) { fPassword = password; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<SetProviderRqst>;
};

class SetProviderRqstPtr : public RefCountPtr<SetProviderRqst>
{
public:
	SetProviderRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<SetProviderRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<SetProviderRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class SetProviderResp : public Streamable
{
protected:
	SetProviderResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~SetProviderResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new SetProviderResp(filerPtr)); }

	virtual const char* className() const { return "SetProviderResp"; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<SetProviderResp>;
};

class SetProviderRespPtr : public RefCountPtr<SetProviderResp>
{
public:
	SetProviderRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<SetProviderResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<SetProviderResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class SetProviderRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return SetProviderResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//SetProviderRqstH
/******************************************************************************/
/******************************************************************************/
