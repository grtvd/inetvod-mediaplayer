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

	DrawTextAligned(RectWH(10, 0, fRect.getWidth() - 275, fHeaderHeight), ha_Left, va_Middle,
		"Show", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 260, 0, 50, fHeaderHeight), ha_Left, va_Middle,
		"Date", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 205, 0, 140, fHeaderHeight), ha_Left, va_Middle,
		"Provider", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 60, 0, 50, fHeaderHeight), ha_Left, va_Middle,
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
	int itemLine1Height = ListControl::getItemHeight(item);
	int itemHeight = getItemHeight(item);
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalWhiteFontID);
	FontPtr smallFontPtr = MainApp::getThe()->getFont(gSmallWhiteFontID);
	CStr32 date;
	CStr64 providerName;
	CStr32 cost;

	date.copy(showSearchPtr->getReleasedYear().c_str());

	showSearchPtr->getShowProviderVector(showProviderVector);
	if(showProviderVector.size() == 1)
	{
		showProviderPtr = showProviderVector[0];

		providerName.copy(MainApp::getThe()->getSession()->getProviderName(showProviderPtr->getProviderID()));
		cost.copy(showProviderPtr->getCost()->getDescription());
	}
	else
		providerName.copy("(multiple)");

	DrawTextAligned(RectWH(10, 0, fRect.getWidth() - 275, itemLine1Height), ha_Left, va_Middle,
		showSearchPtr->getName(), fontPtr);
	if(tStrHasLen(showSearchPtr->getEpisodeName()))
		DrawTextAligned(RectWH(10, itemLine1Height - 5, fRect.getWidth() - 20, fItemLine2Height), ha_Left, va_Middle,
			showSearchPtr->getEpisodeName(), smallFontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 260, 0, 50, itemLine1Height), ha_Left, va_Middle,
		date.c_str(), fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 205, 0, 140, itemLine1Height), ha_Left, va_Middle,
		providerName.c_str(), fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 60, 0, 50, itemLine1Height), ha_Left, va_Middle,
		cost.c_str(), fontPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
