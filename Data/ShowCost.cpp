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

CStr64 ShowCost::formatRental()
{
	CStr64 tempStr;

	if(!fRentalPeriodHours.isUndefined())
	{
		if(fRentalPeriodHours.getValue() > 48)
			tempStr.copyVarg("%d days", fRentalPeriodHours.getValue() / 24);
		else
			tempStr.copyVarg("%s hrs.", fRentalPeriodHours.c_str());
	}
	if(!fRentalWindowDays.isUndefined())
	{
		if(tempStr.hasLen())
			tempStr.concat(" / ");
		tempStr.concatVarg("%s days", fRentalWindowDays.c_str());
	}

	if(!tempStr.hasLen())
		tempStr.copy("n/a");
	return tempStr;
}

/******************************************************************************/

void ShowCost::readFromFiler(DataFilerPtr filerPtr)
{
	fShowCostType = ConvertStringToShowCostType(filerPtr->readString().c_str());
	fCostPtr = filerPtr->readObject(MoneyConstructor());
	fCostDisplay.copy(filerPtr->readString().c_str());
	fRentalWindowDays = filerPtr->readShort();
	fRentalPeriodHours = filerPtr->readShort();
}

/******************************************************************************/

void ShowCost::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(ConvertShowCostTypeToString(fShowCostType).c_str());
	filerPtr->writeObject(fCostPtr);
	filerPtr->writeString(fCostDisplay.c_str());
	fRentalWindowDays.writeToFiler(filerPtr);	//TODO: should try to support through writeShort
	fRentalPeriodHours.writeToFiler(filerPtr);	//TODO: should try to support through writeShort
}

/******************************************************************************/
/******************************************************************************/

void ShowCostVector::readFromFiler(DataFilerPtr filerPtr)
{
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
		push_back(ShowCost::newInstance(filerPtr));
}

/******************************************************************************/

void ShowCostVector::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ShowCostVector::writeToFiler", "not implemented");
	//ShowCostVector::const_iterator iter;

	//filerPtr->writeLong(size());
	//for(iter = begin(); iter != end(); ++iter)
	//	(*iter)->writeToFiler(filerPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
