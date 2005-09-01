/* ShowCost.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ShowCost.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

CStr32 ConvertShowCostTypeToString(ShowCostType sct)
{
	if(sct == sct_Free)
		return CStr32("Free");
	if(sct == sct_Subscription)
		return CStr32("Subscription");
	if(sct == sct_PayPerView)
		return CStr32("PayPerView");

	throw ASIException("ConvertShowCostTypeToString", "Unknown ShowCostType(%d)", (int)sct);
}

/******************************************************************************/

ShowCostType ConvertStringToShowCostType(const char* sct)
{
	CStr32 value(sct);
	value.toLower();

	if(value == "free")
		return sct_Free;
	if(value == "subscription")
		return sct_Subscription;
	if(value == "payperview")
		return sct_PayPerView;

	throw ASIException("ConvertStringToShowCostType", "Unknown ShowCostType(%s)", sct);
}

/******************************************************************************/
/******************************************************************************/

const char* ShowCost::getCostDisplay()
{
	if(!fCostDisplay.hasLen() && !fCostPtr.isNull())
	{
		fCostDisplay.copyVarg("$%0.2lf", fCostPtr->getAmount());
	}

	return fCostDisplay.c_str();
}

/******************************************************************************/

void ShowCost::readFromFiler(DataFilerPtr filerPtr)
{
	fShowCostType = ConvertStringToShowCostType(filerPtr->readString().c_str());
	fCostPtr = filerPtr->readObject(MoneyConstructor());
	fCostDisplay.copy(filerPtr->readString().c_str());
	fRentalHours = filerPtr->readShort();
}

/******************************************************************************/

void ShowCost::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(ConvertShowCostTypeToString(fShowCostType).c_str());
	filerPtr->writeObject(fCostPtr);
	filerPtr->writeString(fCostDisplay.c_str());
	filerPtr->writeShort(fRentalHours.getValue());
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
