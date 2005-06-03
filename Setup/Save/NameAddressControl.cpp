/* NameAddressControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SetupData.h"
#include "NameAddressControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID NameAddressControl::fDescriptionID("description");
const ControlID NameAddressControl::fDescription2ID("description2");
const ControlID NameAddressControl::fNameLabelID("namelabel");
const ControlID NameAddressControl::fFirstNameID("firstname");
const ControlID NameAddressControl::fLastNameID("lastname");
const ControlID NameAddressControl::fAddressLabelID("addresslabel");
const ControlID NameAddressControl::fAddrStreet1ID("addrstreet1");
const ControlID NameAddressControl::fAddrStreet2ID("addrstreet2");
const ControlID NameAddressControl::fCityLabelID("citylabel");
const ControlID NameAddressControl::fCityID("city");
const ControlID NameAddressControl::fStateLabelID("statelabel");
const ControlID NameAddressControl::fStateID("state");
const ControlID NameAddressControl::fPostalCodeLabelID("postalcodelabel");
const ControlID NameAddressControl::fPostalCodeID("postalcode");
const ControlID NameAddressControl::fPhoneLabelID("phonelabel");
const ControlID NameAddressControl::fPhoneID("phone");
const ControlID NameAddressControl::ContinueID("continue");

/******************************************************************************/

NameAddressControl::NameAddressControl(const ControlID& controlID, const ScreenID& screenID)
 : ContainerControl(controlID, screenID)
{
	fTitle.copy("Sign-Up");
}

/******************************************************************************/

ControlPtr NameAddressControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new NameAddressControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void NameAddressControl::createControls()
{
	ControlPtr controlPtr;
	LabelControlPtr labelControlPtr;
	EditControlPtr editControlPtr;
	SelectControlPtr selectControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int controlMidpoint = 130;
	int top;
	int left;

	top = 30;
	controlPtr = TextControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, top, fRect.getWidth() - 20, 20),
		"This wizard will guide you through the iNetVOD setup process.");
	newControl(controlPtr);

	top += 40;
	controlPtr = TextControl::newInstance(fDescription2ID, fScreenID,
		RectWH(10, top, fRect.getWidth() - 20, 20),
		"Please enter the following information:");
	newControl(controlPtr);

	top += 30;
	labelControlPtr = LabelControl::newInstance(fNameLabelID, fScreenID,
		RectWH(controlMidpoint - 120 - 5, top, 120, 0),
		"Name (F/L):");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	editControlPtr = EditControl::newInstance(fFirstNameID, fScreenID,
		RectWH(controlMidpoint + 5, top, 156, 0));
	editControlPtr->setMaxLength(15);
	newControl(editControlPtr);
	left = editControlPtr->getRect().right + 10;
	editControlPtr = EditControl::newInstance(fLastNameID, fScreenID,
		RectWH(left, top, 228, 0));
	editControlPtr->setMaxLength(31);
	newControl(editControlPtr);

	top += 40;
	labelControlPtr = LabelControl::newInstance(fAddressLabelID, fScreenID,
		RectWH(controlMidpoint - 120 - 5, top, 120, 0), "Address:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	editControlPtr = EditControl::newInstance(fAddrStreet1ID, fScreenID,
		RectWH(controlMidpoint + 5, top, 390, 0));
	editControlPtr->setMaxLength(63);
	newControl(editControlPtr);

	top += 40;
	editControlPtr = EditControl::newInstance(fAddrStreet2ID, fScreenID,
		RectWH(controlMidpoint + 5, top, 390, 0));
	editControlPtr->setMaxLength(63);
	newControl(editControlPtr);

	top += 40;
	labelControlPtr = LabelControl::newInstance(fCityLabelID, fScreenID,
		RectWH(controlMidpoint - 120 - 5, top, 120, 0), "City:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	editControlPtr = EditControl::newInstance(fCityID, fScreenID,
		RectWH(controlMidpoint + 5, top, 138, 0));
	editControlPtr->setMaxLength(63);
	newControl(editControlPtr);

	left = editControlPtr->getRect().right + 5;
	labelControlPtr = LabelControl::newInstance(fStateLabelID, fScreenID,
		RectWH(left, top, 35, 0), "ST:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	left += labelControlPtr->getRect().getWidth() + 5;
	editControlPtr = EditControl::newInstance(fStateID, fScreenID,
		RectWH(left, top, 48, 0));
	editControlPtr->setMaxLength(2);
	newControl(editControlPtr);

	left += editControlPtr->getRect().getWidth() + 5;
	labelControlPtr = LabelControl::newInstance(fPostalCodeLabelID, fScreenID,
		RectWH(left, top, 40, 0), "Zip:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	left += labelControlPtr->getRect().getWidth() + 5;
	editControlPtr = EditControl::newInstance(fPostalCodeID, fScreenID,
		RectWH(left, top, 102, 0));
	editControlPtr->setMaxLength(10);
	newControl(editControlPtr);

	top += 40;
	labelControlPtr = LabelControl::newInstance(fPhoneLabelID, fScreenID,
		RectWH(controlMidpoint - 120 - 5, top, 120, 0), "Phone:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);
	editControlPtr = EditControl::newInstance(fPhoneID, fScreenID,
		RectWH(controlMidpoint + 5, top, 372, 0));
	editControlPtr->setMaxLength(31);
	newControl(editControlPtr);


	controlPtr = ButtonControl::newInstance(ContinueID, fScreenID,
		RectWH(screenCenter - 60, fRect.getHeight() - 50, 120, 38), "Continue");
	newControl(controlPtr);
}

/******************************************************************************/

bool NameAddressControl::loadData(ObjectPtr objectPtr)
{
//TODO: BOB: TEST DATA REMOVE
	EditControlPtr editControlPtr;

	editControlPtr = getControl(fFirstNameID);
	editControlPtr->setText("Robert");

	editControlPtr = getControl(fLastNameID);
	editControlPtr->setText("Davidson");

	editControlPtr = getControl(fAddrStreet1ID);
	editControlPtr->setText("1000 Hoy Circle");

	editControlPtr = getControl(fCityID);
	editControlPtr->setText("Collegeville");

	editControlPtr = getControl(fStateID);
	editControlPtr->setText("PA");

	editControlPtr = getControl(fPostalCodeID);
	editControlPtr->setText("19426");

	editControlPtr = getControl(fPhoneID);
	editControlPtr->setText("610-489-4459");

//TODO: BOB: TEST DATA REMOVE
	return true;
}

/******************************************************************************/

bool NameAddressControl::unloadData(ObjectPtr objectPtr)
{
	EditControlPtr editControlPtr;
	SetupDataPtr setupDataPtr = objectPtr;

	editControlPtr = getControl(fFirstNameID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "First Name must be entered.");
		return false;
	}
	setupDataPtr->setFirstName(editControlPtr->getText());

	editControlPtr = getControl(fLastNameID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "Last Name must be entered.");
		return false;
	}
	setupDataPtr->setLastName(editControlPtr->getText());

	editControlPtr = getControl(fAddrStreet1ID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "Address must be entered.");
		return false;
	}
	setupDataPtr->setAddrStreet1(editControlPtr->getText());

	editControlPtr = getControl(fAddrStreet2ID);
	setupDataPtr->setAddrStreet2(editControlPtr->getText());

	editControlPtr = getControl(fCityID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "City must be entered.");
		return false;
	}
	setupDataPtr->setCity(editControlPtr->getText());

	editControlPtr = getControl(fStateID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "State must be entered.");
		return false;
	}
	setupDataPtr->setState(editControlPtr->getText());

	editControlPtr = getControl(fPostalCodeID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "Zip must be entered.");
		return false;
	}
	setupDataPtr->setPostalCode(editControlPtr->getText());

	editControlPtr = getControl(fPhoneID);
	if(!tStrHasLen(editControlPtr->getText()))
	{
		MessageScreen::newInstance(mp_OK, "Phone must be entered.");
		return false;
	}
	setupDataPtr->setPhone(editControlPtr->getText());

	return true;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
