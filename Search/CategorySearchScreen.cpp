/* CategorySearchScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "TextListControl.h"
#include "CategorySearchScreen.h"
#include "SearchResultsScreen.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID CategorySearchScreen::ID("Search010");

const ControlID CategorySearchScreen::fDescriptionID("description");
const ControlID CategorySearchScreen::fCategoriesID("categories");

/******************************************************************************/

CategorySearchScreen::CategorySearchScreen() : Screen(ID)
{
	fTitle.copy("Search");
}

/******************************************************************************/

void CategorySearchScreen::createControls()
{
	ControlPtr controlPtr;
	TextListControlPtr textListControlPtr;
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	int top;

	// create the controls
	top = 20;
	controlPtr = LabelControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, 20, fContentWidth - 20, 0),
		"Please select which Category(s) you would like to search:");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 5;
	textListControlPtr = TextListControl::newInstance(fCategoriesID, fScreenID,
		RectWH(120, top, fContentWidth - 240, fContentHeight - top - 5));
	textListControlPtr->setFocus(true);
	newControl(textListControlPtr);

	// load the Categories
	CategoryVector categoryVector;
	CategoryVector::const_iterator iter;

	sessionPtr->getCategoryVector(categoryVector);

	NameValuePairVector& itemVector = textListControlPtr->getItemVector();

	for(iter = categoryVector.begin(); iter != categoryVector.end(); ++iter)
		itemVector.push_back(NameValuePair::newInstance((*iter)->getCategoryID().c_str(), (*iter)->getName()));

	textListControlPtr->setFocusedItem(0);
}

/******************************************************************************/

void CategorySearchScreen::onButton(const ControlID& controlID)
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	ShowSearchVector showSearchVector;
	TextListControlPtr textListControlPtr = getControl(fCategoriesID);

	SearchDataPtr searchDataPtr = SearchData::newInstance();
	searchDataPtr->setCategoryID(CategoryID(textListControlPtr->getFocusedItemName().c_str()));

	if(sessionPtr->showSearch(searchDataPtr, showSearchVector))
		SearchResultsScreen::newInstance(showSearchVector);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
