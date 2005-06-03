/* CategorySelectScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "TextListControl.h"
#include "CategorySelectScreen.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID CategorySelectScreen::ID("Search002");

const ControlID CategorySelectScreen::fDescriptionID("description");
const ControlID CategorySelectScreen::fCategoriesID("categories");

/******************************************************************************/

CategorySelectScreen::CategorySelectScreen(SearchDataPtr& searchDataPtr) : Screen(ID)
{
	fTitle.copy("Search");
	fSearchDataPtr = searchDataPtr;
}

/******************************************************************************/

void CategorySelectScreen::newInstance(SearchDataPtr& searchDataPtr)
{
	Screen::newInstance(new CategorySelectScreen(searchDataPtr));
	MainApp::getThe()->modelLoop(ID);
}

/******************************************************************************/

void CategorySelectScreen::createControls()
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
	itemVector.push_back(NameValuePair::newInstance(Category::AllCategoriesID.c_str(), sessionPtr->getCategoryName(Category::AllCategoriesID)));

	for(iter = categoryVector.begin(); iter != categoryVector.end(); ++iter)
		itemVector.push_back(NameValuePair::newInstance((*iter)->getCategoryID().c_str(), (*iter)->getName()));

	if(!fSearchDataPtr->getCategoryID().isUndefined())
		textListControlPtr->setFocusedItemByName(fSearchDataPtr->getCategoryID().c_str());
}

/******************************************************************************/

void CategorySelectScreen::onButton(const ControlID& controlID)
{
	TextListControlPtr textListControlPtr = getControl(fCategoriesID);
	fSearchDataPtr->setCategoryID(CategoryID(textListControlPtr->getFocusedItemName().c_str()));

	close();
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
