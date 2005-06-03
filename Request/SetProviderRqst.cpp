/* SetProviderRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SetProviderRqst.h"

namespace asi
{

/******************************************************************************/

void SetProviderRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("SetProviderRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void SetProviderRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fProviderID.c_str());
	filerPtr->writeString(fUserID.c_str());
	filerPtr->writeString(fPassword.c_str());
}

/******************************************************************************/
/******************************************************************************/

void SetProviderResp::readFromFiler(DataFilerPtr filerPtr)
{
}

/******************************************************************************/

void SetProviderResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("SetProviderResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
