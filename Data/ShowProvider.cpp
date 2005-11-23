/* ShowProvider.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ShowProvider.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

ObjectPtr ShowProvider::newInstance()
{ 
	ShowProviderPtr showProviderPtr(new ShowProvider());
	showProviderPtr->clear();
	return showProviderPtr;
}

/******************************************************************************/

void ShowProvider::readFromFiler(DataFilerPtr filerPtr)
{
	fProviderID = ProviderID(filerPtr->readString().c_str());

	fShowCostVector.readFromFiler(filerPtr);
}

/******************************************************************************/

void ShowProvider::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ShowProvider::writeToFiler", "not implemented");
}

/******************************************************************************/
/******************************************************************************/

ShowProviderPtr ShowProviderVector::findByID(const ProviderID& providerID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(providerID));
	if(iter != end())
		return(*iter);

	return ShowProviderPtr();
}

/******************************************************************************/

ShowProviderPtr ShowProviderVector::getByID(const ProviderID& providerID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(providerID));
	if(iter != end())
		return(*iter);

	throw ASIException("ShowProviderVector::getByID","Invalid ProviderID(%s)", providerID.c_str());
}

/******************************************************************************/

void ShowProviderVector::removeByID(const ProviderID& providerID)
{
	iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(providerID));
	if(iter != end())
		erase(iter);
}

/******************************************************************************/

void ShowProviderVector::readFromFiler(DataFilerPtr filerPtr)
{
	ShowProviderPtr showProviderPtr;
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
	{
		showProviderPtr = ShowProvider::newInstance();
		showProviderPtr->readFromFiler(filerPtr);
		push_back(showProviderPtr);
	}
}

/******************************************************************************/

void ShowProviderVector::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ShowProviderVector::writeToFiler", "not implemented");
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
