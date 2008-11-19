/* ShowSearch.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ShowSearch.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

ObjectPtr ShowSearch::newInstance()
{ 
	ShowSearchPtr showSearchPtr(new ShowSearch());
	showSearchPtr->clear();
	return showSearchPtr;
}

/******************************************************************************/

void ShowSearch::readFromFiler(DataFilerPtr filerPtr)
{
	fShowID = ShowID(filerPtr->readString().c_str());
	fName.copy(filerPtr->readString().c_str());
	fEpisodeName.copy(filerPtr->readString().c_str());
	fReleasedOn = filerPtr->readDateTime();
	fReleasedYear = filerPtr->readShort();
	fPictureURL = filerPtr->readString();

	fShowProviderVector.readFromFiler(filerPtr);
}

/******************************************************************************/

void ShowSearch::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ShowSearch::writeToFiler", "not implemented");
}

/******************************************************************************/
/******************************************************************************/

void ShowSearchVector::readFromFiler(DataFilerPtr filerPtr)
{
	ShowSearchPtr showSearchPtr;
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
	{
		showSearchPtr = ShowSearch::newInstance();
		showSearchPtr->readFromFiler(filerPtr);
		push_back(showSearchPtr);
	}
}

/******************************************************************************/

void ShowSearchVector::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ShowSearchVector::writeToFiler", "not implemented");
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
