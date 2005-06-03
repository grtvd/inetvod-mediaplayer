/* SearchData.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SearchDataH
#define SearchDataH

namespace asi
{

/******************************************************************************/

class SearchData : public Object
{
protected:
	CStr64 fPartialName;

	ProviderID fProviderID;
	CategoryID fCategoryID;
	RatingID fRatingID;

protected:
	SearchData() { fProviderID = Provider::AllProvidersID; fCategoryID = Category::AllCategoriesID;
		fRatingID = Rating::AllRatingsID; }
	virtual ~SearchData() {}

public:
	static ObjectPtr newInstance() { return ObjectPtr(new SearchData()); }

	void setPartialName(const char* partialName) { fPartialName.copy(partialName); fPartialName.compress(csw_Trailing); }
	const char* getPartialName() const { return fPartialName.c_str(); }

	void setProviderID(const ProviderID& providerID) { fProviderID = providerID; }
	ProviderID getProviderID() const { return fProviderID; }

	void setCategoryID(const CategoryID& categoryID) { fCategoryID = categoryID; }
	CategoryID getCategoryID() const { return fCategoryID; }

	void setRatingID(const RatingID& ratingID) { fRatingID = ratingID; }
	RatingID getRatingID() const { return fRatingID; }

	friend class RefCountPtr<SearchData>;
};

class SearchDataPtr : public RefCountPtr<SearchData>
{
public:
	SearchDataPtr(ObjectPtr objectPtr = ObjectPtr()) : 
		RefCountPtr<SearchData>(objectPtr.isNull() ? NULL :
		&dynamic_cast<SearchData&>(*objectPtr)) {}

	operator ObjectPtr() { return(ObjectPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//SearchDataH
/******************************************************************************/
/******************************************************************************/
