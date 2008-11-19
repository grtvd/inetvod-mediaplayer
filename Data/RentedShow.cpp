/* RentedShow.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentedShow.h"

namespace asi
{

/******************************************************************************/

void RentedShow::readFromFiler(DataFilerPtr filerPtr)
{
	fRentedShowID = RentedShowID(filerPtr->readString().c_str());

	fShowID = ShowID(filerPtr->readString().c_str());
	fProviderID = ProviderID(filerPtr->readString().c_str());
	fName.copy(filerPtr->readString().c_str());
	fEpisodeName.copy(filerPtr->readString().c_str());
	fEpisodeNumber.copy(filerPtr->readString().c_str());

	fReleasedOn = filerPtr->readDateTime();
	fReleasedYear = filerPtr->readShort();
	fDescription = filerPtr->readString();
	fRunningMins = filerPtr->readShort();
	fPictureURL = filerPtr->readString();

	fCategoryIDVector.readFromFiler(filerPtr);
	fRatingID = RatingID(filerPtr->readString().c_str());
	fIsAdult = filerPtr->readBoolean();

	fShowCostPtr = filerPtr->readObject(ShowCostConstructor());
	fRentedOn = filerPtr->readDateTime();
	fAvailableUntil = filerPtr->readDateTime();
}

/******************************************************************************/

void RentedShow::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("RentedShow::writeToFiler", "not implemented");
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
