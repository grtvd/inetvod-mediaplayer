/* MemberProvider.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "MemberProvider.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

void MemberProvider::readFromFiler(DataFilerPtr filerPtr)
{
	fProviderID = ProviderID(filerPtr->readString().c_str());
}

/******************************************************************************/

void MemberProvider::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fProviderID.c_str());
}

/******************************************************************************/
/******************************************************************************/

MemberProviderPtr MemberProviderVector::findByID(const ProviderID& providerID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(providerID));
	if(iter != end())
		return(*iter);

	return MemberProviderPtr();
}

/******************************************************************************/

MemberProviderPtr MemberProviderVector::getByID(const ProviderID& providerID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(providerID));
	if(iter != end())
		return(*iter);

	throw ASIException("MemberProviderVector::getByID","Invalid ProviderID(%s)", providerID.c_str());
}

/******************************************************************************/

void MemberProviderVector::removeByID(const ProviderID& providerID)
{
	iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(providerID));
	if(iter != end())
		erase(iter);
}

/******************************************************************************/

void MemberProviderVector::readFromFiler(DataFilerPtr filerPtr)
{
	MemberProviderPtr memberProviderPtr;
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
	{
		memberProviderPtr = MemberProvider::newInstance();
		memberProviderPtr->readFromFiler(filerPtr);
		push_back(memberProviderPtr);
	}
}

/******************************************************************************/

void MemberProviderVector::writeToFiler(DataFilerPtr filerPtr) const
{
	MemberProviderVector::const_iterator iter;

	filerPtr->writeLong(size());
	for(iter = begin(); iter != end(); ++iter)
		(*iter)->writeToFiler(filerPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
