/* EnableAdultAccessRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "EnableAdultAccessRqst.h"

namespace asi
{

/******************************************************************************/

void EnableAdultAccessRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("EnableAdultAccessRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void EnableAdultAccessRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fPassword.c_str());
}

/******************************************************************************/
/******************************************************************************/

void EnableAdultAccessResp::readFromFiler(DataFilerPtr filerPtr)
{
}

/******************************************************************************/

void EnableAdultAccessResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("EnableAdultAccessResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
