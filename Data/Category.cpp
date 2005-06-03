/* Category.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "Category.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const CategoryID Category::AllCategoriesID("all");
const CStr32 Category::AllCategoriesName("All Categories");
const CategoryID Category::FeaturedCategoryID("featured");

/******************************************************************************/

void Category::readFromFiler(DataFilerPtr filerPtr)
{
	fCategoryID = CategoryID(filerPtr->readString().c_str());
	fName.copy(filerPtr->readString().c_str());
}

/******************************************************************************/

void Category::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fCategoryID.c_str());
	filerPtr->writeString(fName.c_str());
}

/******************************************************************************/
/******************************************************************************/

CategoryPtr CategoryVector::findByID(const CategoryID& categoryID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(categoryID));
	if(iter != end())
		return(*iter);

	return CategoryPtr();
}

/******************************************************************************/

CategoryPtr CategoryVector::getByID(const CategoryID& categoryID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(categoryID));
	if(iter != end())
		return(*iter);

	throw ASIException("CategoryVector::getByID","Invalid CategoryID(%s)", categoryID.c_str());
}

/******************************************************************************/

void CategoryVector::removeByID(const CategoryID& categoryID)
{
	iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(categoryID));
	if(iter != end())
		erase(iter);
}

/******************************************************************************/

void CategoryVector::readFromFiler(DataFilerPtr filerPtr)
{
	CategoryPtr categoryPtr;
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
	{
		categoryPtr = Category::newInstance();
		categoryPtr->readFromFiler(filerPtr);
		push_back(categoryPtr);
	}
}

/******************************************************************************/

void CategoryVector::writeToFiler(DataFilerPtr filerPtr) const
{
	CategoryVector::const_iterator iter;

	filerPtr->writeLong(size());
	for(iter = begin(); iter != end(); ++iter)
		(*iter)->writeToFiler(filerPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
