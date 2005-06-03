/* ButtonControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

ButtonControl::ButtonControl(const ControlID& controlID, const ScreenID& screenID,
	const char* text) : Control(controlID,screenID)
{
	fText.copy(text);
	fHorzAlign = ha_Center;
	fVertAlign = va_Middle;
	fHorzPadWidth = 10;
}

/******************************************************************************/

void ButtonControl::draw(bool showFocus)
{
	Rect rect = Rect(0,0,fRect.getWidth(),fRect.getHeight());

	if(showFocus && hasFocus())
	{
		rect.inset(fFocusedBorderWidth, fFocusedBorderWidth);
		DrawRect(rect, gFocusedBackgroundColor);
		rect.inset(-fFocusedBorderWidth, -fFocusedBorderWidth);
		DrawBorder2(rect, fFocusedBorderWidth, gFocusedBorderColor);
	}
	else
	{
		DrawBorder2(rect, fFocusedBorderWidth, gUnfocusedBorderColor);
	}

	rect.inset(fHorzPadWidth,0);
	DrawTextAligned(rect, fHorzAlign, fVertAlign, fText.c_str(), gNormalWhiteFontID);
}

/******************************************************************************/

bool ButtonControl::key(int key)
{
	if(key == ek_Select)
	{
		getScreen()->onButton(fControlID);
		return true;
	}

	return false;
}

/******************************************************************************/

bool ButtonControl::mouseClick(bool leftButton, bool buttonDown, int x, int y)
{
	if(hasFocus() && leftButton && !buttonDown)
	{
		getScreen()->onButton(fControlID);
		return true;
	}

	return false;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
