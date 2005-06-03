/* HaveLogonIDControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SetupData.h"
#include "HaveLogonIDControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID HaveLogonIDControl::fDescriptionID("description");
const ControlID HaveLogonIDControl::fLogonIDLabelID("logonidlabel");
const ControlID HaveLogonIDControl::fLogonIDID("logonid");
const ControlID HaveLogonIDControl::fPINLabelID("pinlabel");
const ControlID HaveLogonIDControl::fPINID("pin");
const ControlID HaveLogonIDControl::fRememberPINLabelID("rememberpinlabel");
const ControlID HaveLogonIDControl::fRememberPINID("rememberpin");
const ControlID HaveLogonIDControl::ContinueID("continue");

/******************************************************************************/

ControlPtr HaveLogonIDControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new HaveLogonIDControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void HaveLogonIDControl::createControls()
{
	ControlPtr controlPtr;
	LabelControlPtr labelControlPtr;
	EditControlPtr editControlPtr;
	SelectControlPtr selectControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	top = 20;
	controlPtr = TextControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, top, fRect.getWidth() - 20, 56),
		"Please enter your registered Logon ID and your chosen PIN:");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 28;
	labelControlPtr = LabelControl::newInstance(fLogonIDLabelID, fScreenID,
		RectWH(screenCenter - 255, top, 250, 0), "Logon ID:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	editControlPtr = EditControl::newInstance(fLogonIDID, fScreenID,
		RectWH(screenCenter + 5, top, 198, 0));
	editControlPtr->setType(ect_UpperAlphaNumeric);
	editControlPtr->setMaxLength(9);
	editControlPtr->setFocus(true);
	newControl(editControlPtr);

	top += 40;
	labelControlPtr = LabelControl::newInstance(fPINLabelID, fScreenID,
		RectWH(screenCenter - 255, top, 250, 0), "PIN:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	editControlPtr = EditControl::newInstance(fPINID, fScreenID,
		RectWH(screenCenter + 5, top, 132, 0));
	editControlPtr->setType(ect_Numeric);
	editControlPtr->setMaxLength(6);
	newControl(editControlPtr);

	top += 40;
	labelControlPtr = LabelControl::newInstance(fRememberPINLabelID, fScreenID,
		RectWH(screenCenter - 255, top, 250, 0), "Remember PIN:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	selectControlPtr = SelectControl::newInstance(fRememberPINID, fScreenID,
		RectWH(screenCenter + 5, top, 120, 0));
	selectControlPtr->getItemVector().push_back(CStrVar("Yes"));
	selectControlPtr->getItemVector().push_back(CStrVar("No"));
	newControl(selectControlPtr);

	controlPtr = ButtonControl::newInstance(ContinueID, fScreenID,
		RectWH(screenCenter - 60, fRect.getHeight() - 50, 120, 38), "Continue");
	newControl(controlPtr);
}

/******************************************************************************/

bool HaveLogonIDControl::loadData(ObjectPtr objectPtr)
{
	return true;
}

/******************************************************************************/

bool HaveLogonIDControl::unloadData(ObjectPtr objectPtr)
{
	EditControlPtr editControlPtr;
	SelectControlPtr selectControlPtr;
	SetupDataPtr setupDataPtr = objectPtr;
	CStr256 tempStr;

	editControlPtr = getControl(fLogonIDID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "Logon ID must be entered.");
		return false;
	}
	setupDataPtr->setUserID(editControlPtr->getText());

	editControlPtr = getControl(fPINID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "PIN must be entered.");
		return false;
	}
	setupDataPtr->setUserPassword(editControlPtr->getText());

	selectControlPtr = getControl(fRememberPINID);
	setupDataPtr->setRememberPassword(selectControlPtr->getCurItem() == 0);

	return true;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
