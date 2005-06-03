/* PreferencesScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "PreferencesScreen.h"
#include "AskAdultPINScreen.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const ScreenID PreferencesScreen::ID("Prefs001");

const ControlID PreferencesScreen::fAccessAdultTextID("accessadulttext");
const ControlID PreferencesScreen::fAccessAdultValueID("accessadultvalue");
const ControlID PreferencesScreen::fAccessAdultButtonID("accessadultbutton");

/******************************************************************************/

PreferencesScreen::PreferencesScreen() : Screen(ID)
{
	fTitle.copy("Preferences");
}

/******************************************************************************/

void PreferencesScreen::createControls()
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	ButtonControlPtr buttonControlPtr;
	LabelControlPtr labelControlPtr;
	int top;
	int left;
	
	Screen::createControls();

	top = 30;
	left = 30;
	labelControlPtr = LabelControl::newInstance(fAccessAdultTextID, getScreenID(),
		RectWH(left, top, 130, 0), "Access Adult:");
	newControl(labelControlPtr);

	left += labelControlPtr->getRect().getWidth() + 10;
	labelControlPtr = LabelControl::newInstance(fAccessAdultValueID, getScreenID(),
		RectWH(left, top, 90, 0), sessionPtr->canAccessAdult() ? "Enabled" : "Disabled");
	newControl(labelControlPtr);

	if(!sessionPtr->canAccessAdult() && (sessionPtr->getIncludeAdult() == ina_PromptPassword))
	{
		left += labelControlPtr->getRect().getWidth() + 10;
		buttonControlPtr = ButtonControl::newInstance(fAccessAdultButtonID, getScreenID(),
			RectWH(left, top, 110, 38), "Enable");
		buttonControlPtr->setFocus(true);
		newControl(buttonControlPtr);
	}
}

/******************************************************************************/

void PreferencesScreen::onButton(const ControlID& controlID)
{
	if(controlID == fAccessAdultButtonID)
	{
		SessionPtr sessionPtr = MainApp::getThe()->getSession();

		AskAdultPINScreenPtr askAdultPINScreenPtr = AskAdultPINScreen::newInstance();
		if(tStrHasLen(askAdultPINScreenPtr->getAdultPassword()))
		{
			if(sessionPtr->enableAdultAccess(askAdultPINScreenPtr->getAdultPassword()) == sc_Success)
			{
				LabelControlPtr labelControlPtr = getControl(fAccessAdultValueID);
				labelControlPtr->setText("Enabled");

				deleteControl(fAccessAdultButtonID);
			}
		}

		return;
	}

	Screen::onButton(controlID);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
