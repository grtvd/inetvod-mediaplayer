/* LabelControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

LabelControl::LabelControl(const ControlID& controlID, const ScreenID& screenID,
	const char* text) : Control(controlID, screenID)
{
	fText.copy(text);
	fFontPtr = MainApp::getThe()->getFont(gNormalWhiteFontID);

	fHorzAlign = ha_Left;
	fVertAlign = va_Middle;
}

/******************************************************************************/

ControlPtr LabelControl::newInstance(const ControlID& controlID, const ScreenID& screenID,
	const Rect& rect, const char* text)
{
	return Control::newInstance(new LabelControl(controlID, screenID, text), rect);
}

/******************************************************************************/

void LabelControl::setFontID(const FontID& fontID)
{
	fFontPtr = MainApp::getThe()->getFont(fontID);
}

/******************************************************************************/

void LabelControl::draw(bool /*showFocus*/)
{
	DrawTextAligned(Rect(0, 0, fRect.getWidth(), fRect.getHeight()), fHorzAlign, fVertAlign,
		fText.c_str(), fFontPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
