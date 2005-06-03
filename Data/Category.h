/* Category.h */

/******************************************************************************/
/******************************************************************************/
#ifndef CategoryH
#define CategoryH

#include "DataID.h"

namespace asi
{

/******************************************************************************/

class Category : public Streamable
{
protected:
	CategoryID fCategoryID;
	CStr32 fName;

public:
	static const CategoryID AllCategoriesID;
	static const CStr32 AllCategoriesName;
	static const CategoryID FeaturedCategoryID;

protected:
	Category() {}
	virtual ~Category() {}

private:
	Category(const Category&);						// don't allow copy constructor
	const Category& operator=(const Category&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance() { return StreamablePtr(new Category()); }

	virtual const char* className() const { return "Category"; }

	virtual void clear() { Streamable::clear(); fCategoryID.clear(); fName.clear(); }

	// Data Get/Set Methods
	const CategoryID& getCategoryID() const { return(fCategoryID); }

	const char* getName() const { return fName.c_str(); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<Category>;
};

class CategoryPtr : public RefCountPtr<Category>
{
public:
	CategoryPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<Category>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<Category&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class CategoryVector : public std::vector<CategoryPtr>
{
public:
	void copy(const CategoryVector& categoryVector)
		{ clear(); insert(end(), categoryVector.begin(), categoryVector.end()); }

	CategoryPtr findByID(const CategoryID& categoryID) const;
	CategoryPtr getByID(const CategoryID& categoryID) const;
	void removeByID(const CategoryID& categoryID);

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;

protected:
	struct findIDCompare
	{
	protected:
		CategoryID fCategoryID;

	public:
		findIDCompare(const CategoryID& categoryID) { fCategoryID = categoryID; }
		bool operator() (const CategoryPtr& lhs) const
			{ return(lhs->getCategoryID() == fCategoryID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//CategoryH
/******************************************************************************/
/******************************************************************************/
