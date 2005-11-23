/* SearchResultsScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SearchResultsScreen.h"
#include "ShowSearchListControl.h"
#include "SearchDetailScreen.h"
#include "PickProviderScreen.h"

using namespace asi;

/******************************************************************************/
/******************************************************************************/

const ScreenID SearchResultsScreen::ID("Search003");

const ControlID SearchResultsScreen::fShowListID("showlist");
const ControlID SearchResultsScreen::fNoShowsTextID("noshows");

/******************************************************************************/

SearchResultsScreen::SearchResultsScreen(const ShowSearchVector& showSearchVector)
	: Screen(ID)
{
	fTitle.copy("Search");
	fShowSearchVector.copy(showSearchVector);
}

/******************************************************************************/

void SearchResultsScreen::createControls()
{
	if(fShowSearchVector.size() > 0)
	{
		ShowSearchListControlPtr showSearchListControlPtr = ShowSearchListControl::newInstance(
			fShowListID, getScreenID(), RectWH(10, 15, fContentWidth - 20, fContentHeight - 25));
		showSearchListControlPtr->setFocus(true);
		newControl(showSearchListControlPtr);

		showSearchListControlPtr->setShowSearchVector(fShowSearchVector);
	}
	else
	{
		int top = 20;
		ControlPtr controlPtr = TextControl::newInstance(fNoShowsTextID, getScreenID(), RectWH(10,
			top, fContentWidth - 20, 196), "No shows were found matching your search criteria.  Please try again.");
		newControl(controlPtr);
	}
}

/******************************************************************************/

void SearchResultsScreen::onButton(const ControlID& controlID)
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();

	if(controlID == fShowListID)
	{
		ShowSearchListControlPtr showSearchListControlPtr = getControl(fShowListID);
		ShowSearchPtr showSearchPtr = showSearchListControlPtr->getFocusedItemValue();

		ShowDetailPtr showDetailPtr = sessionPtr->showDetail(showSearchPtr->getShowID());
		if(!showDetailPtr.isNull())
			SearchDetailScreen::newInstance(showDetailPtr);

		return;
	}

	Screen::onButton(controlID);
}

/******************************************************************************/
/******************************************************************************/
