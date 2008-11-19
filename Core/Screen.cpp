/* Screen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/

Screen::Screen(const ScreenID& screenID) : fContainerControl(ControlID("ContainerID"), screenID)
{
	int horzSlop = 15;	// Space on left and right
	int vertSlop = 15;	// Space on top and bottom

	// init values
	fScreenID = screenID;

	fIsFullScreen = true;
	#if defined(TITLE_ONE)
	fBorderWidth = 5;
	fTitleHeight = 24;	
	fTitlePadWidth = 10;
	#elif defined(TITLE_TWO)
	fBorderWidth = 3;
	fTitleHeight = 48;	
	fTitlePadWidth = 5;
	#else
		#error Opps
	#endif
	fShadowWidth = 4;
	fStatusHeight = 30;

	// inset content area
	Rect screenCoord = MainApp::getThe()->getScreenCoord();
	#if defined(TITLE_ONE)
	fContentLeft = screenCoord.left + fBorderWidth + horzSlop;
	fContentTop = screenCoord.top + (fBorderWidth * 2) + (fTitleHeight / 2) + vertSlop;
	fContentWidth = screenCoord.getWidth() - (fBorderWidth * 2) - (horzSlop * 2);
	fContentHeight = screenCoord.getHeight() - (fBorderWidth * 3) - (fTitleHeight / 2) - fStatusHeight - (vertSlop * 2);
	#elif defined(TITLE_TWO)
	fContentLeft = screenCoord.left + fBorderWidth + horzSlop;
	fContentTop = screenCoord.top + fBorderWidth + fTitleHeight + vertSlop;
	fContentWidth = screenCoord.getWidth() - fBorderWidth - (horzSlop * 2);
	fContentHeight = screenCoord.getHeight() - fBorderWidth - fTitleHeight - fStatusHeight - (vertSlop * 2);
	#else
		#error Opps
	#endif

	fContainerControl.setRect(Rect(0, 0, fContentWidth, fContentHeight));

	//fDataLoaded = false;
	//fFailedDataLoad = false;
}

/******************************************************************************/

ScreenPtr Screen::newInstance(Screen* pScreen)
{
	ScreenPtr screenPtr(pScreen);

	MainApp::getThe()->openScreen(screenPtr);
	screenPtr->createControls();

	return screenPtr;
}

/******************************************************************************/

void Screen::close() const
{
	MainApp::getThe()->closeScreen(fScreenID);
}

/******************************************************************************/

const char* Screen::getTitle() const
{
	const char* title = fContainerControl.getTitle();

	if (tStrHasLen(title))
		return title;

	return fTitle.c_str();
}

/******************************************************************************/

void Screen::draw(bool hasFocus)
{
	drawFrame(hasFocus);
	drawStatus();
	drawContent(hasFocus);
}

/******************************************************************************/

#if defined(TITLE_ONE)
void Screen::drawFrame(bool /*hasFocus*/)
{
	FontPtr fontPtr = MainApp::getThe()->getFont(gBigFontID);
	int statusSeparatorHeight = 2;
	const char* title = getTitle();
	int titleLen = STRLEN(title);

	DrawRect(Rect(fContentLeft, fContentTop, fContentLeft + fContentWidth, fContentTop + fContentHeight
		+ fStatusHeight), fIsFullScreen ? gScreenBackgroundTransColor : gScreenBackgroundSolidColor);

	// window border shadow
	DrawBorder(fContentLeft - fBorderWidth, fContentTop - fBorderWidth,
		fContentWidth + (2 * fBorderWidth) + fShadowWidth,
		fContentHeight + (2 * fBorderWidth) + fShadowWidth + fStatusHeight,
		fBorderWidth, gBlackColor);

	// status separator shadow
	if(fStatusHeight > 0)
		DrawRect(RectWH(fContentLeft, fContentTop + fContentHeight + statusSeparatorHeight,
			fContentWidth + fShadowWidth, fShadowWidth), gBlackColor);

	// window border
	DrawBorder(fContentLeft - fBorderWidth - fShadowWidth,
		fContentTop - fBorderWidth - fShadowWidth,
		fContentWidth + (2 * fBorderWidth) + fShadowWidth,
		fContentHeight + (2 * fBorderWidth) + fShadowWidth + fStatusHeight,
		fBorderWidth, gWhiteColor);

		// status separator
	if(fStatusHeight > 0)
	{
		DrawRect(RectWH(fContentLeft - fShadowWidth, fContentTop + fContentHeight,
			fContentWidth + fShadowWidth, statusSeparatorHeight), gWhiteColor);
	}

	// title box, background, shadow, border
	if((titleLen > 0) && (fTitleHeight > 0))
	{
		// border and shadow
		int titleWidth = fontPtr->getWidth(title) + (fTitlePadWidth * 2);
		int left = fContentLeft + (fContentWidth / 2) - (titleWidth / 2);
		int top = fContentTop - fShadowWidth - (fTitleHeight / 2);
		Rect rect = RectWH(left, top, titleWidth, fTitleHeight);
		DrawRectDithered(rect, gWhiteColor, gScreenBackgroundSolidColor);
		DrawBorder(left - fBorderWidth, top - fBorderWidth, 
			titleWidth + (2 * fBorderWidth) + fShadowWidth,
			fTitleHeight + (2 * fBorderWidth) + fShadowWidth,
			fBorderWidth, gBlackColor);
		DrawBorder(left - fBorderWidth - fShadowWidth,
			top - fBorderWidth - fShadowWidth, 
			titleWidth + (2 * fBorderWidth) + fShadowWidth,
			fTitleHeight + (2 * fBorderWidth) + fShadowWidth,
			fBorderWidth, gWhiteColor);

		// title w/ shadow
		rect.offset(1, 1);
		DrawTextAligned(rect, ha_Center, va_Middle, title, fontPtr, gBlackColor);
		rect.offset(-1, -1);
		DrawTextAligned(rect, ha_Center, va_Middle, title, fontPtr, gWhiteColor);
	}
}
#elif defined(TITLE_TWO)
void Screen::drawFrame(bool /*hasFocus*/)
{
	FontPtr fontPtr = MainApp::getThe()->getFont(gBigWhiteFontID);
	int statusSeparatorHeight = 2;
	const char* title = getTitle();
	int titleLen = STRLEN(title);

	// draw background
	DrawRect(Rect(fContentLeft - fBorderWidth, fContentTop - fBorderWidth - fTitleHeight,
		fContentLeft + fContentWidth, fContentTop + fContentHeight + fStatusHeight),
		fIsFullScreen ? gScreenBackgroundTransColor : gScreenBackgroundSolidColor);

	// draw Storm
	if(fIsFullScreen)
	{
		DrawTextAligned(Rect(fContentLeft + 10, fContentTop - fBorderWidth - fTitleHeight + fBorderWidth,
			fContentLeft + fContentWidth, fContentTop - fBorderWidth),
			ha_Right, va_Middle, "STORM", fontPtr);
	}

	// draw title
	if((titleLen > 0) && (fTitleHeight > 0))
	{
		DrawRectDithered(fContentLeft - fBorderWidth, fContentTop - fBorderWidth - fTitleHeight,
			fContentLeft + fContentWidth, fContentTop - fBorderWidth - fTitleHeight + fBorderWidth,
			gWhiteColor, gBackgroundColor, dd_Left2Right);

		DrawRectDithered(fContentLeft - fBorderWidth, fContentTop - fBorderWidth - fTitleHeight,
			fContentLeft, fContentTop - fBorderWidth - fTitlePadWidth, gWhiteColor, gBackgroundColor, dd_Top2Bottom);

		DrawTextAligned(Rect(fContentLeft + 10, fContentTop - fBorderWidth - fTitleHeight + fBorderWidth,
			fContentLeft + fContentWidth, fContentTop - fBorderWidth),
			ha_Left, va_Middle, title, fontPtr);
	}

	// draw border
	DrawRectDithered(fContentLeft - fBorderWidth, fContentTop - fBorderWidth, fContentLeft + fContentWidth,
		fContentTop, gWhiteColor, gBackgroundColor, dd_Left2Right);

	DrawRectDithered(fContentLeft - fBorderWidth, fContentTop - fBorderWidth, fContentLeft,
		fContentTop + fContentHeight + fStatusHeight, gWhiteColor, gBackgroundColor, dd_Top2Bottom);

	if(!fIsFullScreen)
	{
		DrawRectDithered(fContentLeft - fBorderWidth, fContentTop + fContentHeight + fStatusHeight - fBorderWidth,
			fContentLeft + fContentWidth, fContentTop + fContentHeight + fStatusHeight, gWhiteColor,
			gBackgroundColor, dd_Right2Left);

		DrawRectDithered(fContentLeft + fContentWidth , fContentTop - fBorderWidth,
			fContentLeft + fContentWidth + fBorderWidth,
			fContentTop + fContentHeight + fStatusHeight, gWhiteColor, gBackgroundColor, dd_Bottom2Top);
	}

	// draw status
	if(fStatusHeight > 0)
	{
		DrawRectDithered(fContentLeft + fBorderWidth, fContentTop + fContentHeight, fContentLeft + fContentWidth,
			fContentTop + fContentHeight + fBorderWidth, gWhiteColor, gBackgroundColor, dd_Left2Right);

		if(fIsFullScreen && (STRLEN(MainApp::getThe()->getVersion()) > 0))
		{
			CStr64 versionStr("v");
			versionStr.concat(MainApp::getThe()->getVersion());

			DrawTextAligned(Rect(fContentLeft + 10, fContentTop + fContentHeight + fBorderWidth,
				fContentLeft + fContentWidth, fContentTop + fContentHeight + fBorderWidth + fStatusHeight),
				ha_Right, va_Middle, versionStr.c_str(), MainApp::getThe()->getFont(gSmallWhiteFontID));
		}
	}
}
#else
	#error Opps
#endif

#if FALSE
void Screen::drawFrame(int inForeground)
{
	int right = fLeft + fWidth;
	int bottom = fTop + fHeight;

	// fill body with background color
    glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2i(fLeft, fTop);
	glVertex2f(right, fTop );
    glColor3f(0.0, 0.0, 0.0);
	glVertex2f(right, bottom);
	glVertex2i(fLeft, bottom);
	glEnd();

	// set border color
	if (inForeground)
	    glColor3f(1.0, 0.0, 0.0);
	else
	    glColor3f(0.5, 0.5, 0.5);

	// draw the title
	glBegin(GL_POLYGON);
	glVertex2i(fLeft - fBorderWidth, fTop - (fBorderWidth * 2) - fTitleHeight);
	glVertex2f(right + fBorderWidth, fTop - (fBorderWidth * 2) - fTitleHeight);
	// set border color
	if(inForeground)
	    glColor3f(1.0, 0.75, 0.75);
	else
	    glColor3f(0.5, 0.5, 0.5);
	glVertex2f(right + fBorderWidth, fTop);
	glVertex2i(fLeft - fBorderWidth, fTop);
	glEnd();

	// frame border
	// left vertical
	glBegin(GL_POLYGON);
	glVertex2i(fLeft - fBorderWidth, fTop);
	glVertex2i(fLeft, fTop);
	glVertex2i(fLeft, bottom);
	glVertex2i(fLeft - fBorderWidth, bottom + fBorderWidth);
	glEnd();
	// bottom horizontal
	glBegin(GL_POLYGON);
	glVertex2i(fLeft, bottom);
	glVertex2i(right, bottom);
	glVertex2f(right + fBorderWidth, bottom + fBorderWidth);
	glVertex2i(fLeft - fBorderWidth, bottom + fBorderWidth);
	glEnd();
	// right vertical
	glBegin(GL_POLYGON);
	glVertex2i(right, fTop);
	glVertex2f(right + fBorderWidth, fTop);
	glVertex2f(right + fBorderWidth, bottom + fBorderWidth);
	glVertex2i(right, bottom);
	glEnd();

	// frame shadow
    glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(fLeft - fBorderWidth + (fShadowWidth / 2), bottom + fBorderWidth);
	glVertex2i(right + fBorderWidth, bottom + fBorderWidth);
	glVertex2i(right + fBorderWidth + fShadowWidth, bottom + fBorderWidth + fShadowWidth);
	glVertex2i(fLeft - fBorderWidth + fShadowWidth, bottom + fBorderWidth + fShadowWidth);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(right + fBorderWidth, fTop - (fBorderWidth * 2) - fTitleHeight + (fShadowWidth / 2));
	glVertex2i(right + fBorderWidth + fShadowWidth, fTop - (fBorderWidth * 2) - fTitleHeight + fShadowWidth);
	glVertex2i(right + fBorderWidth + fShadowWidth, bottom + fBorderWidth + fShadowWidth);
	glVertex2i(right + fBorderWidth, bottom + fBorderWidth);
	glEnd();

    glColor3f(1.0, 1.0, 1.0);
//	output(fLeft + 4, fTop - fBorderWidth, title);
}
#endif

/******************************************************************************/

void Screen::drawStatus()
{
}

/******************************************************************************/

void Screen::drawContent(bool hasFocus)
{
/*
	if(fDataLoaded && !fFailedDataLoad)
	{
*/
		AdjustDrawCoordOffset(fContentLeft, fContentTop);
		fContainerControl.draw(hasFocus);
		AdjustDrawCoordOffset(-fContentLeft, -fContentTop);
/*
	}
	else if(!fDataLoaded)
	{
		Rect rect = RectWH(fContentLeft, fContentTop, fContentWidth, fContentHeight);
		rect.inset(fContentWidth / 4, fContentHeight / 4);

		rect.inset(4, 4);
		DrawRect(rect, gFocusedBackgroundColor);
		DrawTextAligned(rect, ha_Center, va_Middle, "Please Wait...", gNormalFontID, gWhiteColor);
		rect.inset(-4, -4);
		DrawBorder2(rect, 4, gFocusedBorderColor);
	}
	else if(fFailedDataLoad)
	{
		Rect rect = RectWH(fContentLeft, fContentTop, fContentWidth, fContentHeight);
		rect.inset(fContentWidth / 4, fContentHeight / 4);

		rect.inset(4, 4);
		DrawRect(rect, gFocusedBackgroundColor);
		DrawTextAligned(rect, ha_Left, va_Middle, "We are unable to communicate...", gNormalFontID, gWhiteColor);
		rect.inset(-4, -4);
		DrawBorder2(rect, 4, gFocusedBorderColor);
	}
*/
}

/******************************************************************************/

bool Screen::key(int key)
{
	if(fContainerControl.key(key))
		return true;

	if(key == ek_Back)
	{
		close();
		return true;
	}

	return false;
}

/******************************************************************************/

void Screen::idle()
{
/*
	if(!fDataLoaded)
	{
		fDataLoaded = true;
		try
		{
			fFailedDataLoad = !loadData();
		}
		catch(...)
		{
			fFailedDataLoad = true;
		}
	}
*/
}

/******************************************************************************/

bool Screen::mouseClick(bool leftButton, bool buttonDown, int x, int y)
{
	bool rc = fContainerControl.mouseClick(leftButton, buttonDown, x - fContentLeft, y - fContentTop);
	if(rc)
		return rc;

	if(!leftButton && !buttonDown)
	{
		close();
		return true;
	}

	return false;
}

/******************************************************************************/

void Screen::mouseMove(bool buttonDown, int x, int y)
{
	fContainerControl.mouseMove(buttonDown, x - fContentLeft, y - fContentTop);
}

/******************************************************************************/

void Screen::onButton(const ControlID& /*controlID*/)
{
	// default action is to proceed to the next field
	key(ek_DownButton);
}

/******************************************************************************/
/******************************************************************************/

ScreenPtr ScreenVector::findByID(const ScreenID& screenID) const
{
	const_iterator iter;

	iter = std::find_if(begin(), end(), findIDCompare(screenID));
	if(iter != end())
		return(*iter);

	return ScreenPtr();
}

/******************************************************************************/

ScreenPtr ScreenVector::getByID(const ScreenID& screenID) const
{
	const_iterator iter;

	iter = std::find_if(begin(), end(), findIDCompare(screenID));
	if(iter != end())
		return(*iter);

	throw ASIException("ScreenVector::getByID", "Invalid ScreenID(%s)", screenID.c_str());
}

/******************************************************************************/

void ScreenVector::removeByID(const ScreenID& screenID)
{
	iterator iter;

	iter = std::find_if(begin(), end(), findIDCompare(screenID));
	if(iter != end())
		erase(iter);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
