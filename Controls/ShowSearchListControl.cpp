/* ShowSearchListControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ShowSearchListControl.h"

namespace asi
{

const int ShowSearchListControl::fItemLine2Height = 20;

/******************************************************************************/
/******************************************************************************/

ShowSearchPtr ShowSearchListControl::getFocusedItemValue() const
{
	if((fFocusedItem >= 0) && (fFocusedItem < (int)fShowSearchVector.size()))
		return fShowSearchVector[fFocusedItem];

	return ShowSearchPtr();
}

/******************************************************************************/

void ShowSearchListControl::drawHeader(bool /*showFocus*/) const
{
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalYellowFontID);

	DrawTextAligned(RectWH(10, 0, fRect.getWidth() - 295, fHeaderHeight), ha_Left, va_Middle,
		"Show", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 280, 0, 55, fHeaderHeight), ha_Left, va_Middle,
		"Date", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 220, 0, 140, fHeaderHeight), ha_Left, va_Middle,
		"Provider", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 75, 0, 65, fHeaderHeight), ha_Left, va_Middle,
		"Price", fontPtr);
}

/******************************************************************************/

int ShowSearchListControl::getItemCount() const
{
	return fShowSearchVector.size();
}

/******************************************************************************/

int ShowSearchListControl::getItemHeight(int item) const
{
	ShowSearchPtr showSearchPtr = fShowSearchVector[item];
	int itemHeight = ListControl::getItemHeight(item);

	if(tStrHasLen(showSearchPtr->getEpisodeName()))
		itemHeight += fItemLine2Height;

	return itemHeight;
}

/******************************************************************************/

void ShowSearchListControl::drawItem(int item) const
{
	ShowSearchPtr showSearchPtr = fShowSearchVector[item];
	ShowProviderVector showProviderVector;
	ShowProviderPtr showProviderPtr;
	ShowCostVector showCostVector;
	int itemLine1Height = ListControl::getItemHeight(item);
	int itemHeight = getItemHeight(item);
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalWhiteFontID);
	FontPtr smallFontPtr = MainApp::getThe()->getFont(gSmallWhiteFontID);
	CStr32 date;
	CStr64 providerName;
	CStr32 cost;

	date.clear();
	if(!showSearchPtr->getReleasedOn().isUndefined())
	{
		TTimeSpan timeSpan = TDate::getSystemDate().compare(showSearchPtr->getReleasedOn());

		if(timeSpan.getTotalDays() == 0.0)
			date.copy("Today");
		else if(timeSpan.getTotalDays() <= 7.0)
			date.copy(showSearchPtr->getReleasedOn().getDayOfWeek().c_str(dwf_Sun));
		else if(timeSpan.getTotalDays() <= 365.0)
			date.copy(showSearchPtr->getReleasedOn().c_str(dtf_M_D));
		else
			date.copy(showSearchPtr->getReleasedOn().c_str(dtf_YYYY));
	}
	else if(!showSearchPtr->getReleasedYear().isUndefined())
		date.copy(showSearchPtr->getReleasedYear().c_str());

	showSearchPtr->getShowProviderVector(showProviderVector);
	showProviderPtr = showProviderVector[0];
	providerName.copy(MainApp::getThe()->getSession()->getProviderName(showProviderPtr->getProviderID()));
	showProviderPtr->getShowCostVector(showCostVector);
	cost.copy(showCostVector[0]->getCostDisplay());
	if((showProviderVector.size() > 1) || (showCostVector.size() > 1))
		cost.copyVarg("*%s",CStr32(cost.c_str()).c_str());

	DrawTextAligned(RectWH(10, 0, fRect.getWidth() - 295, itemLine1Height), ha_Left, va_Middle,
		showSearchPtr->getName(), fontPtr);
	if(tStrHasLen(showSearchPtr->getEpisodeName()))
		DrawTextAligned(RectWH(10, itemLine1Height - 5, fRect.getWidth() - 20, fItemLine2Height), ha_Left, va_Middle,
			showSearchPtr->getEpisodeName(), smallFontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 280, 0, 55, itemLine1Height), ha_Left, va_Middle,
		date.c_str(), fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 220, 0, 140, itemLine1Height), ha_Left, va_Middle,
		providerName.c_str(), fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 75, 0, 65, itemLine1Height), ha_Left, va_Middle,
		cost.c_str(), fontPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
