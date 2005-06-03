/* TextListControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "TextListControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

TextListControl::TextListControl(const ControlID& controlID,const ScreenID& screenID)
	: ListControl(controlID,screenID)
{
	fShowHeader = false;
	fHorzPadWidth = 10;
}

/******************************************************************************/

CStr64 TextListControl::getFocusedItemName() const
{
	if((fFocusedItem >= 0) && (fFocusedItem < (int)fItemVector.size()))
		return CStr64((fItemVector[fFocusedItem])->getName());

	return CStr64();
}

/******************************************************************************/

CStrVar TextListControl::getFocusedItemValue() const
{
	if((fFocusedItem >= 0) && (fFocusedItem < (int)fItemVector.size()))
		return CStrVar((fItemVector[fFocusedItem])->getValue());

	return CStrVar();
}

/******************************************************************************/

void TextListControl::drawItem(int item) const
{
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalWhiteFontID);
	Rect rect = RectWH(0, 0, fRect.getWidth(), getItemHeight(item));
	rect.inset(fHorzPadWidth,0);
	DrawTextAligned(rect, ha_Left, va_Middle, (fItemVector[item])->getValue(), fontPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
