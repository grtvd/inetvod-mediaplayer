/* WaitScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID WaitScreen::ID("Wait001");

const ControlID WaitScreen::fTextID("text");

/******************************************************************************/

WaitScreen::WaitScreen(const char* text) : Screen(ID)
{
	fIsFullScreen = false;

	fTitleHeight = 0;
	fStatusHeight = 0;

	Rect screenCoord = MainApp::getThe()->getScreenCoord();
	fContentWidth = (screenCoord.getWidth() * 1) / 2;
	fContentHeight = (screenCoord.getHeight() * 1) / 4;
	fContentLeft = screenCoord.left + (screenCoord.getWidth() / 2) - (fContentWidth / 2);
	fContentTop = screenCoord.top + (screenCoord.getHeight() / 2) - (fContentHeight / 2);

	fContainerControl.setRect(Rect(0, 0, fContentWidth, fContentHeight));

	if(tStrHasLen(text))
		fText.copy(text);
	else
		fText.copy("Please wait...");
}

/******************************************************************************/

void WaitScreen::createControls()
{
	ControlPtr controlPtr;
	
	Screen::createControls();

	controlPtr = TextControl::newInstance(fTextID, getScreenID(), 
		RectWH(10, 10, fContentWidth - 20, fContentHeight - 20),
		fText.c_str());
	newControl(controlPtr);
}

/******************************************************************************/

bool WaitScreen::key(int /*key*/)
{
	return true;	//eat all key presses during 'wait'
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
