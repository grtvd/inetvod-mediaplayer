/* SelectControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

SelectControl::SelectControl(const ControlID& controlID, const ScreenID& screenID)
 : Control(controlID, screenID)
{
	fHorzPadWidth = 20;
	fChangeIconWidth = 10;
	fChangeIconPadWidth = 2;
	fChangeIconPadHeight = 4;
	fMoreIconHeight = 20;
	fMoreIconWidth = 28;
	fMoreIconPad = 2;
	fCurItem = 0;
	fFocusedUpIcon = false;
	fFocusedDownIcon = false;
}

/******************************************************************************/

void SelectControl::setCurItem(int curItem)
{
	if((curItem < 0) || (curItem >= (int)fItemVector.size()))
		throw ASIException("SelectControl::setCurItem", "Invalid curItem(%d)", curItem);

	fCurItem = curItem;
}

/******************************************************************************/

void SelectControl::draw(bool showFocus)
{
	Rect rect = Rect(0, 0, fRect.getWidth() - 2 - fMoreIconWidth, fRect.getHeight());

	if(showFocus && hasFocus())
	{
		rect.inset(fFocusedBorderWidth, fFocusedBorderWidth);
		DrawRect(rect, gFocusedBackgroundColor);
		drawChangeIcons(showFocus);
		rect.inset(-fFocusedBorderWidth, -fFocusedBorderWidth);
		DrawBorder2(rect, fFocusedBorderWidth, gFocusedBorderColor);
	}
	else
	{
		DrawBorder2(rect, fFocusedBorderWidth, gUnfocusedBorderColor);
	}

	if(fCurItem < (int)fItemVector.size())
	{
		rect.inset(fHorzPadWidth, 0);
		DrawTextAligned(rect, ha_Left, va_Middle, fItemVector[fCurItem].c_str(), gNormalWhiteFontID);
	}
}

/******************************************************************************/

Rect SelectControl::calcUpMoreIconRect() const
{
	return RectWH(fRect.getWidth() - fMoreIconWidth,
		(fRect.getHeight() / 2) - fMoreIconHeight, fMoreIconWidth, fMoreIconHeight);
}

/******************************************************************************/

Rect SelectControl::calcDownMoreIconRect() const
{
	return RectWH(fRect.getWidth() - fMoreIconWidth, (fRect.getHeight() / 2),
		fMoreIconWidth, fMoreIconHeight);
}

/******************************************************************************/

void SelectControl::drawChangeIcons(bool showFocus) const
{
	if(!showFocus || !hasFocus())
		return;

/*
	rect = RectWH(fFocusedBorderWidth, fFocusedBorderWidth, fChangeIconWidth,
		fRect.getHeight() - (fFocusedBorderWidth * 2));
	rect.inset(fChangeIconPadWidth, fChangeIconPadHeight);
	DrawLeftTriangle(rect, (fCurItem > 0) ? gFocusedBorderColor : gGrayColor);

	rect = RectWH(fRect.getWidth() - fFocusedBorderWidth - fChangeIconWidth,
		fFocusedBorderWidth, fChangeIconWidth, fRect.getHeight() - (fFocusedBorderWidth * 2));
	rect.inset(fChangeIconPadWidth, fChangeIconPadHeight);
	DrawRightTriangle(rect, (fCurItem < (int)fItemVector.size() - 1) ? gFocusedBorderColor : gGrayColor);
*/

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

bool SelectControl::key(int key)
{
	if(key == ek_Select)
	{
		getScreen()->onButton(fControlID);
		return true;
	}
	else if(key == ek_NextValue)
	{
		if (fCurItem < (int)fItemVector.size() - 1)
		{
			++fCurItem;
			return true;
		}
	}
	else if(key == ek_PrevValue)
	{
		if (fCurItem > 0)
		{
			--fCurItem;
			return true;
		}
	}
	
	return false;
}

/******************************************************************************/

bool SelectControl::mouseClick(bool leftButton, bool buttonDown, int x, int y)
{
	if(buttonDown || !leftButton)
		return false;

	Rect rect;
	Point pt = Point(x, y);

	rect = Rect(0, 0, fRect.getWidth() - 2 - fMoreIconWidth, fRect.getHeight());
	if(rect.ptIn(pt))
	{
		if (fCurItem < (int)fItemVector.size() - 1)
			++fCurItem;
		else
			fCurItem = 0;
		MainApp::getThe()->requestDraw();

		return true;
	}

	// check more icons
	rect = calcUpMoreIconRect();
	if(rect.ptIn(pt) && hilightUpMoreIcon())
	{
		if(fFocusedUpIcon)
		{
			key(ek_PrevValue);
			MainApp::getThe()->requestDraw();
		}

		return true;
	}

	rect = calcDownMoreIconRect();
	if(rect.ptIn(pt) && hilightDownMoreIcon())
	{
		if(fFocusedDownIcon)
		{
			key(ek_NextValue);
			MainApp::getThe()->requestDraw();
		}

		return true;
	}

	return false;
}

/******************************************************************************/

void SelectControl::mouseMove(bool buttonDown, int x, int y)
{
	if(buttonDown)
		return;

	Rect rect;
	Point pt = Point(x, y);

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
