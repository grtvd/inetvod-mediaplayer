/* RentedShowRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentedShowRqst.h"

namespace asi
{

/******************************************************************************/

void RentedShowRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("RentedShowRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void RentedShowRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fRentedShowID.c_str());
}

/******************************************************************************/
/******************************************************************************/

void RentedShowResp::readFromFiler(DataFilerPtr filerPtr)
{
	fRentedShowPtr = filerPtr->readObject(RentedShowConstructor());
}

/******************************************************************************/

void RentedShowResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("RentedShowResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
