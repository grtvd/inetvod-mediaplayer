/* TextControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

TextControl::TextControl(const ControlID& controlID, const ScreenID& screenID,
	const char* text) : Control(controlID, screenID)
{
	fText.copy(text);
	fFontPtr = MainApp::getThe()->getFont(gNormalWhiteFontID);

	fScrollable = false;
#if defined(USE_SCROLL_BAR)
	fShowScrollBar = false;
	fScrollBarWidth = 16;
#else
	fShowMoreIcons = false;
	fMoreIconHeight = 10;
#endif
	fLineSpaceHeight = 2;

	fLineHeight = 0;
	fTopLine = 0;
	fVisibleLines = 0;
}

/******************************************************************************/

ControlPtr TextControl::newInstance(const ControlID& controlID, const ScreenID& screenID,
	const Rect& rect, const char* text)
{
	ControlPtr controlPtr = Control::newInstance(new TextControl(controlID, screenID,
		text), rect);
	TextControlPtr textControlPtr = controlPtr;

	textControlPtr->init();

	return controlPtr;
}

/******************************************************************************/

void TextControl::init()
{
	fLineHeight = fFontPtr->getCharHeight() + fLineSpaceHeight;
	if(fLineHeight == 0)
		fLineHeight = 12;	// make sure we don't div by 0

	tStrWordWrapCalcPixelLines(fText.c_str(), fRect.getWidth(), fFontPtr, fLinesVector);
	fVisibleLines = fRect.getHeight() / fLineHeight;

#if defined(USE_SCROLL_BAR)
	fShowScrollBar = false;
	if(fScrollable && ((int)fLinesVector.size() > fVisibleLines))
	{
		tStrWordWrapCalcPixelLines(fText.c_str(), fRect.getWidth() - fScrollBarWidth, fFontPtr, fLinesVector);
	}
#else
	fShowMoreIcons = false;
	if(fScrollable && ((int)fLinesVector.size() > fVisibleLines))
	{
		int moreIconHeight = fMoreIconHeight;
		if(hasFocus())
			moreIconHeight += fMoreIconHeight;

		fShowMoreIcons = true;
		fVisibleLines = (fRect.getHeight() - moreIconHeight) / fLineHeight;
	}
#endif
}

/******************************************************************************/

void TextControl::setText(const char* text)
{
	fText.copy(text);
	init();
}

/******************************************************************************/

void TextControl::setFontID(const FontID& fontID)
{
	fFontPtr = MainApp::getThe()->getFont(fontID);
	init();
}

/******************************************************************************/

void TextControl::setVisibleLines(int visibleLines)
{
	if(visibleLines >= 1)
	{
		int lineHeight = fFontPtr->getCharHeight() + fLineSpaceHeight;
		fRect.setHeight(lineHeight * visibleLines);
		init();
	}
}

/******************************************************************************/

void TextControl::draw(bool showFocus)
{
	drawLines();
#if defined(USE_SCROLL_BAR)
	if(fShowScrollBar)
		drawScrollBar(showFocus);
#else
	if(fShowMoreIcons)
		drawMoreIcons(showFocus);
#endif
}

/******************************************************************************/
#if defined(USE_SCROLL_BAR)
void TextControl::drawScrollBar(bool showFocus) const
{
	if(!showFocus)
		return;

	Rect rect;

	rect = Rect(fRect.getWidth() - fScrollBarWidth, 0, fScrollBarWidth, fRect.getHeight());
	DrawRect(rect, gGrayColor);

	rect = Rect(fRect.getWidth() - fScrollBarWidth, 0, fScrollBarWidth, fScrollBarWidth);
	DrawRect(rect, gGreenColor);
}
#else

void TextControl::drawMoreIcons(bool showFocus) const
{
	if(!showFocus)
		return;

	int iconWidth = 20;
	Rect rect;

	rect = RectWH(0 + (fRect.getWidth() / 2) - (iconWidth / 2), 0, iconWidth, fMoreIconHeight);
	DrawUpTriangle(rect, (fTopLine > 0) ? gGreenColor : gGrayColor);

	rect = RectWH(0 + (fRect.getWidth() / 2) - (iconWidth / 2), fRect.getHeight() - fMoreIconHeight, iconWidth, fMoreIconHeight);
	DrawDownTriangle(rect, (fTopLine + fVisibleLines < (int)fLinesVector.size() - 1) ? gGreenColor : gGrayColor);
}

#endif
/******************************************************************************/

void TextControl::drawLines()
{
#if defined(USE_SCROLL_BAR)
	int moreIconHeight = 0;
	int lineWidth = fRect.getWidth() - (fShowScrollBar ? fScrollBarWidth : 0);
#else
	int moreIconHeight = (fShowMoreIcons ? fMoreIconHeight : 0);
	int lineWidth = fRect.getWidth();
#endif
	CStrVar lineStr;
	int drawLines;
	Rect rect;

	drawLines = (fLinesVector.size() - fTopLine);
	if (drawLines > fVisibleLines)
		drawLines = fVisibleLines;

	for(int i = 0; i < drawLines; i++)
	{
		rect = RectWH(0, moreIconHeight + (i * fLineHeight), lineWidth, fLineHeight);
		//DrawBorder2(rect, 1, gWhiteColor);

		lineStr = tStrWordWrapGetNextLine(fText.c_str(), fLinesVector, fTopLine + i);
		if(!fScrollable && (i == drawLines - 1) && ((int)fLinesVector.size() > fVisibleLines))
			lineStr.concat("...");
		DrawTextAligned(rect, ha_Left, va_Top, lineStr.c_str(), fFontPtr);
	}
}

/******************************************************************************/

bool TextControl::key(int /*key*/)
{
#if 0
	int itemCount = getItemCount();

	if(key == ek_Select)
	{
		getScreen()->onButton(fControlID);
		return true;
	}
	else if((key == ek_DownButton) || (key == ek_RightButton))
	{
		if(fFocusedItem < itemCount - 1)
			++fFocusedItem;

		if(fFocusedItem > fBottomItem)
			fTopItem += fFocusedItem - fBottomItem;

		return true;
	}

	if((key == ek_UpButton) || (key == ek_LeftButton))
	{
		if(fFocusedItem > 0)
			--fFocusedItem;

		if(fFocusedItem < fTopItem)
			fTopItem -= fTopItem - fFocusedItem;

		return true;
	}
#endif

	return false;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
