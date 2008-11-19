/* WelcomeScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "WelcomeScreen.h"
#include "NowPlayingScreen.h"
#include "SearchResultsScreen.h"
#include "CategorySearchScreen.h"
#include "SearchScreen.h"
#include "PreferencesScreen.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID WelcomeScreen::ID("Welcome001");

const ControlID WelcomeScreen::fNowPlayingID("nowplaying");
const ControlID WelcomeScreen::fFeaturedID("featured");
const ControlID WelcomeScreen::fSearchByCategoryID("searchbycategory");
const ControlID WelcomeScreen::fSearchByNameID("searchbyname");
const ControlID WelcomeScreen::fPreferencesID("preferences");
const ControlID WelcomeScreen::fHelpLabelID("helplabel");
const ControlID WelcomeScreen::fHelpID("help");

/******************************************************************************/

WelcomeScreen::WelcomeScreen() : Screen(ID)
{
	fTitle.copy("Welcome");
}

/******************************************************************************/

void WelcomeScreen::createControls()
{
	ButtonControlPtr buttonControlPtr;
	LabelControlPtr labelControlPtr;
	TextControlPtr textControlPtr;
	
	Screen::createControls();

	buttonControlPtr = ButtonControl::newInstance(fNowPlayingID, getScreenID(),
		RectWH(30, 30, 300, 38), "Now Playing");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);

	buttonControlPtr = ButtonControl::newInstance(fFeaturedID, getScreenID(),
		RectWH(30, 75, 300, 38), "Featured");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);

	buttonControlPtr = ButtonControl::newInstance(fSearchByCategoryID, getScreenID(),
		RectWH(30, 120, 300, 38), "Search by Category");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);

	buttonControlPtr = ButtonControl::newInstance(fSearchByNameID, getScreenID(),
		RectWH(30, 165, 300, 38), "Search by Title");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);

	buttonControlPtr = ButtonControl::newInstance(fPreferencesID, getScreenID(),
		RectWH(30, 210, 300, 38), "Preferences");
	buttonControlPtr->setHorzAlign(ha_Left);
	newControl(buttonControlPtr);

	labelControlPtr = LabelControl::newInstance(fHelpLabelID, getScreenID(),
		RectWH(350, 30, fContentWidth - 360, 0), "Help");
	labelControlPtr->setFontID(gSmallWhiteFontID);
	newControl(labelControlPtr);

	textControlPtr = TextControl::newInstance(fHelpID, getScreenID(),
		RectWH(350, 70, fContentWidth - 360, fContentHeight - 40), NULL);
	textControlPtr->setFontID(gSmallWhiteFontID);
	newControl(textControlPtr);

	buttonControlPtr = getControl(fNowPlayingID);
	buttonControlPtr->setFocus(true);
}

/******************************************************************************/

void WelcomeScreen::onButton(const ControlID& controlID)
{
	if(controlID == fNowPlayingID)
	{
		NowPlayingScreen::newInstance();
		return;
	}
	
	if(controlID == fFeaturedID)
	{
		SessionPtr sessionPtr = MainApp::getThe()->getSession();
		ShowSearchVector showSearchVector;

		SearchDataPtr searchDataPtr = SearchData::newInstance();
		searchDataPtr->setCategoryID(Category::FeaturedCategoryID);

		if(sessionPtr->showSearch(searchDataPtr, showSearchVector))
			SearchResultsScreen::newInstance(showSearchVector);
		return;
	}

	if(controlID == fSearchByCategoryID)
	{
		CategorySearchScreen::newInstance();
		return;
	}

	if(controlID == fSearchByNameID)
	{
		SearchScreen::newInstance();
		return;
	}

	if(controlID == fPreferencesID)
	{
		PreferencesScreen::newInstance();
		return;
	}

	Screen::onButton(controlID);
}

/******************************************************************************/

void WelcomeScreen::onFocus(const ControlID& controlID)
{
	TextControlPtr textControlPtr = getControl(fHelpID);

	if(controlID == fNowPlayingID)
		textControlPtr->setText("\"Now Playing\" lists the shows that you have previously rented and have available for viewing.");
	else if(controlID == fFeaturedID)
		textControlPtr->setText("\"Featured\" lists shows that are currently featured.");
	else if(controlID == fSearchByCategoryID)
		textControlPtr->setText("Use \"Search by Category\" to find shows by a specific category.");
	else if(controlID == fSearchByNameID)
		textControlPtr->setText("Use \"Search by Title\" to find shows by a partial show title.");
	else if(controlID == fPreferencesID)
		textControlPtr->setText("\"Preferences\" allows you to update your Storm settings.");
	else
		textControlPtr->setText(NULL);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
