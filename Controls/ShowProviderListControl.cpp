/* ShowProviderListControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ShowProviderListControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

ShowProviderPtr ShowProviderListControl::getFocusedItemValue() const
{
	if((fFocusedItem >= 0) && (fFocusedItem < (int)fShowProviderVector.size()))
		return fShowProviderVector[fFocusedItem];

	return ShowProviderPtr();
}

/******************************************************************************/

void ShowProviderListControl::drawHeader(bool /*showFocus*/) const
{
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalYellowFontID);

	DrawTextAligned(RectWH(10, 0, fRect.getWidth() - 80, fHeaderHeight), ha_Left, va_Middle,
		"Provider", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 60, 0, 50, fHeaderHeight), ha_Left, va_Middle,
		"Price", fontPtr);
}

/******************************************************************************/

int ShowProviderListControl::getItemCount() const
{
	return fShowProviderVector.size();
}

/******************************************************************************/

void ShowProviderListControl::drawItem(int item) const
{
	ShowProviderPtr showProviderPtr = fShowProviderVector[item];
	int itemHeight = getItemHeight(item);
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalWhiteFontID);

	DrawTextAligned(RectWH(10, 0, fRect.getWidth() - 80, itemHeight), ha_Left, va_Middle,
		MainApp::getThe()->getSession()->getProviderName(showProviderPtr->getProviderID()),
		fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 60, 0, 50, itemHeight), ha_Left, va_Middle,
		showProviderPtr->getCost()->getCostDisplay(), fontPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
