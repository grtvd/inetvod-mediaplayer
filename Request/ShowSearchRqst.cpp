/* ShowSearchRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ShowSearchRqst.h"

namespace asi
{

/******************************************************************************/

void ShowSearchRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("ShowSearchRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void ShowSearchRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fPartialName.c_str());

	fProviderIDVector.writeToFiler(filerPtr);
	fCategoryIDVector.writeToFiler(filerPtr);
	fRatingIDVector.writeToFiler(filerPtr);

	fMaxResults.writeToFiler(filerPtr);
}

/******************************************************************************/
/******************************************************************************/

void ShowSearchResp::readFromFiler(DataFilerPtr filerPtr)
{
	fShowSearchVector.readFromFiler(filerPtr);
	fReachedMax = filerPtr->readBoolean();
}

/******************************************************************************/

void ShowSearchResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ShowSearchResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
