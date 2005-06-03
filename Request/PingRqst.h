/* PingRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef PingRqstH
#define PingRqstH

namespace asi
{

/******************************************************************************/

class PingRqst : public Streamable
{
protected:
	PingRqst() {}
	virtual ~PingRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new PingRqst()); }

	virtual const char* className() const { return "PingRqst"; }

	virtual void readFromFiler(DataFilerPtr filerPtr) { throw ASIException("PingRqst::readFromFiler", "not implemented"); }
	virtual void writeToFiler(DataFilerPtr filerPtr) const {}

	friend class RefCountPtr<PingRqst>;
};

class PingRqstPtr : public RefCountPtr<PingRqst>
{
public:
	PingRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<PingRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<PingRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class PingResp : public Streamable
{
protected:
	PingResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~PingResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new PingResp(filerPtr)); }

	virtual const char* className() const { return "PingResp"; }

	virtual void readFromFiler(DataFilerPtr filerPtr) {}
	virtual void writeToFiler(DataFilerPtr filerPtr) const { throw ASIException("PingResp::writeToFiler", "not implemented"); }

	friend class RefCountPtr<PingResp>;
};

class PingRespPtr : public RefCountPtr<PingResp>
{
public:
	PingRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<PingResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<PingResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class PingRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return PingResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//PingRqstH
/******************************************************************************/
/******************************************************************************/
