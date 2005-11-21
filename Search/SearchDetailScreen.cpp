/* SearchDetailScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SearchDetailScreen.h"
#include "RentScreen.h"
#include "RentedShowDetailScreen.h"

using namespace asi;

/******************************************************************************/
/******************************************************************************/

const ScreenID SearchDetailScreen::ID("Search004");

const ControlID SearchDetailScreen::fNameID("name");
const ControlID SearchDetailScreen::fEpisodeID("episode");
const ControlID SearchDetailScreen::fReleasedLabelID("releasedlabel");
const ControlID SearchDetailScreen::fReleasedID("released");
const ControlID SearchDetailScreen::fDescriptionID("description");
const ControlID SearchDetailScreen::fRunningMinsLabelID("runningminslabel");
const ControlID SearchDetailScreen::fRunningMinsID("runningmins");
const ControlID SearchDetailScreen::fCategoryLabelID("categorylabel");
const ControlID SearchDetailScreen::fCategoryID("category");
const ControlID SearchDetailScreen::fProviderLabelID("providerlabel");
const ControlID SearchDetailScreen::fProviderID("provider");
const ControlID SearchDetailScreen::fCostLabelID("costlabel");
const ControlID SearchDetailScreen::fCostID("cost");
const ControlID SearchDetailScreen::fRentalHoursLabelID("rentalhourslabel");
const ControlID SearchDetailScreen::fRentalHoursID("rentalhours");
const ControlID SearchDetailScreen::fRentNowID("rentnow");

/******************************************************************************/

SearchDetailScreen::SearchDetailScreen(const ShowDetailPtr& showDetailPtr)
	: Screen(ID)
{
	fTitle.copy("Search");
	fShowDetailPtr = showDetailPtr;
}

/******************************************************************************/

void SearchDetailScreen::createControls()
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	ControlPtr controlPtr;
	LabelControlPtr labelControlPtr;
	TextControlPtr textControlPtr;
	CStrVar tempStr;
	int top;
	int saveTop;
	int tempAlign;
	int labelWidth;
	int fieldWidth;

	top = 10;
	controlPtr = LabelControl::newInstance(fNameID, fScreenID,
		RectWH(10, top, fContentWidth - 20, 0), fShowDetailPtr->getName());
	newControl(controlPtr);
	top += 40;

	if(tStrHasLen(fShowDetailPtr->getEpisodeName()) || tStrHasLen(fShowDetailPtr->getEpisodeNumber()))
	{
		tempStr.clear();
		if(tStrHasLen(fShowDetailPtr->getEpisodeName()))
		{
			tempStr.copyVarg("\"%s\"", fShowDetailPtr->getEpisodeName());
			if(tStrHasLen(fShowDetailPtr->getEpisodeNumber()))
				tempStr.concatVarg(" (%s)", fShowDetailPtr->getEpisodeNumber());
		}
		else
			tempStr.copy(fShowDetailPtr->getEpisodeNumber());

		labelControlPtr = LabelControl::newInstance(fEpisodeID, fScreenID,
			RectWH(10, top, fContentWidth - 20, 18), tempStr.c_str());
		labelControlPtr->setFontID(gSmallWhiteFontID);
		newControl(labelControlPtr);
		top += 30;
	}

	textControlPtr = TextControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, top, fContentWidth - 20, 120), fShowDetailPtr->getDescription());
	textControlPtr->setFontID(gSmallWhiteFontID);
	newControl(textControlPtr);

	top = 205;
	saveTop = top;
	tempAlign = 120;
	labelWidth = tempAlign - 15;
	fieldWidth = 430 - 125 - 5 - tempAlign;

	labelControlPtr = LabelControl::newInstance(fReleasedLabelID, fScreenID,
		RectWH(10, top, labelWidth, 20), "Released:");
	labelControlPtr->setFontID(gSmallWhiteFontID);
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);

	tempStr.copy("n/a");
	if(!fShowDetailPtr->getReleasedOn().isUndefined())
		tempStr.copy(fShowDetailPtr->getReleasedOn().c_str(dtf_M_D_YYYY));
	else if(!fShowDetailPtr->getReleasedYear().isUndefined())
		tempStr.copy(fShowDetailPtr->getReleasedYear().c_str());
	labelControlPtr = LabelControl::newInstance(fReleasedID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, 20), tempStr.c_str());
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);
	top += 20;

	labelControlPtr = LabelControl::newInstance(fRunningMinsLabelID, fScreenID,
		RectWH(10, top, labelWidth, 20), "Running Time:");
	labelControlPtr->setHorzAlign(ha_Right);
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	tempStr.copy("n/a");
	if(!fShowDetailPtr->getRunningMins().isUndefined())
		tempStr.copyVarg("%s mins.", fShowDetailPtr->getRunningMins().c_str());
	labelControlPtr = LabelControl::newInstance(fRunningMinsID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, 20), tempStr.c_str());
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);
	top += 20;

	labelControlPtr = LabelControl::newInstance(fCategoryLabelID, fScreenID,
		RectWH(10, top, labelWidth, 20), "Categories:");
	labelControlPtr->setHorzAlign(ha_Right);
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	CategoryIDVector categoryIDVector;
	fShowDetailPtr->getCategoryIDVector(categoryIDVector);
	tempStr = sessionPtr->getCategoryNames(categoryIDVector);
	textControlPtr = TextControl::newInstance(fCategoryID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, fContentHeight - top - 10), tempStr.c_str());
	textControlPtr->setFontID(gSmallWhiteFontID);
	newControl(textControlPtr);

	top = saveTop;
	tempAlign = 430;
	labelWidth = 120;
	fieldWidth = fContentWidth - tempAlign - 10;

	labelControlPtr = LabelControl::newInstance(fProviderLabelID, fScreenID,
		RectWH(tempAlign - 125, top, labelWidth, 20), "Provider:");
	labelControlPtr->setHorzAlign(ha_Right);
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	labelControlPtr = LabelControl::newInstance(fProviderID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, 20),
		sessionPtr->getProviderName(fShowDetailPtr->getProviderID()));
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);
	top += 20;

	labelControlPtr = LabelControl::newInstance(fCostLabelID, fScreenID,
		RectWH(tempAlign - 125, top, labelWidth, 20), "Cost:");
	labelControlPtr->setHorzAlign(ha_Right);
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	ShowCostVector showCostVector;
	fShowDetailPtr->getShowCostVector(showCostVector);
	ShowCostPtr showCostPtr = showCostVector[0];	//TODO: Need to deal with multiple

	labelControlPtr = LabelControl::newInstance(fCostID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, 20), showCostPtr->getCostDisplay());
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);
	top += 20;

	labelControlPtr = LabelControl::newInstance(fRentalHoursLabelID, fScreenID,
		RectWH(tempAlign - 125, top, labelWidth, 20), "Rental Period:");
	labelControlPtr->setHorzAlign(ha_Right);
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	tempStr.copy("n/a");
	if(!showCostPtr->getRentalHours().isUndefined())
		tempStr.copyVarg("%s hrs.", showCostPtr->getRentalHours().c_str());
	labelControlPtr = LabelControl::newInstance(fRentalHoursID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, 20),
		tempStr.c_str());
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	top = 325;
	controlPtr = ButtonControl::newInstance(fRentNowID, fScreenID,
		RectWH(fContentWidth - 150, fContentHeight - 45, 140, 0), "Rent Now");
	controlPtr->setFocus(true);
	newControl(controlPtr);
}

/******************************************************************************/

void SearchDetailScreen::onButton(const ControlID& controlID)
{
	if(controlID == fRentNowID)
	{
		RentedShowID rentedShowID = RentScreen::newInstance(fShowDetailPtr);

		if(!rentedShowID.isUndefined())
		{
			SessionPtr sessionPtr = MainApp::getThe()->getSession();
			RentedShowPtr rentedShowPtr = sessionPtr->rentedShow(rentedShowID);

			MainApp::getThe()->closeAllScreens();

			if(!rentedShowPtr.isNull())
				RentedShowDetailScreen::newInstance(rentedShowPtr);
		}
		return;
	}
	
	Screen::onButton(controlID);
}

/******************************************************************************/
/******************************************************************************/
