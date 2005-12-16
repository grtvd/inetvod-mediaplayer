/* ShowProviderItem.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ShowProviderItemH
#define ShowProviderItemH

namespace asi
{

/******************************************************************************/

class ShowProviderItem;	//forward reference
typedef RefCountPtr<ShowProviderItem> ShowProviderItemPtr;

class ShowProviderItem : public RefCountObject
{
protected:
	ProviderPtr fProviderPtr;
	ShowCostPtr fShowCostPtr;

protected:
	ShowProviderItem(const ProviderID& providerID, const ShowCostPtr& showCostPtr);
	virtual ~ShowProviderItem() {}

private:
	ShowProviderItem(const ShowProviderItem&);						// don't allow copy constructor
	const ShowProviderItem& operator=(const ShowProviderItem&);		// or operator=

public:
	// Construction Methods
	static ShowProviderItemPtr newInstance(const ProviderID& providerID,
		const ShowCostPtr& showCostPtr) { return ShowProviderItemPtr(
		new ShowProviderItem(providerID, showCostPtr)); }

	// Data Get/Set Methods
	ProviderPtr getProvider() const { return fProviderPtr; }
	ShowCostPtr getShowCost() const { return fShowCostPtr; }

	friend class RefCountPtr<ShowProviderItem>;
};

/******************************************************************************/

class ShowProviderItemVector : public std::vector<ShowProviderItemPtr>
{
};

/******************************************************************************/

}; //namespace asi

#endif	//ShowProviderItemH
/******************************************************************************/
/******************************************************************************/
