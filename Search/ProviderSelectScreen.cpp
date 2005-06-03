/* ProviderSelectScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "TextListControl.h"
#include "ProviderSelectScreen.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID ProviderSelectScreen::ID("Search001");

const ControlID ProviderSelectScreen::fDescriptionID("description");
const ControlID ProviderSelectScreen::fProvidersID("providers");

/******************************************************************************/

ProviderSelectScreen::ProviderSelectScreen(SearchDataPtr& searchDataPtr) : Screen(ID)
{
	fTitle.copy("Search");
	fSearchDataPtr = searchDataPtr;
}

/******************************************************************************/

void ProviderSelectScreen::newInstance(SearchDataPtr& searchDataPtr)
{
	Screen::newInstance(new ProviderSelectScreen(searchDataPtr));
	MainApp::getThe()->modelLoop(ID);
}

/******************************************************************************/

void ProviderSelectScreen::createControls()
{
	ControlPtr controlPtr;
	TextListControlPtr textListControlPtr;
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	int top;

	// create the controls
	top = 20;
	controlPtr = LabelControl::newInstance(fDescriptionID, fScreenID,
		RectWH(10, top, fContentWidth - 20, 0),
		"Please select the Provider(s) you would like to search:");
	newControl(controlPtr);

	top += controlPtr->getRect().getHeight() + 5;
	textListControlPtr = TextListControl::newInstance(fProvidersID, fScreenID,
		RectWH(120, top, fContentWidth - 240, fContentHeight - top - 5));
	textListControlPtr->setFocus(true);
	newControl(textListControlPtr);

	// load the Providers
	ProviderVector providerVector;
	ProviderVector::const_iterator iter;

	sessionPtr->getProviderVector(providerVector);

	NameValuePairVector& itemVector = textListControlPtr->getItemVector();
	itemVector.push_back(NameValuePair::newInstance(Provider::AllProvidersID.c_str(), sessionPtr->getProviderName(Provider::AllProvidersID)));
	itemVector.push_back(NameValuePair::newInstance(Provider::MyProvidersID.c_str(), sessionPtr->getProviderName(Provider::MyProvidersID)));

	for(iter = providerVector.begin(); iter != providerVector.end(); ++iter)
		itemVector.push_back(NameValuePair::newInstance((*iter)->getProviderID().c_str(), (*iter)->getName()));

	if(!fSearchDataPtr->getProviderID().isUndefined())
		textListControlPtr->setFocusedItemByName(fSearchDataPtr->getProviderID().c_str());
}

/******************************************************************************/

void ProviderSelectScreen::onButton(const ControlID& controlID)
{
	TextListControlPtr textListControlPtr = getControl(fProvidersID);
	fSearchDataPtr->setProviderID(ProviderID(textListControlPtr->getFocusedItemName().c_str()));

	close();
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
