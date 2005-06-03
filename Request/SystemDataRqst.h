/* SystemDataRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SystemDataRqstH
#define SystemDataRqstH

namespace asi
{

/******************************************************************************/

class SystemDataRqst : public Streamable
{
protected:

protected:
	SystemDataRqst() {}
	virtual ~SystemDataRqst() {}

public:
	static StreamablePtr newInstance() { return StreamablePtr(new SystemDataRqst()); }

	virtual const char* className() const { return "SystemDataRqst"; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<SystemDataRqst>;
};

class SystemDataRqstPtr : public RefCountPtr<SystemDataRqst>
{
public:
	SystemDataRqstPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<SystemDataRqst>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<SystemDataRqst&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class SystemDataResp : public Streamable
{
protected:
	ProviderVector fProviderVector;
	CategoryVector fCategoryVector;
	RatingVector fRatingVector;

protected:
	SystemDataResp(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~SystemDataResp() {}

public:
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new SystemDataResp(filerPtr)); }

	virtual const char* className() const { return "SystemDataResp"; }

	void getProviderVector(ProviderVector& providerVector) const
		{ providerVector.copy(fProviderVector); }
	void getCategoryVector(CategoryVector& categoryVector) const
		{ categoryVector.copy(fCategoryVector); }
	void getRatingVector(RatingVector& ratingVector) const
		{ ratingVector.copy(fRatingVector); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<SystemDataResp>;
};

class SystemDataRespPtr : public RefCountPtr<SystemDataResp>
{
public:
	SystemDataRespPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<SystemDataResp>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<SystemDataResp&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class SystemDataRespConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return SystemDataResp::newInstance(filerPtr); }
};

/******************************************************************************/

};	//namespace asi

#endif	//SystemDataRqstH
/******************************************************************************/
/******************************************************************************/
