/* ShowDetailRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ShowDetailRqst.h"

namespace asi
{

/******************************************************************************/

void ShowDetailRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("ShowDetailRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void ShowDetailRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fShowID.c_str());
	filerPtr->writeString(fProviderID.c_str());
}

/******************************************************************************/
/******************************************************************************/

void ShowDetailResp::readFromFiler(DataFilerPtr filerPtr)
{
	fShowDetailPtr = filerPtr->readObject(ShowDetailConstructor());
}

/******************************************************************************/

void ShowDetailResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ShowDetailResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
