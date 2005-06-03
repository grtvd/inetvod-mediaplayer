/* Provider.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ProviderH
#define ProviderH

#include "DataID.h"

namespace asi
{

/******************************************************************************/

class Provider : public Streamable
{
protected:
	ProviderID fProviderID;
	CStr64 fName;

public:
	static const ProviderID AllProvidersID;
	static const CStr32 AllProvidersName;
	static const ProviderID MyProvidersID;
	static const CStr32 MyProvidersName;

protected:
	Provider() {}
	virtual ~Provider() {}

private:
	Provider(const Provider&);						// don't allow copy constructor
	const Provider& operator=(const Provider&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance() { return StreamablePtr(new Provider()); }

	virtual const char* className() const { return "Provider"; }

	// Data Get/Set Methods
	const ProviderID& getProviderID() const { return(fProviderID); }

	const char* getName() const { return fName.c_str(); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<Provider>;
};

class ProviderPtr : public RefCountPtr<Provider>
{
public:
	ProviderPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<Provider>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<Provider&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class ProviderVector : public std::vector<ProviderPtr>
{
public:
	void copy(const ProviderVector& providerVector)
		{ clear(); insert(end(), providerVector.begin(), providerVector.end()); }

	ProviderPtr findByID(const ProviderID& providerID) const;
	ProviderPtr getByID(const ProviderID& providerID) const;
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
		bool operator() (const ProviderPtr& lhs) const
			{ return(lhs->getProviderID() == fProviderID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//ProviderH
/******************************************************************************/
/******************************************************************************/
