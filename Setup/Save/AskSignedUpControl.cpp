/* AskSignedUpControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SetupData.h"
#include "AskSignedUpControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID AskSignedUpControl::fWelecomeTextID("welecometext");
const ControlID AskSignedUpControl::SignUpNowID("signupnowid");
const ControlID AskSignedUpControl::fRegisteredTextID("registeredtext");
const ControlID AskSignedUpControl::LoadSettingsID("loadsettings");
const ControlID AskSignedUpControl::RecreateSettingsID("recreatesettings");

/******************************************************************************/

ControlPtr AskSignedUpControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new AskSignedUpControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void AskSignedUpControl::createControls()
{
	ControlPtr controlPtr;
	ButtonControlPtr buttonControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	top = 50;
	controlPtr = TextControl::newInstance(fWelecomeTextID, fScreenID, RectWH(10, top, fRect.getWidth() - 20, 60),
		"Welcome to iNetVOD! Before getting started, you will need to register using the serial number from the back side of the product case:");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 6;
	buttonControlPtr = ButtonControl::newInstance(SignUpNowID, fScreenID, RectWH(screenCenter - 150, top, 300, 38), "Register Now");
	buttonControlPtr->setHorzAlign(ha_Left);
	buttonControlPtr->setFocus(true);
	newControl(buttonControlPtr);

	top += 60;
	controlPtr = TextControl::newInstance(fRegisteredTextID, fScreenID, RectWH(10, top, fRect.getWidth() - 20, 60),
		"If you have already registered with iNetVOD, you will need to re-enter your serial number or insert the Memory Card where your settings are located:");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 6;
	buttonControlPtr = ButtonControl::newInstance(LoadSettingsID, fScreenID, RectWH(screenCenter - 150, top, 300, 38), "Load my settings");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);

	top += 45;
	buttonControlPtr = ButtonControl::newInstance(RecreateSettingsID, fScreenID, RectWH(screenCenter - 150, top, 300, 38), "Recreate my settings");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
