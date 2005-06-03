/* RentedShowSearch.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentedShowSearch.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

ObjectPtr RentedShowSearch::newInstance()
{ 
	RentedShowSearchPtr rentedShowSearchPtr(new RentedShowSearch());
	rentedShowSearchPtr->clear();
	return rentedShowSearchPtr;
}

/******************************************************************************/

void RentedShowSearch::readFromFiler(DataFilerPtr filerPtr)
{
	fRentedShowID = RentedShowID(filerPtr->readString().c_str());

	fShowID = ShowID(filerPtr->readString().c_str());
	fProviderID = ProviderID(filerPtr->readString().c_str());
	fName.copy(filerPtr->readString().c_str());
	fEpisodeName.copy(filerPtr->readString().c_str());

	fAvailableUntil = filerPtr->readDateTime();
}

/******************************************************************************/

void RentedShowSearch::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("RentedShowSearch::writeToFiler", "not implemented");
}

/******************************************************************************/
/******************************************************************************/

void RentedShowSearchVector::removeByID(const RentedShowID& rentedShowID)
{
	iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(rentedShowID));
	if(iter != end())
		erase(iter);
}

/******************************************************************************/

void RentedShowSearchVector::readFromFiler(DataFilerPtr filerPtr)
{
	RentedShowSearchPtr rentedShowSearchPtr;
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
	{
		rentedShowSearchPtr = RentedShowSearch::newInstance();
		rentedShowSearchPtr->readFromFiler(filerPtr);
		push_back(rentedShowSearchPtr);
	}
}

/******************************************************************************/

void RentedShowSearchVector::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("RentedShowSearchVector::writeToFiler", "not implemented");
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
