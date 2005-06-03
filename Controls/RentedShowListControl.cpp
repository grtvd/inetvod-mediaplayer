/* RentedShowListControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentedShowListControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

void RentedShowListControl::setRentedShowSearchVector(const RentedShowSearchVector& rentedShowSearchVector)
{
	fRentedShowSearchVector.copy(rentedShowSearchVector);

	if(fFocusedItem >= (int)fRentedShowSearchVector.size())
		fFocusedItem = fRentedShowSearchVector.size() - 1;

	setFocusedItem(fFocusedItem);
}

/******************************************************************************/

RentedShowSearchPtr RentedShowListControl::getFocusedItemValue() const
{
	if((fFocusedItem >= 0) && (fFocusedItem < (int)fRentedShowSearchVector.size()))
		return fRentedShowSearchVector[fFocusedItem];

	return RentedShowSearchPtr();
}

/******************************************************************************/

void RentedShowListControl::drawHeader(bool /*showFocus*/) const
{
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalYellowFontID);

	DrawTextAligned(RectWH(10, 0, fRect.getWidth() - 250, fHeaderHeight), ha_Left, va_Middle,
		"Show", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 255, 0, 140, fHeaderHeight), ha_Left, va_Middle,
		"Provider", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 110, 0, 100, fHeaderHeight), ha_Left, va_Middle,
		"Until", fontPtr);
}

/******************************************************************************/

int RentedShowListControl::getItemCount() const
{
	return fRentedShowSearchVector.size();
}

/******************************************************************************/

void RentedShowListControl::drawItem(int item) const
{
	RentedShowSearchPtr rentedShowSearchPtr = fRentedShowSearchVector[item];
	int itemHeight = getItemHeight(item);
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalWhiteFontID);
	CStr32 expires;
	TTimeSpan timeSpan = rentedShowSearchPtr->getAvailableUntil().compare(TDateTime::getSystemDateTime());

	if(rentedShowSearchPtr->getAvailableUntil().isUndefined())
	{
	}
	else if(timeSpan.getTotalDays() < 0.0)
		expires.copy("Expired");
	else if(timeSpan.getTotalDays() == 0.0)
	{
		expires.copy(rentedShowSearchPtr->getAvailableUntil().c_str(dtf_H_MM_AM));
	}
	else if((timeSpan.getTotalDays() <= 7.0))
	{
		expires.copy(rentedShowSearchPtr->getAvailableUntil().getDayOfWeek().c_str(dwf_Sun));
		expires.concat(" ");
		expires.concat(rentedShowSearchPtr->getAvailableUntil().c_str(dtf_H_AM));
	}
	else
		expires.copy(rentedShowSearchPtr->getAvailableUntil().c_str(dtf_M_D));

	DrawTextAligned(RectWH(10, 0, fRect.getWidth() - 250, itemHeight), ha_Left, va_Middle,
		rentedShowSearchPtr->getName(), fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 255, 0, 140, itemHeight), ha_Left, va_Middle,
		MainApp::getThe()->getSession()->getProviderName(rentedShowSearchPtr->getProviderID()),
		fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 110, 0, 100, itemHeight), ha_Left, va_Middle,
		expires.c_str(), fontPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
