/* SystemDataRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SystemDataRqst.h"

namespace asi
{

/******************************************************************************/

void SystemDataRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("SystemDataRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void SystemDataRqst::writeToFiler(DataFilerPtr filerPtr) const
{
}

/******************************************************************************/
/******************************************************************************/

void SystemDataResp::readFromFiler(DataFilerPtr filerPtr)
{
	fProviderVector.readFromFiler(filerPtr);
	fCategoryVector.readFromFiler(filerPtr);
	fRatingVector.readFromFiler(filerPtr);
}

/******************************************************************************/

void SystemDataResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("SystemDataResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
