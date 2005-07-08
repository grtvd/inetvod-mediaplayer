/* RentedShowDetailScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentedShowDetailScreen.h"
#include "NowPlayingScreen.h"

using namespace asi;

/******************************************************************************/
/******************************************************************************/

const ScreenID RentedShowDetailScreen::ID("Search004");

const ControlID RentedShowDetailScreen::fNameID("name");
const ControlID RentedShowDetailScreen::fEpisodeID("episode");
const ControlID RentedShowDetailScreen::fReleasedLabelID("releasedlabel");
const ControlID RentedShowDetailScreen::fReleasedID("released");
const ControlID RentedShowDetailScreen::fDescriptionID("description");
const ControlID RentedShowDetailScreen::fRunningMinsLabelID("runningminslabel");
const ControlID RentedShowDetailScreen::fRunningMinsID("runningmins");
const ControlID RentedShowDetailScreen::fCategoryLabelID("categorylabel");
const ControlID RentedShowDetailScreen::fCategoryID("category");
const ControlID RentedShowDetailScreen::fProviderLabelID("providerlabel");
const ControlID RentedShowDetailScreen::fProviderID("provider");
const ControlID RentedShowDetailScreen::fCostLabelID("costlabel");
const ControlID RentedShowDetailScreen::fCostID("cost");
const ControlID RentedShowDetailScreen::fRentalHoursLabelID("rentalhourslabel");
const ControlID RentedShowDetailScreen::fRentalHoursID("rentalhours");
const ControlID RentedShowDetailScreen::fRentedOnLabelID("rentedonlabelid");
const ControlID RentedShowDetailScreen::fRentedOnID("rentedonid");
const ControlID RentedShowDetailScreen::fAvailableUntilLabelID("availableuntillabelid");
const ControlID RentedShowDetailScreen::fAvailableUntilID("availableuntilid");
const ControlID RentedShowDetailScreen::fWatchNowID("watchnow");
const ControlID RentedShowDetailScreen::fDeleteNowID("deletenow");

/******************************************************************************/

RentedShowDetailScreen::RentedShowDetailScreen(const RentedShowPtr& rentedShowPtr)
	: Screen(ID)
{
	fTitle.copy("Now Playing");
	fRentedShowPtr = rentedShowPtr;
}

/******************************************************************************/

void RentedShowDetailScreen::createControls()
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
		RectWH(10, top, fContentWidth - 20, 0), fRentedShowPtr->getName());
	newControl(controlPtr);
	top += 40;

	if(tStrHasLen(fRentedShowPtr->getEpisodeName()) || tStrHasLen(fRentedShowPtr->getEpisodeNumber()))
	{
		tempStr.copy("Episode: ");
		if(tStrHasLen(fRentedShowPtr->getEpisodeName()))
		{
			tempStr.concat(fRentedShowPtr->getEpisodeName());
			if(tStrHasLen(fRentedShowPtr->getEpisodeNumber()))
				tempStr.concatVarg(" (%s)", fRentedShowPtr->getEpisodeNumber());
		}
		else
			tempStr.concat(fRentedShowPtr->getEpisodeNumber());

		labelControlPtr = LabelControl::newInstance(fEpisodeID, fScreenID,
			RectWH(10, top, fContentWidth - 20, 18), tempStr.c_str());
		labelControlPtr->setFontID(gSmallWhiteFontID);
		newControl(labelControlPtr);
		top += 30;
	}

	textControlPtr = TextControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, top, fContentWidth - 20, 120), fRentedShowPtr->getDescription());
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

	tempStr.clear();
	if(!fRentedShowPtr->getReleasedOn().isUndefined())
		tempStr.copy(fRentedShowPtr->getReleasedOn().c_str(dtf_MM_DD_YYYY));
	else if(!fRentedShowPtr->getReleasedYear().isUndefined())
		tempStr.copy(fRentedShowPtr->getReleasedYear().c_str());
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

	tempStr.clear();
	if(!fRentedShowPtr->getRunningMins().isUndefined())
		tempStr.copyVarg("%s mins.", fRentedShowPtr->getRunningMins().c_str());
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
	fRentedShowPtr->getCategoryIDVector(categoryIDVector);
	tempStr = sessionPtr->getCategoryNames(categoryIDVector);
	textControlPtr = TextControl::newInstance(fCategoryID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, 0), tempStr.c_str());
	textControlPtr->setFontID(gSmallWhiteFontID);
	textControlPtr->setVisibleLines(3);
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
		sessionPtr->getProviderName(fRentedShowPtr->getProviderID()));
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);
	top += 20;

	labelControlPtr = LabelControl::newInstance(fCostLabelID, fScreenID,
		RectWH(tempAlign - 125, top, labelWidth, 20), "Cost:");
	labelControlPtr->setHorzAlign(ha_Right);
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	labelControlPtr = LabelControl::newInstance(fCostID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, 20),
		fRentedShowPtr->getCost()->getCostDisplay());
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);
	top += 20;

	labelControlPtr = LabelControl::newInstance(fRentalHoursLabelID, fScreenID,
		RectWH(tempAlign - 125, top, labelWidth, 20), "Rental Period:");
	labelControlPtr->setHorzAlign(ha_Right);
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	tempStr.copyVarg("%s hrs.", fRentedShowPtr->getRentalHours().c_str());
	labelControlPtr = LabelControl::newInstance(fRentalHoursID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, 20),
		tempStr.c_str());
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);
	top += 20;

	labelControlPtr = LabelControl::newInstance(fRentedOnLabelID, fScreenID,
		RectWH(tempAlign - 125, top, labelWidth, 20), "Rented On:");
	labelControlPtr->setHorzAlign(ha_Right);
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	labelControlPtr = LabelControl::newInstance(fRentedOnID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, 20),
		fRentedShowPtr->getRentedOn().c_str(dtf_M_D_H_MM_AM));
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);
	top += 20;

	labelControlPtr = LabelControl::newInstance(fAvailableUntilLabelID, fScreenID,
		RectWH(tempAlign - 125, top, labelWidth, 20), "Available Until:");
	labelControlPtr->setHorzAlign(ha_Right);
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	labelControlPtr = LabelControl::newInstance(fAvailableUntilID, fScreenID,
		RectWH(tempAlign, top, fieldWidth, 20),
		fRentedShowPtr->getAvailableUntil().c_str(dtf_M_D_H_MM_AM));
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	top = 325;
	controlPtr = ButtonControl::newInstance(fWatchNowID, fScreenID,
		RectWH(10, fContentHeight - 45, 140, 0), "Watch Now");
	controlPtr->setFocus(true);
	newControl(controlPtr);

	controlPtr = ButtonControl::newInstance(fDeleteNowID, fScreenID,
		RectWH(160, fContentHeight - 45, 140, 0), "Delete Now");
	newControl(controlPtr);

}

/******************************************************************************/

void RentedShowDetailScreen::onButton(const ControlID& controlID)
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();

	if(controlID == fWatchNowID)
	{
		WatchShowRespPtr watchShowRespPtr = sessionPtr->watchShow(fRentedShowPtr->getRentedShowID());
		MessageScreen::newInstance(mp_OK, "This demo player does not yet play audio or video content.");

		return;
	}
	else if(controlID == fDeleteNowID)
	{
		StatusCode statusCode = sessionPtr->releaseShow(fRentedShowPtr->getRentedShowID());

		if(statusCode == sc_Success)
		{
			NowPlayingScreenPtr nowPlayingScreenPtr = MainApp::getThe()->findScreen(NowPlayingScreen::ID);
			if(!nowPlayingScreenPtr.isNull())
				nowPlayingScreenPtr->removeRentedShow(fRentedShowPtr->getRentedShowID());

			close();
		}
		return;
	}

	Screen::onButton(controlID);
}

/******************************************************************************/
/******************************************************************************/
