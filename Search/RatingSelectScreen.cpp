/* RatingSelectScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "TextListControl.h"
#include "RatingSelectScreen.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID RatingSelectScreen::ID("Search008");

const ControlID RatingSelectScreen::fDescriptionID("description");
const ControlID RatingSelectScreen::fRatingsID("ratings");

/******************************************************************************/

RatingSelectScreen::RatingSelectScreen(SearchDataPtr& searchDataPtr) : Screen(ID)
{
	fTitle.copy("Search");
	fSearchDataPtr = searchDataPtr;
}

/******************************************************************************/

void RatingSelectScreen::newInstance(SearchDataPtr& searchDataPtr)
{
	Screen::newInstance(new RatingSelectScreen(searchDataPtr));
	MainApp::getThe()->modelLoop(ID);
}

/******************************************************************************/

void RatingSelectScreen::createControls()
{
	ControlPtr controlPtr;
	TextListControlPtr textListControlPtr;
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	int top;

	// create the controls
	top = 20;
	controlPtr = LabelControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, top, fContentWidth - 20, 0),
		"Please select which Rating(s) you would like to search:");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 5;
	textListControlPtr = TextListControl::newInstance(fRatingsID, fScreenID,
		RectWH(120, top, fContentWidth - 240, fContentHeight - top - 5));
	textListControlPtr->setFocus(true);
	newControl(textListControlPtr);

	// load the Ratings
	RatingVector ratingVector;
	RatingVector::const_iterator iter;

	sessionPtr->getRatingVector(ratingVector);

	NameValuePairVector& itemVector = textListControlPtr->getItemVector();
	itemVector.push_back(NameValuePair::newInstance(Rating::AllRatingsID.c_str(),
		sessionPtr->getRatingName(Rating::AllRatingsID)));

	for(iter = ratingVector.begin(); iter != ratingVector.end(); ++iter)
		itemVector.push_back(NameValuePair::newInstance((*iter)->getRatingID().c_str(), (*iter)->getName()));

	if(!fSearchDataPtr->getRatingID().isUndefined())
		textListControlPtr->setFocusedItemByName(fSearchDataPtr->getRatingID().c_str());
}

/******************************************************************************/

void RatingSelectScreen::onButton(const ControlID& controlID)
{
	TextListControlPtr textListControlPtr = getControl(fRatingsID);
	fSearchDataPtr->setRatingID(RatingID(textListControlPtr->getFocusedItemName().c_str()));

	close();
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
