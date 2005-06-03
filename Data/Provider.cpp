/* Provider.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "Provider.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ProviderID Provider::AllProvidersID("all");
const CStr32 Provider::AllProvidersName("All Providers");
const ProviderID Provider::MyProvidersID("my");
const CStr32 Provider::MyProvidersName("My Providers");

/******************************************************************************/

void Provider::readFromFiler(DataFilerPtr filerPtr)
{
	fProviderID = ProviderID(filerPtr->readString().c_str());
	fName.copy(filerPtr->readString().c_str());
}

/******************************************************************************/

void Provider::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fProviderID.c_str());
	filerPtr->writeString(fName.c_str());
}

/******************************************************************************/
/******************************************************************************/

ProviderPtr ProviderVector::findByID(const ProviderID& providerID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(providerID));
	if(iter != end())
		return(*iter);

	return ProviderPtr();
}

/******************************************************************************/

ProviderPtr ProviderVector::getByID(const ProviderID& providerID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(providerID));
	if(iter != end())
		return(*iter);

	throw ASIException("ProviderVector::getByID","Invalid ProviderID(%s)", providerID.c_str());
}

/******************************************************************************/

void ProviderVector::removeByID(const ProviderID& providerID)
{
	iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(providerID));
	if(iter != end())
		erase(iter);
}

/******************************************************************************/

void ProviderVector::readFromFiler(DataFilerPtr filerPtr)
{
	ProviderPtr providerPtr;
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
	{
		providerPtr = Provider::newInstance();
		providerPtr->readFromFiler(filerPtr);
		push_back(providerPtr);
	}
}

/******************************************************************************/

void ProviderVector::writeToFiler(DataFilerPtr filerPtr) const
{
	ProviderVector::const_iterator iter;

	filerPtr->writeLong(size());
	for(iter = begin(); iter != end(); ++iter)
		(*iter)->writeToFiler(filerPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
