/* IncludeAdultControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SetupData.h"
#include "IncludeAdultControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID IncludeAdultControl::fDescriptionID("description");
const ControlID IncludeAdultControl::NeverID("never");
const ControlID IncludeAdultControl::PromptPasswordID("promptpassword");
const ControlID IncludeAdultControl::AlwaysID("always");

/******************************************************************************/

ControlPtr IncludeAdultControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new IncludeAdultControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void IncludeAdultControl::createControls()
{
	ControlPtr controlPtr;
	ButtonControlPtr buttonControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	top = 50;
	controlPtr = TextControl::newInstance(fDescriptionID, fScreenID, RectWH(10, top, fRect.getWidth() - 20, 40),
		"Do you want to be able to access Adult content?");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 20;
	buttonControlPtr = ButtonControl::newInstance(NeverID, fScreenID,
		RectWH(screenCenter - 200, top, 400, 38), "No, never");
	buttonControlPtr->setHorzAlign(ha_Left);
	buttonControlPtr->setFocus(true);
	newControl(buttonControlPtr);

	top += 45;
	buttonControlPtr = ButtonControl::newInstance(PromptPasswordID, fScreenID,
		RectWH(screenCenter - 200, top, 400, 38), "Yes, but first prompt for my PIN");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);

	top += 45;
	buttonControlPtr = ButtonControl::newInstance(AlwaysID, fScreenID,
		RectWH(screenCenter - 200, top, 400, 38), "Yes, alwasys (don't ask for my PIN)");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
