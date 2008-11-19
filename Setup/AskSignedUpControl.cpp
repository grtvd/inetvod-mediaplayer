/* AskSignedUpControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
//#include "SetupData.h"
#include "AskSignedUpControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID AskSignedUpControl::fWelecomeTextID("welecometext");
const ControlID AskSignedUpControl::fRegisteredTextID("registeredtext");
const ControlID AskSignedUpControl::AlreadyRegisteredID("alreadyregistered");
const ControlID AskSignedUpControl::NotRegisteredID("notregistered");

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

	top = 20;
	controlPtr = TextControl::newInstance(fWelecomeTextID, fScreenID, RectWH(10, top, fRect.getWidth() - 20, 84),
		"Welcome to Storm Media Player! Storm is a service for accessing a vast array of Internet-based content, such as movies, TV shows, and radio programs.");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 28;
	controlPtr = TextControl::newInstance(fRegisteredTextID, fScreenID, RectWH(30, top, fRect.getWidth() - 40, 28),
		"Are you already registered with Storm?");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 28;
	buttonControlPtr = ButtonControl::newInstance(AlreadyRegisteredID, fScreenID, RectWH(screenCenter - 150, top, 300, 38), "Yes, I am already registered");
	buttonControlPtr->setHorzAlign(ha_Left);
	buttonControlPtr->setFocus(true);
	newControl(buttonControlPtr);

	top += buttonControlPtr->getRect().getHeight() + 6;
	buttonControlPtr = ButtonControl::newInstance(NotRegisteredID, fScreenID, RectWH(screenCenter - 150, top, 300, 38), "No, I am not yet registered");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
