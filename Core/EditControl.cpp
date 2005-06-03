/* EditControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

EditControl::EditControl(const ControlID& controlID, const ScreenID& screenID) : Control(controlID, screenID)
{
	FontPtr fontPtr = MainApp::getThe()->getFont(gNormalWhiteFontID);

	fType = ect_AlphaNumeric;
	memset(fText, 0, sizeof(fText));
	fFirstPos = 0;
	fCurPos = -1;
	fCharWidth = fontPtr->getMaxCharWidth();
	fMaxLength = 25;
	fAutoButton = false;
}

/******************************************************************************/

ControlPtr EditControl::newInstance(const ControlID& controlID, const ScreenID& screenID,
	const Rect& rect)
{
	ControlPtr controlPtr = Control::newInstance(new EditControl(controlID, screenID), rect);
	EditControlPtr editControlPtr = controlPtr;

	editControlPtr->init();

	return controlPtr;
}

/******************************************************************************/

void EditControl::init()
{
	fTextRect = RectWH(0, 0, fRect.getWidth(), fRect.getHeight());
	fTextRect.inset(fFocusedBorderWidth + 2, fFocusedBorderWidth + 2);

	fillValidCharVector();
}

/******************************************************************************/

void EditControl::fillValidCharVector()
{
	char ch;

	fValidCharVector.clear();
	switch(fType)
	{
		case ect_AlphaNumeric:
			for(ch = 'A'; ch <= 'Z'; ++ch)
			{
				fValidCharVector.push_back(ch);
				fValidCharVector.push_back(tolower(ch));
			}
			for(ch = '0'; ch <= '9'; ++ch)
				fValidCharVector.push_back(ch);
			fValidCharVector.push_back(' ');
			break;
		case ect_UpperAlphaNumeric:
			for(ch = 'A'; ch <= 'Z'; ++ch)
				fValidCharVector.push_back(ch);
			for(ch = '0'; ch <= '9'; ++ch)
				fValidCharVector.push_back(ch);
			fValidCharVector.push_back(' ');
			break;
		case ect_Numeric:
			for(ch = '0'; ch <= '9'; ++ch)
				fValidCharVector.push_back(ch);
			break;
		default:
			throw ASIException("EditControl::fillValidCharVector", "Invalid fType(%d)", fType);
	}
}

/******************************************************************************/

void EditControl::setFocus(bool set)
{
	Control::setFocus(set);

	if(set && (fCurPos == -1))
	{
		int viewableChars = fTextRect.getWidth() / fCharWidth;
		int len = strlen(fText);

		if((viewableChars == fMaxLength) && (len == fMaxLength))
			fCurPos = len - 1;
		else
			fCurPos = len;
		checkPositions();
	}

	if(!set)
	{
		fCurPos = -1;
		fFirstPos = 0;
	}
}

/******************************************************************************/

void EditControl::draw(bool showFocus)
{
	DrawRect(fTextRect, gBlackColor);
	drawChars(showFocus);
	DrawBorder2(RectWH(0, 0, fRect.getWidth(), fRect.getHeight()), fFocusedBorderWidth,
		(showFocus && hasFocus()) ? gFocusedBorderColor : gUnfocusedBorderColor);
	drawChangeIcons(showFocus);
}

/******************************************************************************/

void EditControl::checkPositions()
{
	int viewableChars = fTextRect.getWidth() / fCharWidth;
	int len = strlen(fText);

	if(fCurPos < 0)
		fCurPos = 0;
	else if(fCurPos > len)
		fCurPos = len;

	if(fCurPos < fFirstPos)
		fFirstPos = fCurPos;
	else if(fFirstPos < fCurPos - viewableChars + 1)
		fFirstPos = fCurPos - viewableChars + 1;
}

/******************************************************************************/

void EditControl::drawChangeIcons(bool showFocus) const
{
	if(!showFocus || !hasFocus())
		return;

	int iconHeight = 10;
	int pos = fCurPos - fFirstPos;
	Rect rect;

	rect = RectWH(fTextRect.left + (fCharWidth * pos), fTextRect.top - iconHeight, fCharWidth, iconHeight);
	DrawUpTriangle(rect, gFocusedBackgroundColor);

	rect = RectWH(fTextRect.left + (fCharWidth * pos), fTextRect.bottom, fCharWidth, iconHeight);
	DrawDownTriangle(rect, gFocusedBackgroundColor);
}

/******************************************************************************/

void EditControl::drawChars(bool showFocus)
{
	int textLen = strlen(fText);
	int numChars = textLen + 1;
	int viewableChars = fTextRect.getWidth() / fCharWidth;
	char drawChar[2];
	Rect rect;
	bool focusedChar;

	drawChar[1] = '\0';
	if(numChars - fFirstPos > viewableChars)
		numChars = viewableChars + fFirstPos;

	for(int i = 0; i < numChars; i++)
	{
		rect = RectWH(fTextRect.left + (i * fCharWidth), fTextRect.top, fCharWidth,
			fTextRect.getHeight());

		focusedChar = (showFocus && hasFocus() && (i + fFirstPos == fCurPos));
		if (focusedChar)
			DrawRect(rect, gFocusedBorderColor);

		if(i + fFirstPos < textLen)
		{
			drawChar[0] = fText[i + fFirstPos];
			DrawTextAligned(rect, ha_Center, va_Middle, drawChar,
				focusedChar ? gNormalBlackFontID : gNormalWhiteFontID);
		}
	}
}

/******************************************************************************/

bool EditControl::key(int key)
{
	if(key == ek_Select)
	{
		getScreen()->onButton(fControlID);
		return true;
	}
	else if(key == ek_NextValue)
	{
		if(fCurPos >= (int)strlen(fText))
		{
			tStrCat(fText, sizeof(fText), " ");
			fCurPos = strlen(fText) - 1;
			fText[fCurPos] = *fValidCharVector.begin();
		}
		else
		{
			std::vector<char>::const_iterator pos;
			char curValue = fText[fCurPos];

			pos = find(fValidCharVector.begin(), fValidCharVector.end(), curValue);
			if((pos != fValidCharVector.end()) && (pos + 1 != fValidCharVector.end()))
				fText[fCurPos] = *(pos + 1);
			else
				fText[fCurPos] = *fValidCharVector.begin();
		}
		checkPositions();

		return true;
	}
	else if(key == ek_PrevValue)
	{
		if(fCurPos >= (int)strlen(fText))
		{
			tStrCat(fText, sizeof(fText), " ");
			fCurPos = strlen(fText) - 1;
			fText[fCurPos] = *(fValidCharVector.end() - 1);
		}
		else
		{
			std::vector<char>::const_iterator pos;
			char curValue = fText[fCurPos];

			pos = find(fValidCharVector.begin(), fValidCharVector.end(), curValue);
			if((pos != fValidCharVector.end()) && (pos != fValidCharVector.begin()))
				fText[fCurPos] = *(pos - 1);
			else
				fText[fCurPos] = *(fValidCharVector.end() - 1);
		}
		checkPositions();

		return true;
	}
	else if(key == ek_RightButton)
	{
		if(fCurPos < fMaxLength - 1)
		{
			if(fCurPos < (int)strlen(fText))
			{
				++fCurPos;
				checkPositions();
				return true;
			}
			else if(!tStrHasLen(fText) || (fText[strlen(fText) - 1] != ' '))
			{
				std::vector<char>::const_iterator pos;

				// see if spaces are supported, add a space char
				pos = find(fValidCharVector.begin(), fValidCharVector.end(), ' ');
				if(pos != fValidCharVector.end())
				{
					tStrCat(fText, sizeof(fText), " ");
					fCurPos = strlen(fText);
					checkPositions();
					return true;
				}
			}
		}
	}
	else if(key == ek_LeftButton)
	{
		if(fCurPos > 0)
		{
			if(fCurPos < (int)strlen(fText))
				fText[fCurPos] = '\0';

			--fCurPos;
			checkPositions();
			return true;
		}
		else if (fCurPos == 0)
		{
			if(fText[fCurPos] != '\0')
			{
				fText[fCurPos] = '\0';
				return true;
			}
		}
	}
	else if((key == ek_Back) || (key == ek_UpButton) || (key == ek_DownButton))
	{
		// skip
	}
	else	// could be alpha or numberic chars (from keyboard or remote control)
	{
		std::vector<char>::const_iterator pos;

		// force upper case
		if ((key >= 'a') && (key <= 'z'))
			key -= ('a' - 'A');

		pos = find(fValidCharVector.begin(), fValidCharVector.end(), key);
		if(pos != fValidCharVector.end())
		{
			if(fCurPos >= (int)strlen(fText))
			{
				tStrCat(fText, sizeof(fText), " ");
				fCurPos = strlen(fText) - 1;
			}
			fText[fCurPos] = key;

			if(fCurPos < (int)strlen(fText))
				if(fCurPos < fMaxLength - 1)
					++fCurPos;
			checkPositions();

			if (fAutoButton && (strlen(fText) == fMaxLength))
				getScreen()->onButton(fControlID);

			return true;
		}
	}
	
	return false;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
