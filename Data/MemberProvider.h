/* MemberProvider.h */

/******************************************************************************/
/******************************************************************************/
#ifndef MemberProviderH
#define MemberProviderH

#include "DataID.h"

namespace asi
{

/******************************************************************************/

class MemberProvider : public Streamable
{
protected:
	ProviderID fProviderID;

protected:
	MemberProvider() {}
	MemberProvider(const ProviderID& providerID) { fProviderID = providerID; }
	virtual ~MemberProvider() {}

private:
	MemberProvider(const MemberProvider&);						// don't allow copy constructor
	const MemberProvider& operator=(const MemberProvider&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance() { return StreamablePtr(new MemberProvider()); }
	static StreamablePtr newInstance(const ProviderID& providerID)
		{ return StreamablePtr(new MemberProvider(providerID)); }

	virtual const char* className() const { return "MemberProvider"; }

	// Data Get/Set Methods
	const ProviderID& getProviderID() const { return(fProviderID); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<MemberProvider>;
};

class MemberProviderPtr : public RefCountPtr<MemberProvider>
{
public:
	MemberProviderPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<MemberProvider>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<MemberProvider&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class MemberProviderVector : public std::vector<MemberProviderPtr>
{
public:
	void copy(const MemberProviderVector& memberProviderVector)
		{ clear(); insert(end(), memberProviderVector.begin(), memberProviderVector.end()); }

	MemberProviderPtr findByID(const ProviderID& providerID) const;
	MemberProviderPtr getByID(const ProviderID& providerID) const;
	void removeByID(const ProviderID& providerID);

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;

protected:
	struct findIDCompare
	{
	protected:
		ProviderID fProviderID;

	public:
		findIDCompare(const ProviderID& providerID) { fProviderID = providerID; }
		bool operator() (const MemberProviderPtr& lhs) const
			{ return(lhs->getProviderID() == fProviderID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//MemberProviderH
/******************************************************************************/
/******************************************************************************/
