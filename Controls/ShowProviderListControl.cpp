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

void ShowProviderListControl::initShowProviderItemList(const ShowProviderVector& showProviderVector)
{
	ShowProviderVector::const_iterator showProvderIter;
	ShowProviderPtr showProviderPtr;
	ShowCostVector showCostVector;
	ShowCostVector::const_iterator showCostIter;

	fShowProviderItemVector.clear();

	//filerPtr->writeLong(size());
	for(showProvderIter = showProviderVector.begin();
		showProvderIter != showProviderVector.end(); ++showProvderIter)
	{
		showProviderPtr = *showProvderIter;
		showProviderPtr->getShowCostVector(showCostVector);
		for(showCostIter = showCostVector.begin(); showCostIter != showCostVector.end();
			++showCostIter)
		{
			fShowProviderItemVector.push_back(ShowProviderItem::newInstance(
				showProviderPtr->getProviderID(), *showCostIter));
		}
	}
}

/******************************************************************************/

void ShowProviderListControl::setShowProviderVector(const ShowProviderVector& showProviderVector)
{
	initShowProviderItemList(showProviderVector);
}

/******************************************************************************/

ShowProviderItemPtr ShowProviderListControl::getFocusedItemValue() const
{
	if((fFocusedItem >= 0) && (fFocusedItem < (int)fShowProviderItemVector.size()))
		return fShowProviderItemVector[fFocusedItem];

	return ShowProviderItemPtr();
}

/******************************************************************************/

void ShowProviderListControl::drawHeader(bool /*showFocus*/) const
{
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalYellowFontID);

	DrawTextAligned(RectWH(10, 0, fRect.getWidth() - 280, fHeaderHeight), ha_Left, va_Middle,
		"Provider", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 260, 0, 175, fHeaderHeight), ha_Left, va_Middle,
		"Rental", fontPtr);
	DrawTextAligned(RectWH(fRect.getWidth() - 75, 0, 65, fHeaderHeight), ha_Left, va_Middle,
		"Price", fontPtr);
}

/******************************************************************************/

int ShowProviderListControl::getItemCount() const
{
	return fShowProviderItemVector.size();
}

/******************************************************************************/

void ShowProviderListControl::drawItem(int item) const
{
	ShowProviderItemPtr showProviderItemPtr = fShowProviderItemVector[item];
	int itemHeight = getItemHeight(item);
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalWhiteFontID);

	DrawTextAligned(RectWH(10, 0, fRect.getWidth() - 280, itemHeight), ha_Left, va_Middle,
		showProviderItemPtr->getProvider()->getName(), fontPtr);

	DrawTextAligned(RectWH(fRect.getWidth() - 260, 0, 175, itemHeight), ha_Left, va_Middle,
		showProviderItemPtr->getShowCost()->formatRental().c_str(), fontPtr);

	DrawTextAligned(RectWH(fRect.getWidth() - 75, 0, 65, itemHeight), ha_Left, va_Middle,
		showProviderItemPtr->getShowCost()->getCostDisplay(), fontPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
