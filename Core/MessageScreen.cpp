/* MessageScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID MessageScreen::ID("Message001");

const ControlID MessageScreen::fTextID("text");
const ControlID MessageScreen::fYesID("yes");
const ControlID MessageScreen::fNoID("no");
const ControlID MessageScreen::fCancelID("cancel");

/******************************************************************************/

MessageScreen::MessageScreen(MessagePrompt messagePrompt, const char* text)
	: Screen(ID)
{
	if(messagePrompt != mp_OK)
		throw ASIException("MessageScreen::MessageScreen", "Need to implement");

	fIsFullScreen = false;

	fTitleHeight = 0;
	fStatusHeight = 0;

	Rect screenCoord = MainApp::getThe()->getScreenCoord();
	fContentWidth = (screenCoord.getWidth() * 3) / 4;
	fContentHeight = (screenCoord.getHeight() * 1) / 2;
	fContentLeft = screenCoord.left + (screenCoord.getWidth() / 2) - (fContentWidth / 2);
	fContentTop = screenCoord.top + (screenCoord.getHeight() / 2) - (fContentHeight / 2);

	fContainerControl.setRect(Rect(0, 0, fContentWidth, fContentHeight));

	fMessagePrompt = messagePrompt;
	fText.copy(text);
	fMessageReturn = mr_OK;
}

/******************************************************************************/

MessageReturn MessageScreen::newInstance(MessagePrompt messagePrompt, const char* text)
{
	MessageScreenPtr messageScreenPtr = Screen::newInstance(new MessageScreen(messagePrompt, text));

	MainApp::getThe()->modelLoop(MessageScreen::ID);
	return messageScreenPtr->getMessageReturn();
}

/******************************************************************************/

void MessageScreen::createControls()
{
	ControlPtr controlPtr;
	ButtonControlPtr buttonControlPtr;
	
	Screen::createControls();

	controlPtr = TextControl::newInstance(fTextID, getScreenID(), 
		RectWH(10, 10, fContentWidth - 20, fContentHeight - 70),
		fText.c_str());
	newControl(controlPtr);

	buttonControlPtr = ButtonControl::newInstance(fYesID, getScreenID(),
		RectWH((fContentWidth / 2) - 40, fContentHeight - 50, 80, 38), "OK");
	buttonControlPtr->setFocus(true);
	newControl(buttonControlPtr);
}

/******************************************************************************/

void MessageScreen::onButton(const ControlID& /*controlID*/)
{
	close();
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
