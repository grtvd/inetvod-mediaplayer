/* SearchScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SearchScreen.h"
#include "ProviderSelectScreen.h"
#include "CategorySelectScreen.h"
#include "RatingSelectScreen.h"
#include "SearchResultsScreen.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID SearchScreen::ID("Search006");

const ControlID SearchScreen::fDescriptionID("description");
const ControlID SearchScreen::fShowNameLabelID("shownamelabel");
const ControlID SearchScreen::fShowNameID("showname");
const ControlID SearchScreen::fSearchID("search");
const ControlID SearchScreen::fRefineTextID("refinetext");
const ControlID SearchScreen::fProviderLabelID("providerlabel");
const ControlID SearchScreen::fProviderID("provider");
const ControlID SearchScreen::fCategoryLabelID("categorylabel");
const ControlID SearchScreen::fCategoryID("category");
const ControlID SearchScreen::fRatingLabelID("ratinglabel");
const ControlID SearchScreen::fRatingID("rating");

/******************************************************************************/

SearchScreen::SearchScreen() : Screen(ID)
{
	fTitle.copy("Search");
	fSearchDataPtr = SearchData::newInstance();
}

/******************************************************************************/

void SearchScreen::createControls()
{
	ControlPtr controlPtr;
	LabelControlPtr labelControlPtr;
	EditControlPtr editControlPtr;
	ButtonControlPtr buttonControlPtr;
	SelectControlPtr selectControlPtr;
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	int top;
	int left;
	int center;

	top = 20;
	controlPtr = LabelControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, top, fContentWidth - 20, 0),
		"Please enter a partial title then Search:");
	newControl(controlPtr);

	top += 45;
	labelControlPtr = LabelControl::newInstance(fShowNameLabelID, fScreenID,
		RectWH(10, top, 70, 0), "Title:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);

	left = labelControlPtr->getRect().right + 10;
	editControlPtr = EditControl::newInstance(fShowNameID, fScreenID,
		RectWH(left, top, 320, 0));
	editControlPtr->setType(ect_UpperAlphaNumeric);
	editControlPtr->setFocus(true);
	newControl(editControlPtr);

	left = editControlPtr->getRect().right + 10;
	controlPtr = ButtonControl::newInstance(fSearchID, fScreenID,
		RectWH(left, top, 120, 0), "Search");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 30;
	controlPtr = LabelControl::newInstance(fRefineTextID, fScreenID,
		RectWH(10, top, fContentWidth - 20, 0),
		"You may also refine your search:");
	newControl(controlPtr);

	center = 200;

	top += 45;
	labelControlPtr = LabelControl::newInstance(fProviderLabelID, fScreenID,
		RectWH(10, top, center - 15, 0), "Provider:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);

	controlPtr = ButtonControl::newInstance(fProviderID, fScreenID,
		RectWH(center + 5, top, 200, 0), sessionPtr->getProviderName(fSearchDataPtr->getProviderID()));
	newControl(controlPtr);

	top += 45;
	labelControlPtr = LabelControl::newInstance(fCategoryLabelID, fScreenID,
		RectWH(10, top, center - 15, 0), "Category:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);

	controlPtr = ButtonControl::newInstance(fCategoryID, fScreenID,
		RectWH(center + 5, top, 200, 0), sessionPtr->getCategoryName(fSearchDataPtr->getCategoryID()));
	newControl(controlPtr);

	top += 45;
	labelControlPtr = LabelControl::newInstance(fRatingLabelID, fScreenID,
		RectWH(10, top, center - 15, 0), "Rating:");
	labelControlPtr->setHorzAlign(ha_Right);
	newControl(labelControlPtr);

	controlPtr = ButtonControl::newInstance(fRatingID, fScreenID,
		RectWH(center + 5, top, 200, 0), sessionPtr->getRatingName(fSearchDataPtr->getRatingID()));
	newControl(controlPtr);
}

/******************************************************************************/

void SearchScreen::onButton(const ControlID& controlID)
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	ButtonControlPtr buttonControlPtr;
	EditControlPtr editControlPtr;

	if(controlID == fSearchID)
	{
		ShowSearchVector showSearchVector;

		editControlPtr = getControl(fShowNameID);
		fSearchDataPtr->setPartialName(editControlPtr->getText());

		if(sessionPtr->showSearch(fSearchDataPtr, showSearchVector))
			SearchResultsScreen::newInstance(showSearchVector);
		return;
	}
	
	if(controlID == fProviderID)
	{
		ProviderSelectScreen::newInstance(fSearchDataPtr);

		buttonControlPtr = getControl(fProviderID);
		buttonControlPtr->setText(sessionPtr->getProviderName(fSearchDataPtr->getProviderID()));
		return;
	}
	
	if(controlID == fCategoryID)
	{
		CategorySelectScreen::newInstance(fSearchDataPtr);

		buttonControlPtr = getControl(fCategoryID);
		buttonControlPtr->setText(sessionPtr->getCategoryName(fSearchDataPtr->getCategoryID()));
		return;
	}
	
	if(controlID == fRatingID)
	{
		RatingSelectScreen::newInstance(fSearchDataPtr);

		buttonControlPtr = getControl(fRatingID);
		buttonControlPtr->setText(sessionPtr->getRatingName(fSearchDataPtr->getRatingID()));
		return;
	}

	Screen::onButton(controlID);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
