/* RecreateSettingsControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SetupData.h"
#include "RecreateSettingsControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID RecreateSettingsControl::fDescriptionID("description");
const ControlID RecreateSettingsControl::fSerialNoLabelID("serialnolabel");
const ControlID RecreateSettingsControl::fSerialNoID("serialno");
const ControlID RecreateSettingsControl::fPINLabelID("pinlabel");
const ControlID RecreateSettingsControl::fPINID("pin");
const ControlID RecreateSettingsControl::fRememberPINLabelID("rememberpinlabel");
const ControlID RecreateSettingsControl::fRememberPINID("rememberpin");
const ControlID RecreateSettingsControl::ContinueID("continue");

/******************************************************************************/

RecreateSettingsControl::RecreateSettingsControl(const ControlID& controlID, const ScreenID& screenID)
 : ContainerControl(controlID, screenID)
{
	fTitle.copy("Recreate Settings");
}

/******************************************************************************/

ControlPtr RecreateSettingsControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new RecreateSettingsControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void RecreateSettingsControl::createControls()
{
	ControlPtr controlPtr;
	LabelControlPtr labelControlPtr;
	EditControlPtr editControlPtr;
	SelectControlPtr selectControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	controlPtr = TextControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, 50, fRect.getWidth() - 20, 60),
		"To recreate your settings and have them resaved to a memory card, please enter the Serial Number from the iNetVOD case and enter the PIN you chose for your account:");
	newControl(controlPtr);

	top = 150;
	labelControlPtr = LabelControl::newInstance(fSerialNoLabelID, fScreenID,
		RectWH(screenCenter - 255, top, 250, 0), "Serial Number:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	editControlPtr = EditControl::newInstance(fSerialNoID, fScreenID,
		RectWH(screenCenter + 5, top, 174, 0));
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
		RectWH(screenCenter + 5, top, 84, 0));
	editControlPtr->setType(ect_Numeric);
	editControlPtr->setMaxLength(4);
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

bool RecreateSettingsControl::loadData(ObjectPtr objectPtr)
{
	return true;
}

/******************************************************************************/

bool RecreateSettingsControl::unloadData(ObjectPtr objectPtr)
{
	EditControlPtr editControlPtr;
	SelectControlPtr selectControlPtr;
	SetupDataPtr setupDataPtr = objectPtr;
	CStr256 tempStr;

	editControlPtr = getControl(fSerialNoID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "Serial Number must be entered.");
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
