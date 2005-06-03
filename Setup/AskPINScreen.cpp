/* AskPINScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "AskPINScreen.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID AskPINScreen::ID("Startup004");

const ControlID AskPINScreen::fTextID("text");
const ControlID AskPINScreen::fPINLabelID("pinlabel");
const ControlID AskPINScreen::fPINID("pin");

/******************************************************************************/

AskPINScreen::AskPINScreen() : Screen(ID)
{
	fIsFullScreen = false;

	Rect screenCoord = MainApp::getThe()->getScreenCoord();
	fContentWidth = (screenCoord.getWidth() * 3) / 4;
	fContentHeight = (screenCoord.getHeight() * 1) / 2;
	fContentLeft = screenCoord.left + (screenCoord.getWidth() / 2) - (fContentWidth / 2);
	fContentTop = screenCoord.top + (screenCoord.getHeight() / 2) - (fContentHeight / 2);

	fContainerControl.setRect(Rect(0, 0, fContentWidth, fContentHeight));

	fTitle.copy("PIN Required");
}

/******************************************************************************/

ScreenPtr AskPINScreen::newInstance()
{
	ScreenPtr askPINScreenPtr = Screen::newInstance(new AskPINScreen());

	MainApp::getThe()->modelLoop(ID);
	return askPINScreenPtr;
}

/******************************************************************************/

void AskPINScreen::createControls()
{
	ControlPtr controlPtr;
	LabelControlPtr labelControlPtr;
	EditControlPtr editControlPtr;
	int screenCenter = fContentWidth / 2;
	int top;
	
	Screen::createControls();

	top = 40;
	controlPtr = TextControl::newInstance(fTextID, getScreenID(), 
		RectWH(10, top, fContentWidth - 20, 44),
		"Please enter your PIN:");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 20;
	labelControlPtr = LabelControl::newInstance(fPINLabelID, fScreenID,
		RectWH(10, top, screenCenter - 50, 0), "PIN:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	editControlPtr = EditControl::newInstance(fPINID, fScreenID, RectWH(screenCenter - 30, top, 132, 0));
	editControlPtr->setType(ect_Numeric);
	editControlPtr->setMaxLength(6);
	editControlPtr->setFocus(true);
	editControlPtr->setAutoButton(true);
	newControl(editControlPtr);
}

/******************************************************************************/

void AskPINScreen::onButton(const ControlID& controlID)
{
	if(controlID == fPINID)
	{
		EditControlPtr editControlPtr;

		editControlPtr = getControl(fPINID);
		if(!tStrHasLen(editControlPtr->getText()))
		{
			MessageScreen::newInstance(mp_OK, "PIN must be entered.");
			return;
		}
		fUserPassword.copy(editControlPtr->getText());

		close();
		return;
	}

	Screen::onButton(controlID);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
