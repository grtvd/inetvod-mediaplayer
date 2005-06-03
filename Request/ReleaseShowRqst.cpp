/* ReleaseShowRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ReleaseShowRqst.h"

namespace asi
{

/******************************************************************************/

void ReleaseShowRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("ReleaseShowRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void ReleaseShowRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fRentedShowID.c_str());
}

/******************************************************************************/
/******************************************************************************/

void ReleaseShowResp::readFromFiler(DataFilerPtr filerPtr)
{
}

/******************************************************************************/

void ReleaseShowResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ReleaseShowResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
