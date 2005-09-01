/* CheckShowAvailRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "CheckShowAvailRqst.h"

namespace asi
{

/******************************************************************************/

void CheckShowAvailRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("CheckShowAvailRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void CheckShowAvailRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fShowID.c_str());
	filerPtr->writeString(fProviderID.c_str());
}

/******************************************************************************/
/******************************************************************************/

void CheckShowAvailResp::readFromFiler(DataFilerPtr filerPtr)
{
	fShowCostPtr = filerPtr->readObject(ShowCostConstructor());
}

/******************************************************************************/

void CheckShowAvailResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("CheckShowAvailResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
