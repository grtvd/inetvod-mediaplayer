/* NeedLogonIDControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "NeedLogonIDControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID NeedLogonIDControl::fRegisterTextID("registertext");
const ControlID NeedLogonIDControl::fProceedTextID("proceedtext");
const ControlID NeedLogonIDControl::HaveLogonID("havelogon");

/******************************************************************************/

ControlPtr NeedLogonIDControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new NeedLogonIDControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void NeedLogonIDControl::createControls()
{
	ControlPtr controlPtr;
	ButtonControlPtr buttonControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	top = 20;
	controlPtr = TextControl::newInstance(fRegisterTextID, fScreenID, RectWH(10, top, fRect.getWidth() - 20, 56),
		"You may register for iNetVOD by visiting www.iNetVOD.com/register or by calling 1-800-999-9999.");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 28;
	controlPtr = TextControl::newInstance(fProceedTextID, fScreenID, RectWH(10, top, fRect.getWidth() - 20, 56),
		"Upon registering, you will be assigned a Logon ID.  Proceed once you have your Logon ID.");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 28;
	buttonControlPtr = ButtonControl::newInstance(HaveLogonID, fScreenID, RectWH(screenCenter - 150, top, 300, 38), "I have my Logon ID");
	buttonControlPtr->setHorzAlign(ha_Left);
	buttonControlPtr->setFocus(true);
	newControl(buttonControlPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
