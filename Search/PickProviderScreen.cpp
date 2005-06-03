/* PickProviderScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "PickProviderScreen.h"
#include "ShowProviderListControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID PickProviderScreen::ID("Search009");

const ControlID PickProviderScreen::fAvailTextID("availtext");
const ControlID PickProviderScreen::fSelectTextID("selecttext");
const ControlID PickProviderScreen::fProviderListID("providerlist");

/******************************************************************************/

PickProviderScreen::PickProviderScreen(ShowSearchPtr showSearchPtr)
	: Screen(ID)
{
	fIsFullScreen = false;
	fStatusHeight = 0;

	Rect screenCoord = MainApp::getThe()->getScreenCoord();
	fContentWidth = (screenCoord.getWidth() * 3) / 4;
	fContentHeight = (screenCoord.getHeight() * 5) / 8;
	fContentLeft = screenCoord.left + (screenCoord.getWidth() / 2) - (fContentWidth / 2);
	fContentTop = screenCoord.top + (screenCoord.getHeight() / 2) - (fContentHeight / 2);

	fContainerControl.setRect(Rect(0, 0, fContentWidth, fContentHeight));

	fTitle.copy("Select Provider");
	fShowSearchPtr = showSearchPtr;
}

/******************************************************************************/

ScreenPtr PickProviderScreen::newInstance(ShowSearchPtr showSearchPtr)
{
	PickProviderScreenPtr pickProviderScreenPtr = Screen::newInstance(
		new PickProviderScreen(showSearchPtr));

	MainApp::getThe()->modelLoop(ID);
	return pickProviderScreenPtr;
}

/******************************************************************************/

void PickProviderScreen::createControls()
{
	ShowProviderVector showProviderVector;
	CStr256 title;
	ControlPtr controlPtr;
	int top;
	
	Screen::createControls();

	top = 20;
	title.copy("'");
	title.concat(fShowSearchPtr->getName());
	title.concat("' is available from multiple providers.");
	controlPtr = TextControl::newInstance(fAvailTextID, getScreenID(), 
		RectWH(10, top, fContentWidth - 20, 56), title.c_str());
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight();
	controlPtr = TextControl::newInstance(fSelectTextID, getScreenID(), 
		RectWH(10, top, fContentWidth - 20, 28),
		"Please select your desired provider:");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 10;
	ShowProviderListControlPtr showProviderListControlPtr = ShowProviderListControl::newInstance(
		fProviderListID, getScreenID(), RectWH(10, top, fContentWidth - 20, fContentHeight - top - 5));
	showProviderListControlPtr->setFocus(true);
	newControl(showProviderListControlPtr);

	fShowSearchPtr->getShowProviderVector(showProviderVector);
	showProviderListControlPtr->setShowProviderVector(showProviderVector);
}

/******************************************************************************/

void PickProviderScreen::onButton(const ControlID& controlID)
{
	if(controlID == fProviderListID)
	{
		ShowProviderListControlPtr listControlPtr;
		ShowProviderPtr showProviderPtr;

		listControlPtr = getControl(fProviderListID);
		showProviderPtr = listControlPtr->getFocusedItemValue();
		fProviderID = showProviderPtr->getProviderID();

		close();
		return;
	}

	Screen::onButton(controlID);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
