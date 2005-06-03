/* RentShowRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentShowRqst.h"

namespace asi
{

/******************************************************************************/

void RentShowRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("RentShowRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void RentShowRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fShowID.c_str());
	filerPtr->writeString(fProviderID.c_str());
	filerPtr->writeObject(fApprovedCostPtr);
}

/******************************************************************************/
/******************************************************************************/

void RentShowResp::readFromFiler(DataFilerPtr filerPtr)
{
	fRentedShowID = RentedShowID(filerPtr->readString().c_str());
	fShowURL.copy(filerPtr->readString().c_str());
}

/******************************************************************************/

void RentShowResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("RentShowResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
