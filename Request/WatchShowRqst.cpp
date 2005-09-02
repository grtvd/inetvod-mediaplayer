/* WatchShowRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "WatchShowRqst.h"

namespace asi
{

/******************************************************************************/

void WatchShowRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("WatchShowRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void WatchShowRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fRentedShowID.c_str());
}

/******************************************************************************/
/******************************************************************************/

void WatchShowResp::readFromFiler(DataFilerPtr filerPtr)
{
	fLicensePtr = filerPtr->readObject(LicenseConstructor());
}

/******************************************************************************/

void WatchShowResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("WatchShowResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
