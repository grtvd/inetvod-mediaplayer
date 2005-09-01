/* ShowDetail.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ShowDetail.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

void ShowDetail::readFromFiler(DataFilerPtr filerPtr)
{
	fShowID = ShowID(filerPtr->readString().c_str());
	fProviderID = ProviderID(filerPtr->readString().c_str());
	fName.copy(filerPtr->readString().c_str());
	fEpisodeName.copy(filerPtr->readString().c_str());
	fEpisodeNumber.copy(filerPtr->readString().c_str());

	fReleasedOn = filerPtr->readDate();
	fReleasedYear = filerPtr->readShort();
	fDescription = filerPtr->readString();
	fRunningMins = filerPtr->readShort();
	fPictureURL = filerPtr->readString();

	fCategoryIDVector.readFromFiler(filerPtr);
	fRatingID = RatingID(filerPtr->readString().c_str());
	fIsAdult = filerPtr->readBoolean();

	fShowCostPtr = filerPtr->readObject(ShowCostConstructor());
}

/******************************************************************************/

void ShowDetail::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ShowDetail::writeToFiler", "not implemented");
}

/******************************************************************************/
/******************************************************************************/

void ShowDetailVector::readFromFiler(DataFilerPtr filerPtr)
{
	//ShowDetailPtr showDetailPtr;
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
	{
		//showDetailPtr = ShowDetail::newInstance(filerPtr);
		push_back(ShowDetail::newInstance(filerPtr));
		//push_back(showDetailPtr);
	}
}

/******************************************************************************/

void ShowDetailVector::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ShowDetailVector::writeToFiler", "not implemented");
	//ShowDetailVector::const_iterator iter;

	//filerPtr->writeLong(size());
	//for(iter = begin(); iter != end(); ++iter)
	//	(*iter)->writeToFiler(filerPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
