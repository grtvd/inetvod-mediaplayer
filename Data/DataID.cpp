/* DataID.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/

void ProviderIDVector::readFromFiler(DataFilerPtr filerPtr)
{
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
		push_back(ProviderID(filerPtr->readString().c_str()));
}

/******************************************************************************/

void ProviderIDVector::writeToFiler(DataFilerPtr filerPtr) const
{
	ProviderIDVector::const_iterator iter;

	filerPtr->writeLong(size());
	for(iter = begin(); iter != end(); ++iter)
		filerPtr->writeString((*iter).c_str());
}

/******************************************************************************/
/******************************************************************************/

void CategoryIDVector::readFromFiler(DataFilerPtr filerPtr)
{
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
		push_back(CategoryID(filerPtr->readString().c_str()));
}

/******************************************************************************/

void CategoryIDVector::writeToFiler(DataFilerPtr filerPtr) const
{
	CategoryIDVector::const_iterator iter;

	filerPtr->writeLong(size());
	for(iter = begin(); iter != end(); ++iter)
		filerPtr->writeString((*iter).c_str());
}

/******************************************************************************/
/******************************************************************************/

void RatingIDVector::readFromFiler(DataFilerPtr filerPtr)
{
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
		push_back(RatingID(filerPtr->readString().c_str()));
}

/******************************************************************************/

void RatingIDVector::writeToFiler(DataFilerPtr filerPtr) const
{
	RatingIDVector::const_iterator iter;

	filerPtr->writeLong(size());
	for(iter = begin(); iter != end(); ++iter)
		filerPtr->writeString((*iter).c_str());
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
