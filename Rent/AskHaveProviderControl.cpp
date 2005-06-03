/* AskHaveProviderControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentData.h"
#include "AskHaveProviderControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID AskHaveProviderControl::fWelecomeTextID("welecometext");
const ControlID AskHaveProviderControl::fMembershipTextID("membershiptext");
const ControlID AskHaveProviderControl::HaveMembershipID("havemembership");
const ControlID AskHaveProviderControl::NeedMembershipID("needmembership");

/******************************************************************************/

ControlPtr AskHaveProviderControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new AskHaveProviderControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void AskHaveProviderControl::createControls()
{
	ControlPtr controlPtr;
	ButtonControlPtr buttonControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	top = 20;
	controlPtr = TextControl::newInstance(fWelecomeTextID, fScreenID, RectWH(10, top, fRect.getWidth() - 20, 56), NULL);
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 28;
	controlPtr = TextControl::newInstance(fMembershipTextID, fScreenID, RectWH(30, top, fRect.getWidth() - 40, 56), NULL);
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 28;
	buttonControlPtr = ButtonControl::newInstance(HaveMembershipID, fScreenID, RectWH(screenCenter - 175, top, 350, 38), "Yes, I already have a membership");
	buttonControlPtr->setHorzAlign(ha_Left);
	buttonControlPtr->setFocus(true);
	newControl(buttonControlPtr);

	top += buttonControlPtr->getRect().getHeight() + 6;
	buttonControlPtr = ButtonControl::newInstance(NeedMembershipID, fScreenID, RectWH(screenCenter - 175, top, 350, 38), "No, but please sign me up");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);
}

/******************************************************************************/

bool AskHaveProviderControl::loadData(ObjectPtr objectPtr)
{
	RentDataPtr rentDataPtr = objectPtr;
	TextControlPtr textControlPtr;
	CStr256 tempStr;

	textControlPtr = getControl(fWelecomeTextID);
	tempStr.copy("This show requires a membership with the provider, ");
	tempStr.concat(rentDataPtr->getProviderName());
	tempStr.concat(".");
	textControlPtr->setText(tempStr.c_str());

	textControlPtr = getControl(fMembershipTextID);
	tempStr.copy("Do you already have a membership with ");
	tempStr.concat(rentDataPtr->getProviderName());
	tempStr.concat("?");
	textControlPtr->setText(tempStr.c_str());

	return true;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
