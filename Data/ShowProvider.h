/* ShowProvider.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ShowProviderH
#define ShowProviderH

#include "DataID.h"

namespace asi
{

/******************************************************************************/

class ShowProvider : public Streamable
{
protected:
	ProviderID fProviderID;
	ShowCostVector fShowCostVector;

protected:
	ShowProvider() {}
	virtual ~ShowProvider() {}

private:
	ShowProvider(const ShowProvider&);						// don't allow copy constructor
	const ShowProvider& operator=(const ShowProvider&);		// or operator=

public:
	// Construction Methods
	static ObjectPtr newInstance();

	virtual const char* className() const { return "ShowProvider"; }

	virtual void clear() { Object::clear(); fProviderID.clear(); fShowCostVector.clear(); }

	// Data Get/Set Methods
	const ProviderID& getProviderID() const { return(fProviderID); }
	void getShowCostVector(ShowCostVector& showCostVector) const
		{ showCostVector.copy(fShowCostVector); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ShowProvider>;
};

class ShowProviderPtr : public RefCountPtr<ShowProvider>
{
public:
	ShowProviderPtr(ObjectPtr objectPtr = ObjectPtr()) : 
		RefCountPtr<ShowProvider>(objectPtr.isNull() ? NULL :
		&dynamic_cast<ShowProvider&>(*objectPtr)) {}

	operator ObjectPtr() { return(ObjectPtr(fT)); }
};

/******************************************************************************/

class ShowProviderVector : public std::vector<ShowProviderPtr>
{
public:
	void copy(const ShowProviderVector& showProviderVector)
		{ clear(); insert(end(), showProviderVector.begin(), showProviderVector.end()); }

	ShowProviderPtr findByID(const ProviderID& providerID) const;
	ShowProviderPtr getByID(const ProviderID& providerID) const;
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
		bool operator() (const ShowProviderPtr& lhs) const
			{ return(lhs->getProviderID() == fProviderID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//ShowProviderH
/******************************************************************************/
/******************************************************************************/
