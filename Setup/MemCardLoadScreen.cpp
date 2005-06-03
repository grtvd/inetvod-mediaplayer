/* MemCardLoadScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "MemCardLoadScreen.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID MemCardLoadScreen::ID("Setup005");

const ControlID MemCardLoadScreen::fTextID("text");
const ControlID MemCardLoadScreen::fMemCard1ControlID("memcard1");
const ControlID MemCardLoadScreen::fMemCard2ControlID("memcard2");

/******************************************************************************/

MemCardLoadScreen::MemCardLoadScreen() : Screen(ID)
{
	fIsFullScreen = false;

	Rect screenCoord = MainApp::getThe()->getScreenCoord();
	fContentWidth = (screenCoord.getWidth() * 3) / 4;
	fContentHeight = (screenCoord.getHeight() * 1) / 2;
	fContentLeft = screenCoord.left + (screenCoord.getWidth() / 2) - (fContentWidth / 2);
	fContentTop = screenCoord.top + (screenCoord.getHeight() / 2) - (fContentHeight / 2);

	fContainerControl.setRect(Rect(0, 0, fContentWidth, fContentHeight));

	fTitle.copy("Load");
	fSelectedMemoryCardSlot = mc_Undefined;
}

/******************************************************************************/

MemoryCardSlot MemCardLoadScreen::newInstance()
{
	MemCardLoadScreenPtr memCardLoadScreenPtr = Screen::newInstance(new MemCardLoadScreen());

	MainApp::getThe()->modelLoop(ID);
	return memCardLoadScreenPtr->getSelectedMemoryCardSlot();
}

/******************************************************************************/

void MemCardLoadScreen::createControls()
{
	ControlPtr controlPtr;
	ButtonControlPtr buttonControlPtr;
	int screenCenter = fContentWidth / 2;
	int top;
	
	Screen::createControls();

	top = 40;
	controlPtr = TextControl::newInstance(fTextID, getScreenID(), 
		RectWH(10, top, fContentWidth - 20, 44),
		"Please select the Memory Card to load your settings:");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 20;
	buttonControlPtr = ButtonControl::newInstance(fMemCard1ControlID, getScreenID(),
		RectWH(screenCenter - 100, top, 200, 38), "Memory Card 1");
	buttonControlPtr->setFocus(true);
	newControl(buttonControlPtr);

	top += 45;
	buttonControlPtr = ButtonControl::newInstance(fMemCard2ControlID, getScreenID(),
		RectWH(screenCenter - 100, top, 200, 38), "Memory Card 2");
	newControl(buttonControlPtr);
}

/******************************************************************************/

void MemCardLoadScreen::onButton(const ControlID& controlID)
{
	if(controlID == fMemCard1ControlID)
	{
		fSelectedMemoryCardSlot = mc_Slot1;
		close();
		return;
	}

	if(controlID == fMemCard2ControlID)
	{
		fSelectedMemoryCardSlot = mc_Slot2;
		close();
		return;
	}

	Screen::onButton(controlID);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
