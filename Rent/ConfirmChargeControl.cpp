/* ConfirmChargeControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentData.h"
#include "ConfirmChargeControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID ConfirmChargeControl::fChargeTextID("chargetext");
const ControlID ConfirmChargeControl::ChargeAccountID("chargeaccountid");
const ControlID ConfirmChargeControl::DontChargeAccountID("dontchargeaccountid");

/******************************************************************************/

ControlPtr ConfirmChargeControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new ConfirmChargeControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void ConfirmChargeControl::createControls()
{
	ControlPtr controlPtr;
	ButtonControlPtr buttonControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	top = 20;
	controlPtr = TextControl::newInstance(fChargeTextID, fScreenID,
		RectWH(10, top, fRect.getWidth() - 20, 112), NULL);
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 28;
	buttonControlPtr = ButtonControl::newInstance(ChargeAccountID, fScreenID,
		RectWH(screenCenter - 175, top, 350, 38), "Yes, charge my account");
	buttonControlPtr->setHorzAlign(ha_Left);
	buttonControlPtr->setFocus(true);
	newControl(buttonControlPtr);

	top += buttonControlPtr->getRect().getHeight() + 6;
	buttonControlPtr = ButtonControl::newInstance(DontChargeAccountID, fScreenID,
		RectWH(screenCenter - 175, top, 350, 38), "No, don't charge my account");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);
}

/******************************************************************************/

bool ConfirmChargeControl::loadData(ObjectPtr objectPtr)
{
	RentDataPtr rentDataPtr = objectPtr;
	ShowCostPtr showCostPtr = rentDataPtr->getShowCost();
	TextControlPtr textControlPtr;
	CStr256 tempStr;

	textControlPtr = getControl(fChargeTextID);
	tempStr.copy("This show has a cost of ");
	tempStr.concat(showCostPtr->getCostDisplay());
	tempStr.concat(".  This cost will be charged to your account at ");
	tempStr.concat(rentDataPtr->getProviderName());
	tempStr.concat(".\r\rDo you wish to proceed?");
	textControlPtr->setText(tempStr.c_str());

	return true;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
