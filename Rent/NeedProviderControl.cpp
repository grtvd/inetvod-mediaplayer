/* NeedProviderControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentData.h"
#include "NeedProviderControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID NeedProviderControl::fMemberTextID("membertext");
const ControlID NeedProviderControl::CreateMembershipID("createmembership");

/******************************************************************************/

ControlPtr NeedProviderControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new NeedProviderControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void NeedProviderControl::createControls()
{
	ControlPtr controlPtr;
	ButtonControlPtr buttonControlPtr;
	int screenCenter = fRect.getWidth() / 2;
	int top;

	top = 20;
	controlPtr = TextControl::newInstance(fMemberTextID, fScreenID,
		RectWH(10, top, fRect.getWidth() - 20, 280), NULL);
	newControl(controlPtr);

	buttonControlPtr = ButtonControl::newInstance(CreateMembershipID, fScreenID, RectWH(screenCenter - 150, fRect.getHeight() - 50, 300, 38), "Create Membership");
	buttonControlPtr->setFocus(true);
	newControl(buttonControlPtr);
}

/******************************************************************************/

bool NeedProviderControl::loadData(ObjectPtr objectPtr)
{
	RentDataPtr rentDataPtr = objectPtr;
	TextControlPtr textControlPtr;
	CStrVar tempStr;

	textControlPtr = getControl(fMemberTextID);
	tempStr.copy("Your Storm membership information will be used to create a new FREE membership at ");
	tempStr.concat(rentDataPtr->getProviderName());
	tempStr.concat(".  Your credit card information, if on file, will not be sent to ");
	tempStr.concat(rentDataPtr->getProviderName());
	tempStr.concat(".\r\r");
	tempStr.concat(rentDataPtr->getProviderName());
	tempStr.concat(" may have various member subscription plans that may be of interest to you.  Please visit the their site for more information.");
	textControlPtr->setText(tempStr.c_str());

	return true;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
