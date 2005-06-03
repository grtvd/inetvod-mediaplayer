/* StorePasswordsControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SetupData.h"
#include "StorePasswordsControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID StorePasswordsControl::fDescriptionID("description");
const ControlID StorePasswordsControl::NotStoredID("notstored");
const ControlID StorePasswordsControl::StoreLocallyID("storelocally");
const ControlID StorePasswordsControl::StoreServerID("storeserver");

/******************************************************************************/

ControlPtr StorePasswordsControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new StorePasswordsControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void StorePasswordsControl::createControls()
{
	ControlPtr controlPtr;
	ButtonControlPtr buttonControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	top = 50;
	controlPtr = TextControl::newInstance(fDescriptionID, fScreenID, RectWH(10, top, fRect.getWidth() - 20, 40),
		"Where would you like to store your passwords that you enter for your Providers?");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 20;
	buttonControlPtr = ButtonControl::newInstance(NotStoredID, fScreenID,
		RectWH(screenCenter - 200, top, 400, 38), "Don't store any of my passwords");
	buttonControlPtr->setHorzAlign(ha_Left);
	buttonControlPtr->setFocus(true);
	newControl(buttonControlPtr);

	top += 45;
	buttonControlPtr = ButtonControl::newInstance(StoreLocallyID, fScreenID,
		RectWH(screenCenter - 200, top, 400, 38), "Store my passwords on the Memory Card");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);

	top += 45;
	buttonControlPtr = ButtonControl::newInstance(StoreServerID, fScreenID,
		RectWH(screenCenter - 200, top, 400, 38), "Store my passwords on the iNetVOD servers");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
