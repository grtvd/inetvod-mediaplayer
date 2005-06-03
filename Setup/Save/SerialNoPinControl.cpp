/* SerialNoPinControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SetupData.h"
#include "SerialNoPinControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID SerialNoPinControl::fDescriptionID("description");
const ControlID SerialNoPinControl::fSerialNoLabelID("serialnolabel");
const ControlID SerialNoPinControl::fSerialNoID("serialno");
const ControlID SerialNoPinControl::fPINLabelID("pinlabel");
const ControlID SerialNoPinControl::fPINID("pin");
const ControlID SerialNoPinControl::fRememberPINLabelID("rememberpinlabel");
const ControlID SerialNoPinControl::fRememberPINID("rememberpin");
const ControlID SerialNoPinControl::ContinueID("continue");

/******************************************************************************/

SerialNoPinControl::SerialNoPinControl(const ControlID& controlID, const ScreenID& screenID)
 : ContainerControl(controlID, screenID)
{
	fTitle.copy("Sign-Up");
}

/******************************************************************************/

ControlPtr SerialNoPinControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new SerialNoPinControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void SerialNoPinControl::createControls()
{
	ControlPtr controlPtr;
	LabelControlPtr labelControlPtr;
	EditControlPtr editControlPtr;
	SelectControlPtr selectControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	controlPtr = TextControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, 50, fRect.getWidth() - 20, 40),
		"Please enter the Serial Number from the iNetVOD case and choose a PIN for your account:");
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

bool SerialNoPinControl::loadData(ObjectPtr objectPtr)
{
	return true;
}

/******************************************************************************/

bool SerialNoPinControl::unloadData(ObjectPtr objectPtr)
{
	EditControlPtr editControlPtr;
	SelectControlPtr selectControlPtr;
	SetupDataPtr setupDataPtr = objectPtr;

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
