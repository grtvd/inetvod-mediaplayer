/* PickRentalControl.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "PickRentalControl.h"
#include "RentData.h"
#include "ShowProviderListControl.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ControlID PickRentalControl::fAvailTextID("availtext");
const ControlID PickRentalControl::fSelectTextID("selecttext");
const ControlID PickRentalControl::ProviderListID("providerlist");

/******************************************************************************/

ControlPtr PickRentalControl::newInstance(const ControlID& controlID,
	const ScreenID& screenID, const Rect& rect)
{
	ContainerControlPtr containerControlPtr = Control::newInstance(
		new PickRentalControl(controlID, screenID), rect);

	containerControlPtr->createControls();

	return containerControlPtr;
}

/******************************************************************************/

void PickRentalControl::createControls()
{
	ControlPtr controlPtr;
	int top;
	
	top = 20;
	controlPtr = TextControl::newInstance(fAvailTextID, fScreenID, 
		RectWH(10, top, fRect.getWidth() - 20, 56), NULL);
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight();
	controlPtr = TextControl::newInstance(fSelectTextID, fScreenID, 
		RectWH(50, top, fRect.getWidth() - 100, 28),
		"Please select your desired rental:");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 10;
	ShowProviderListControlPtr showProviderListControlPtr = ShowProviderListControl::newInstance(
		ProviderListID, fScreenID, RectWH(50, top, fRect.getWidth() - 100,
		fRect.getHeight() - top - 5));
	showProviderListControlPtr->setFocus(true);
	newControl(showProviderListControlPtr);
}

/******************************************************************************/

bool PickRentalControl::loadData(ObjectPtr objectPtr)
{
	RentDataPtr rentDataPtr = objectPtr;
	TextControlPtr textControlPtr;
	ShowProviderListControlPtr showProviderListControlPtr;
	ShowProviderVector showProviderVector;
	CStr256 tempStr;

	textControlPtr = getControl(fAvailTextID);
	tempStr.copy("'");
	tempStr.concat(rentDataPtr->getShowDetail()->getName());
	tempStr.concat("' is available through multiple rentals.");
	textControlPtr->setText(tempStr.c_str());

	showProviderListControlPtr = getControl(ProviderListID);
	rentDataPtr->getShowDetail()->getShowProviderVector(showProviderVector);
	showProviderListControlPtr->setShowProviderVector(showProviderVector);

	return true;
}

/******************************************************************************/

bool PickRentalControl::unloadData(ObjectPtr objectPtr)
{
	ShowProviderListControlPtr showProviderListControlPtr;
	ShowProviderItemPtr showProviderItemPtr;
	RentDataPtr rentDataPtr = objectPtr;

	showProviderListControlPtr = getControl(ProviderListID);
	showProviderItemPtr = showProviderListControlPtr->getFocusedItemValue();
	rentDataPtr->setRental(showProviderItemPtr->getProvider(), showProviderItemPtr->getShowCost());

	return true;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
