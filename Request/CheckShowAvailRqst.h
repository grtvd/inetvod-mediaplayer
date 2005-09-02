/* CheckShowAvailRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef CheckShowAvailRqstH
#define CheckShowAvailRqstH

namespace asi
{

/******************************************************************************/

class CheckShowAvailRqst : public Streamable
{
protected:
	ShowID fShowID;
	ProviderID fProviderID;

protected:
	CheckShowAvailRqst() {}
	virtual ~CheckShowAvailRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new CheckShowAvailRqst()); }

	virtual const char* className() const { return "CheckShowAvailRqst"; }

	void setShowID(const ShowID& showID) { fShowID = showID; }
	void setProviderID(const ProviderID& providerID) { fProviderID = providerID; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<CheckShowAvailRqst>;
};

class CheckShowAvailRqstPtr : public RefCountPtr<CheckShowAvailRqst>
{
public:
	CheckShowAvailRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<CheckShowAvailRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<CheckShowAvailRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class CheckShowAvailResp : public Streamable
{
protected:
	ShowCostVector fShowCostVector;

protected:
	CheckShowAvailResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~CheckShowAvailResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new CheckShowAvailResp(filerPtr)); }

	virtual const char* className() const { return "CheckShowAvailResp"; }

	void getShowCostVector(ShowCostVector& showCostVector) const
		{ showCostVector.copy(fShowCostVector); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<CheckShowAvailResp>;
};

class CheckShowAvailRespPtr : public RefCountPtr<CheckShowAvailResp>
{
public:
	CheckShowAvailRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<CheckShowAvailResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<CheckShowAvailResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class CheckShowAvailRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return CheckShowAvailResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//CheckShowAvailRqstH
/******************************************************************************/
/******************************************************************************/
