/* HaveProviderControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentData.h"
#include "HaveProviderControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID HaveProviderControl::fDescriptionID("description");
const ControlID HaveProviderControl::fUserIDLabelID("useridlabel");
const ControlID HaveProviderControl::fUserIDID("userid");
const ControlID HaveProviderControl::fPasswordLabelID("passwordlabel");
const ControlID HaveProviderControl::fPasswordID("password");
const ControlID HaveProviderControl::ContinueID("continue");

/******************************************************************************/

ControlPtr HaveProviderControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new HaveProviderControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void HaveProviderControl::createControls()
{
	ControlPtr controlPtr;
	LabelControlPtr labelControlPtr;
	EditControlPtr editControlPtr;
	SelectControlPtr selectControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	top = 20;
	controlPtr = TextControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, top, fRect.getWidth() - 20, 56), NULL);
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 28;
	labelControlPtr = LabelControl::newInstance(fUserIDLabelID, fScreenID,
		RectWH(screenCenter - 255, top, 250, 0), "User ID:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	editControlPtr = EditControl::newInstance(fUserIDID, fScreenID,
		RectWH(screenCenter + 5, top, 198, 0));
	editControlPtr->setType(ect_UpperAlphaNumeric);
	editControlPtr->setMaxLength(9);
	editControlPtr->setFocus(true);
	newControl(editControlPtr);

	top += 40;
	labelControlPtr = LabelControl::newInstance(fPasswordLabelID, fScreenID,
		RectWH(screenCenter - 255, top, 250, 0), "Password:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	editControlPtr = EditControl::newInstance(fPasswordID, fScreenID,
		RectWH(screenCenter + 5, top, 132, 0));
	editControlPtr->setType(ect_Numeric);
	editControlPtr->setMaxLength(6);
	newControl(editControlPtr);

	controlPtr = ButtonControl::newInstance(ContinueID, fScreenID,
		RectWH(screenCenter - 60, fRect.getHeight() - 50, 120, 38), "Continue");
	newControl(controlPtr);
}

/******************************************************************************/

bool HaveProviderControl::loadData(ObjectPtr objectPtr)
{
	RentDataPtr rentDataPtr = objectPtr;
	TextControlPtr textControlPtr;
	CStr256 tempStr;

	textControlPtr = getControl(fDescriptionID);
	tempStr.copy("Please enter your logon information for ");
	tempStr.concat(rentDataPtr->getProviderName());
	tempStr.concat(":");
	textControlPtr->setText(tempStr.c_str());

	return true;
}

/******************************************************************************/

bool HaveProviderControl::unloadData(ObjectPtr objectPtr)
{
	EditControlPtr editControlPtr;
	SelectControlPtr selectControlPtr;
	RentDataPtr rentDataPtr = objectPtr;
	CStr256 tempStr;

	editControlPtr = getControl(fUserIDID);
	tempStr.copy(editControlPtr->getText());
	tempStr.compress(csw_Trailing);
	if(!tempStr.hasLen())
	{
		MessageScreen::newInstance(mp_OK, "User ID must be entered.");
		return false;
	}
	rentDataPtr->setUserID(tempStr.c_str());

	editControlPtr = getControl(fPasswordID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "Password must be entered.");
		return false;
	}
	rentDataPtr->setPassword(editControlPtr->getText());

	return true;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
