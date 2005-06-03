/* ProviderEnrollRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ProviderEnrollRqstH
#define ProviderEnrollRqstH

namespace asi
{

/******************************************************************************/

class ProviderEnrollRqst : public Streamable
{
protected:
	ProviderID fProviderID;

protected:
	ProviderEnrollRqst() {}
	virtual ~ProviderEnrollRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new ProviderEnrollRqst()); }

	virtual const char* className() const { return "ProviderEnrollRqst"; }

	void setProviderID(const ProviderID& providerID) { fProviderID = providerID; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ProviderEnrollRqst>;
};

class ProviderEnrollRqstPtr : public RefCountPtr<ProviderEnrollRqst>
{
public:
	ProviderEnrollRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ProviderEnrollRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ProviderEnrollRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ProviderEnrollResp : public Streamable
{
protected:
	ProviderEnrollResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~ProviderEnrollResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new ProviderEnrollResp(filerPtr)); }

	virtual const char* className() const { return "ProviderEnrollResp"; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ProviderEnrollResp>;
};

class ProviderEnrollRespPtr : public RefCountPtr<ProviderEnrollResp>
{
public:
	ProviderEnrollRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<ProviderEnrollResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<ProviderEnrollResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ProviderEnrollRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return ProviderEnrollResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//ProviderEnrollRqstH
/******************************************************************************/
/******************************************************************************/
