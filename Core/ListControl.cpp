/* ListControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

ListControl::ListControl(const ControlID& controlID, const ScreenID& screenID) : Control(controlID, screenID)
{
	fShowHeader = true;
	fHeaderHeight = 24;
	fShowMoreIcons = true;
	fMoreIconHeight = 20;
	fMoreIconWidth = 28;
	fMoreIconPad = 2;
	fItemTopPadHeight = 2;
	fItemBottomPadHeight = 3;

	fTopItem = 0;
	fBottomItem = -1;
	fFocusedItem = -1;
	fFocusedUpIcon = false;
	fFocusedDownIcon = false;
}

/******************************************************************************/

void ListControl::recalcTopItemFromBottomItem()
{
	int totalItems = getItemCount();
	int remainingItemHeight = fRect.getHeight() - calcHeaderHeight() - calcMoreIconHeight();
	int itemHeight;

	if(totalItems == 0)
	{
		fTopItem = 0;
		fBottomItem = -1;
		return;
	}

	if(fBottomItem >= totalItems)
		fBottomItem = totalItems - 1;
	fTopItem = fBottomItem;

	for(int i = fBottomItem; i >= 0; i--)
	{
		itemHeight = getItemHeight(i);
		if (itemHeight + fItemTopPadHeight + fItemBottomPadHeight > remainingItemHeight)
			break;
		remainingItemHeight -= (itemHeight + fItemTopPadHeight + fItemBottomPadHeight);
		fTopItem = i;
	}
}

/******************************************************************************/

void ListControl::recalcBottomItemFromTopItem()
{
	int totalItems = getItemCount();
	int remainingItemHeight = fRect.getHeight() - calcHeaderHeight() - calcMoreIconHeight();
	int itemHeight;

	fBottomItem = -1;
	if(totalItems == 0)
	{
		fTopItem = 0;
		return;
	}

	if(fTopItem >= totalItems)
		fTopItem = totalItems - 1;

	for(int i = fTopItem; i < totalItems; i++)
	{
		itemHeight = getItemHeight(i);
		if (itemHeight + fItemTopPadHeight + fItemBottomPadHeight > remainingItemHeight)
			break;
		remainingItemHeight -= (itemHeight + fItemTopPadHeight + fItemBottomPadHeight);
		fBottomItem = i;
	}
}

/******************************************************************************/

void ListControl::setFocus(bool set)
{
	Control::setFocus(set);
	if(set && (fFocusedItem == -1))
		fFocusedItem = 0;
}

/******************************************************************************/

void ListControl::setFocusedItem(int focusedItem)
{
	if((focusedItem >= 0) && (focusedItem < getItemCount()))
	{
		fFocusedItem = focusedItem;

		if(fFocusedItem < fTopItem)
			fFocusedItem = fTopItem;
		recalcBottomItemFromTopItem();

		if(fFocusedItem > fBottomItem)
		{
			fBottomItem = fFocusedItem;
			recalcTopItemFromBottomItem();
		}
	}
}

/******************************************************************************/

void ListControl::draw(bool showFocus)
{
//DrawRect(Rect(0, 0, fRect.getWidth(), fRect.getHeight()), gBlackColor);

	if(fShowHeader)
		drawHeader(showFocus);
	drawItems(showFocus);
	if(fShowMoreIcons)
		drawMoreIcons(showFocus);
}

/******************************************************************************/

Rect ListControl::calcUpMoreIconRect() const
{
	return RectWH((fRect.getWidth() / 2) - fMoreIconWidth - 2,
		fRect.getHeight() - fMoreIconHeight, fMoreIconWidth, fMoreIconHeight);
}

/******************************************************************************/

Rect ListControl::calcDownMoreIconRect() const
{
	return RectWH((fRect.getWidth() / 2) + 2, fRect.getHeight() - fMoreIconHeight,
		fMoreIconWidth, fMoreIconHeight);
}

/******************************************************************************/

void ListControl::drawMoreIcons(bool showFocus) const
{
	if(!showFocus || !fShowMoreIcons)
		return;

	Rect rect = calcUpMoreIconRect();
	rect.inset(fFocusedBorderWidth + fMoreIconPad, fFocusedBorderWidth + fMoreIconPad);
	DrawUpTriangle(rect, hilightUpMoreIcon() ? gGreenColor : gGrayColor);
	rect.inset(-(fFocusedBorderWidth + fMoreIconPad), -(fFocusedBorderWidth + fMoreIconPad));
	DrawBorder2(rect, fFocusedBorderWidth, fFocusedUpIcon
		? gFocusedBorderColor : gUnfocusedBorderColor);

	rect = calcDownMoreIconRect();
	rect.inset(fFocusedBorderWidth + fMoreIconPad, fFocusedBorderWidth + fMoreIconPad);
	DrawDownTriangle(rect, hilightDownMoreIcon() ? gGreenColor : gGrayColor);
	rect.inset(-(fFocusedBorderWidth + fMoreIconPad), -(fFocusedBorderWidth + fMoreIconPad));
	DrawBorder2(rect, fFocusedBorderWidth, fFocusedDownIcon
		? gFocusedBorderColor : gUnfocusedBorderColor);
}

/******************************************************************************/

void ListControl::drawItems(bool showFocus)
{
	int drawCoordH;
	int drawCoordV;

	int itemHeight;
	Rect rect;

	recalcBottomItemFromTopItem();

	GetDrawCoordOffset(drawCoordH, drawCoordV);
	AdjustDrawCoordOffset(0, calcHeaderHeight());

	for(int i = fTopItem; i <= fBottomItem; i++)
	{
		itemHeight = getItemHeight(i);

		AdjustDrawCoordOffset(0, fItemTopPadHeight);
		rect = RectWH(0, 0, fRect.getWidth(), itemHeight);
		if (showFocus && hasFocus() && (fFocusedItem == i))
		{
			rect.inset(fFocusedBorderWidth, fFocusedBorderWidth);
			DrawRect(rect, gFocusedBackgroundColor);
			rect.inset(-fFocusedBorderWidth, -fFocusedBorderWidth);
		}
		drawItem(i);
		DrawBorder2(rect, fFocusedBorderWidth, (showFocus && (fFocusedItem == i))
			? gFocusedBorderColor : gUnfocusedBorderColor);
		AdjustDrawCoordOffset(0, itemHeight + fItemBottomPadHeight);
	}

	SetDrawCoordOffset(drawCoordH, drawCoordV);
}

/******************************************************************************/
#if 0

void ListControl::drawItem(int item) const
{
	int itemHeight = getItemHeight(item);
	Rect rect = Rect(0, 0, fRect.getWidth(), itemHeight);

	DrawRect(rect, ((item % 2) == 0) ? gBlueColor : gOrangeColor);
}

#endif
/******************************************************************************/

bool ListControl::key(int key)
{
	if(key == ek_Select)
	{
		getScreen()->onButton(fControlID);
		return true;
	}
	
	if((key == ek_DownButton) || (key == ek_RightButton))
	{
		int itemCount = getItemCount();

		if(fFocusedItem < itemCount - 1)
			++fFocusedItem;

		if(fFocusedItem > fBottomItem)
		{
			fBottomItem = fFocusedItem;
			recalcTopItemFromBottomItem();
		}

		return true;
	}

	if((key == ek_UpButton) || (key == ek_LeftButton))
	{
		if(fFocusedItem > 0)
			--fFocusedItem;

		if(fFocusedItem < fTopItem)
		{
			fTopItem = fFocusedItem;
			recalcBottomItemFromTopItem();
		}

		return true;
	}
	
	if(key == ek_PageDown)
	{
		int itemCount = getItemCount();
		int pageCount = (fBottomItem - fTopItem + 1);

		fBottomItem += pageCount;
		if(fBottomItem >= itemCount)
			fBottomItem = itemCount - 1;
		fFocusedItem += pageCount;
		if(fFocusedItem >= itemCount)
			fFocusedItem = itemCount - 1;
		recalcTopItemFromBottomItem();
		return true;
	}

	if(key == ek_PageUp)
	{
		int pageCount = (fBottomItem - fTopItem + 1);

		fTopItem -= pageCount;
		if(fTopItem < 0)
			fTopItem = 0;
		fFocusedItem -= pageCount;
		if(fFocusedItem < 0)
			fFocusedItem = 0;
		recalcBottomItemFromTopItem();
		return true;
	}

	return false;
}

/******************************************************************************/

bool ListControl::mouseClick(bool leftButton, bool buttonDown, int x, int y)
{
	if(buttonDown || !leftButton)
		return false;

	Rect rect;
	int itemHeight;
	int top = calcHeaderHeight();
	Point pt = Point(x, y);

	// check items
	for(int i = fTopItem; i <= fBottomItem; i++)
	{
		itemHeight = getItemHeight(i);

		top += fItemTopPadHeight;
		rect = RectWH(0, top, fRect.getWidth(), itemHeight);
		if(rect.ptIn(pt))
		{
			getScreen()->onButton(fControlID);
			return true;
		}

		top += itemHeight + fItemBottomPadHeight;
	}

	// check more icons
	rect = calcUpMoreIconRect();
	if(rect.ptIn(pt) && hilightUpMoreIcon())
	{
		if(fFocusedUpIcon)
		{
			key(ek_PageUp);
			MainApp::getThe()->requestDraw();
		}

		return true;
	}

	rect = calcDownMoreIconRect();
	if(rect.ptIn(pt) && hilightDownMoreIcon())
	{
		if(fFocusedDownIcon)
		{
			key(ek_PageDown);
			MainApp::getThe()->requestDraw();
		}

		return true;
	}

	return false;
}

/******************************************************************************/

void ListControl::mouseMove(bool buttonDown, int x, int y)
{
	if(buttonDown)
		return;

	Rect rect;
	int itemHeight;
	int top = calcHeaderHeight();
	Point pt = Point(x, y);

	// check items
	for(int i = fTopItem; i <= fBottomItem; i++)
	{
		itemHeight = getItemHeight(i);

		top += fItemTopPadHeight;
		rect = RectWH(0, top, fRect.getWidth(), itemHeight);
		if(rect.ptIn(pt))
		{
			setFocusedItem(i);
			fFocusedUpIcon = false;
			fFocusedDownIcon = false;
			MainApp::getThe()->requestDraw();
			return;
		}

		top += itemHeight + fItemBottomPadHeight;
	}

	// check more icons
	rect = calcUpMoreIconRect();
	if(rect.ptIn(pt))
	{
		if(!fFocusedUpIcon && hilightUpMoreIcon())
		{
			fFocusedUpIcon = true;
			MainApp::getThe()->requestDraw();
		}
	}
	else if(fFocusedUpIcon)
	{
		fFocusedUpIcon = false;
		MainApp::getThe()->requestDraw();
	}

	rect = calcDownMoreIconRect();
	if(rect.ptIn(pt))
	{
		if(!fFocusedDownIcon && hilightDownMoreIcon())
		{
			fFocusedDownIcon = true;
			MainApp::getThe()->requestDraw();
		}
	}
	else if(fFocusedDownIcon)
	{
		fFocusedDownIcon = false;
		MainApp::getThe()->requestDraw();
	}
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
