/* RentedShowListRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentedShowListRqst.h"

namespace asi
{

/******************************************************************************/

void RentedShowListRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("RentedShowListRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void RentedShowListRqst::writeToFiler(DataFilerPtr filerPtr) const
{
}

/******************************************************************************/
/******************************************************************************/

void RentedShowListResp::readFromFiler(DataFilerPtr filerPtr)
{
	fRentedShowSearchVector.readFromFiler(filerPtr);
}

/******************************************************************************/

void RentedShowListResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("RentedShowListResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
