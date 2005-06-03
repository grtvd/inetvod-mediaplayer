/* Rating.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "Rating.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const RatingID Rating::AllRatingsID("all");
const CStr32 Rating::AllRatingsName("All Ratings");

/******************************************************************************/

void Rating::readFromFiler(DataFilerPtr filerPtr)
{
	fRatingID = RatingID(filerPtr->readString().c_str());
	fName.copy(filerPtr->readString().c_str());
}

/******************************************************************************/

void Rating::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fRatingID.c_str());
	filerPtr->writeString(fName.c_str());
}

/******************************************************************************/
/******************************************************************************/

RatingPtr RatingVector::findByID(const RatingID& ratingID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(ratingID));
	if(iter != end())
		return(*iter);

	return RatingPtr();
}

/******************************************************************************/

RatingPtr RatingVector::getByID(const RatingID& ratingID) const
{
	const_iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(ratingID));
	if(iter != end())
		return(*iter);

	throw ASIException("RatingVector::getByID","Invalid RatingID(%s)", ratingID.c_str());
}

/******************************************************************************/

void RatingVector::removeByID(const RatingID& ratingID)
{
	iterator iter;

	iter = std::find_if(begin(),end(),findIDCompare(ratingID));
	if(iter != end())
		erase(iter);
}

/******************************************************************************/

void RatingVector::readFromFiler(DataFilerPtr filerPtr)
{
	RatingPtr ratingPtr;
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
	{
		ratingPtr = Rating::newInstance();
		ratingPtr->readFromFiler(filerPtr);
		push_back(ratingPtr);
	}
}

/******************************************************************************/

void RatingVector::writeToFiler(DataFilerPtr filerPtr) const
{
	RatingVector::const_iterator iter;

	filerPtr->writeLong(size());
	for(iter = begin(); iter != end(); ++iter)
		(*iter)->writeToFiler(filerPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
