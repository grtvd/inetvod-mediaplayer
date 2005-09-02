/* StartScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "StartScreen.h"
#include "SetupScreen.h"
#include "AskPINScreen.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID StartScreen::ID("StartUp001");

const ControlID StartScreen::fTextID("text");
const ControlID StartScreen::fStartID("start");

/******************************************************************************/

StartScreen::StartScreen() : Screen(ID)
{
	fTitle.copy("Welcome");
//	if("Welcome" == fTitle)
//		fTitle.copy("Hello");
}

/******************************************************************************/

void StartScreen::createControls()
{
	Screen::createControls();

	TextControlPtr textControlPtr = TextControl::newInstance(fTextID, fScreenID,
		RectWH(10, 20, fContentWidth - 20, fContentHeight - 50),
		"Welcome to the iNetVOD Media Player demo. This player is a reference "
		"implementation of the iNetVOD user interface for TV-connected devices, "
		"accessing the iNetVOD Service across the Internet using the "
		"iNetVOD Player API. Navigation is performed using the keyboard to simulate "
		"remote control commands. The following commands are supported:\n\n"
		"Arrow Keys - Navigate between the controls\n"
		"Enter - Select the focused control\n"
		"Backspace - Return to the previous screen\n"
		"> - Next value (Edit/Select controls)\n"
		"< - Previous value (Edit/Select controls)\n"
		"Esc - Quit the Media Player"
		);
	textControlPtr->setFontID(gSmallWhiteFontID);
	newControl(textControlPtr);

	ControlPtr controlPtr = ButtonControl::newInstance(fStartID, getScreenID(),
		RectWH((fContentWidth / 2) - 60, fContentHeight - 50, 120, 38), "Start");
	controlPtr->setFocus(true);
	newControl(controlPtr);
}

/******************************************************************************/

void StartScreen::onButton(const ControlID& /*controlID*/)
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();

	if(!sessionPtr->canPingServer())
		if(!sessionPtr->pingServer())
			return;

	if(sessionPtr->findLoadMemCardSettings())
	{
		if(!doSignon())
			return;
	}
	else
	{
		if(SetupScreen::newInstance())
		{
			if(sessionPtr->haveUserID() && !sessionPtr->isUserLoggedOn())
				if(!doSignon())
					return;
		}
	}

	if(sessionPtr->isUserLoggedOn() && !sessionPtr->isSystemDataLoaded())
		if(!sessionPtr->loadSystemData())
			sessionPtr->clearLogonInfo();

	close();
}

/******************************************************************************/

bool StartScreen::doSignon()
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	StatusCode statusCode;

	if(sessionPtr->haveUserPassword())
	{
		statusCode = sessionPtr->signon();

		if(statusCode == sc_Success)
			return true;
		if(statusCode != sc_UserIDPasswordMismatch)
			return false;
	}

	while(true)
	{
		AskPINScreenPtr askPINScreenPtr = AskPINScreen::newInstance();
		if(!tStrHasLen(askPINScreenPtr->getUserPassword()))	// cancelled out
			return false;

		statusCode = sessionPtr->signon(askPINScreenPtr->getUserPassword());

		if(statusCode == sc_Success)
		{
			sessionPtr->saveMemCardSettings();
			return true;
		}

		if(statusCode == sc_InvalidUserID)
			return false;
	}

	return false;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
