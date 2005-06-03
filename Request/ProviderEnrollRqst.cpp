/* ProviderEnrollRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ProviderEnrollRqst.h"

namespace asi
{

/******************************************************************************/

void ProviderEnrollRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("ProviderEnrollRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void ProviderEnrollRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fProviderID.c_str());
}

/******************************************************************************/
/******************************************************************************/

void ProviderEnrollResp::readFromFiler(DataFilerPtr filerPtr)
{
}

/******************************************************************************/

void ProviderEnrollResp::writeToFiler(DataFilerPtr filerPtr) const
{
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
