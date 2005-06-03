/* SetupScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SetupScreen.h"
#include "AskSignedUpControl.h"
#include "RecreateSettingsControl.h"
#include "SerialNoPinControl.h"
#include "NameAddressControl.h"
#include "StorePasswordsControl.h"
#include "IncludeAdultControl.h"
#include "MemCardLoadScreen.h"
#include "MemCardSaveScreen.h"

namespace asi
{

/******************************************************************************/

enum SetupStep
{
	ss_AskSignupStep = 0,
	ss_RecreateSettingsStep,
	ss_SerialNoPinStep,
	ss_NameAddressStep,
	ss_StorePasswordsStep,
	ss_IncludeAdultStep
};

/******************************************************************************/
/******************************************************************************/

const ScreenID SetupScreen::ID("Setup001");

const ControlID SetupScreen::fStepControlID("stepcontrol");

/******************************************************************************/

SetupScreen::SetupScreen() : Screen(ID)
{
	fTitle.copy("Setup");
	fSetupDataPtr = SetupData::newInstance();
	fCurStep = ss_AskSignupStep;
	fSignonNeeded = false;
}

/******************************************************************************/

bool SetupScreen::newInstance()
{
	SetupScreenPtr setupScreenPtr;
	
	setupScreenPtr = Screen::newInstance(new SetupScreen());
	MainApp::getThe()->modelLoop(ID);

	return setupScreenPtr->getSignonNeeded();
}

/******************************************************************************/

void SetupScreen::createControls()
{
	openStep(ss_AskSignupStep);
}

/******************************************************************************/

void SetupScreen::openStep(int step)
{
	ContainerControlPtr containerControlPtr;

	switch(step)
	{
		case ss_AskSignupStep:
		default:
			containerControlPtr = AskSignedUpControl::newInstance(fStepControlID, getScreenID(),
				RectWH(0, 0, fContentWidth, fContentHeight));
			break;
		case ss_RecreateSettingsStep:
			containerControlPtr = RecreateSettingsControl::newInstance(fStepControlID, getScreenID(),
				RectWH(0, 0, fContentWidth, fContentHeight));
			break;
		case ss_SerialNoPinStep:
			containerControlPtr = SerialNoPinControl::newInstance(fStepControlID, getScreenID(),
				RectWH(0, 0, fContentWidth, fContentHeight));
			break;
		case ss_NameAddressStep:
			containerControlPtr = NameAddressControl::newInstance(fStepControlID, getScreenID(),
				RectWH(0, 0, fContentWidth, fContentHeight));
			break;
		case ss_StorePasswordsStep:
			containerControlPtr = StorePasswordsControl::newInstance(fStepControlID, getScreenID(),
				RectWH(0, 0, fContentWidth, fContentHeight));
			break;
		case ss_IncludeAdultStep:
			containerControlPtr = IncludeAdultControl::newInstance(fStepControlID, getScreenID(),
				RectWH(0, 0, fContentWidth, fContentHeight));
			break;
	}

	containerControlPtr->setFocus(true);
	newControl(containerControlPtr);
	fCurStep = step;
	containerControlPtr->loadData(fSetupDataPtr);
}

/******************************************************************************/

bool SetupScreen::closeStep(bool doUnload)
{
	if(doUnload)
	{
		ContainerControlPtr containerControlPtr = getControl(fStepControlID);
		if(!containerControlPtr->unloadData(fSetupDataPtr))
			return false;
	}

	deleteControl(fStepControlID);
	return true;
}

/******************************************************************************/

bool SetupScreen::key(int key)
{
	ContainerControlPtr containerControlPtr;

	if(key == ek_Back)
	{
		if(fCurStep == ss_RecreateSettingsStep)
		{
			if(closeStep(false))
				openStep(ss_AskSignupStep);

			return true;
		}
		else if(fCurStep == ss_SerialNoPinStep)
		{
			if(closeStep(false))
				openStep(ss_AskSignupStep);

			return true;
		}
		else if(fCurStep == ss_NameAddressStep)
		{
			if(closeStep(false))
				openStep(ss_SerialNoPinStep);

			return true;
		}
		else if(fCurStep == ss_StorePasswordsStep)
		{
			if(closeStep(false))
				openStep(ss_NameAddressStep);

			return true;
		}
		else if(fCurStep == ss_IncludeAdultStep)
		{
			if(closeStep(false))
				openStep(ss_StorePasswordsStep);

			return true;
		}
	}

	return Screen::key(key);
}

/******************************************************************************/

void SetupScreen::onButton(const ControlID& controlID)
{
	if(fCurStep == ss_AskSignupStep)
	{
		if(controlID == AskSignedUpControl::SignUpNowID)
		{
			if(canPingServer())
				if(closeStep())
					openStep(ss_SerialNoPinStep);

			return;
		}
		else if(controlID == AskSignedUpControl::LoadSettingsID)
		{
			if(loadSettingsFromMemoryCard())
			{
				fSignonNeeded = true;
				close();
			}

			return;
		}
		else if(controlID == AskSignedUpControl::RecreateSettingsID)
		{
			if(canPingServer())
				if(closeStep())
					openStep(ss_RecreateSettingsStep);
			return;
		}
	}
	else if(fCurStep == ss_RecreateSettingsStep)
	{
		if(controlID == RecreateSettingsControl::ContinueID)
		{
			onRecreateSettingsButton();
			return;
		}
	}
	else if(fCurStep == ss_SerialNoPinStep)
	{
		if(controlID == SerialNoPinControl::ContinueID)
		{
			onSerialNoPinButton();
			return;
		}
	}
	else if(fCurStep == ss_NameAddressStep)
	{
		if(controlID == NameAddressControl::ContinueID)
		{
			if(closeStep())
				openStep(ss_StorePasswordsStep);
			return;
		}
	}
	else if(fCurStep == ss_StorePasswordsStep)
	{
		onStorePasswordsButton(controlID);
		return;
	}
	else if(fCurStep == ss_IncludeAdultStep)
	{
		onIncludeAdultButton(controlID);
		return;
	}

	Screen::onButton(controlID);
}

/******************************************************************************/

bool SetupScreen::canPingServer()
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();

	if(!sessionPtr->canPingServer())
		if(!sessionPtr->pingServer())
			return false;

	return true;
}

/******************************************************************************/

bool SetupScreen::loadSettingsFromMemoryCard()
{
	MainAppPtr mainAppPtr = MainApp::getThe();
	SessionPtr sessionPtr = mainAppPtr->getSession();
	MemoryCardSlot useMemCard;
		
	while(true)
	{
		useMemCard = MemCardLoadScreen::newInstance();
		if(useMemCard == mc_Undefined)	// cancelled
			return false;

		if(sessionPtr->loadMemCardSettings(useMemCard))
			return true;
		else
			MessageScreen::newInstance(mp_OK, "No settings were found on the Memory Card.");
	}
}

/******************************************************************************/

void SetupScreen::saveSettingsToMemoryCard()
{
	MainAppPtr mainAppPtr = MainApp::getThe();
	SessionPtr sessionPtr = mainAppPtr->getSession();

	MemoryCardSlot useMemCard = MemCardSaveScreen::newInstance();
	if(useMemCard == mc_Undefined)	// cancelled
		return;

	if(!sessionPtr->saveMemCardSettings(useMemCard))
		MessageScreen::newInstance(mp_OK, "An error occured while saving your settings to the Memory Card.");
}

/******************************************************************************/

void SetupScreen::onRecreateSettingsButton()
{
	ContainerControlPtr containerControlPtr = getControl(fStepControlID);
	SessionPtr sessionPtr;
	StatusCode statusCode;

	if(containerControlPtr->unloadData(fSetupDataPtr))
	{
		sessionPtr = MainApp::getThe()->getSession();

		statusCode = sessionPtr->memberSignon(fSetupDataPtr->getUserID(), fSetupDataPtr->getUserPassword(),
			fSetupDataPtr->getRememberPassword());

		if(statusCode == sc_Success)
		{
			saveSettingsToMemoryCard();
			close();
			return;
		}

		sessionPtr->clearLogonInfo();
		if(statusCode == sc_InvalidUserID)
		{
			MessageScreen::newInstance(mp_OK, "The Serial Number and/or PIN entered is incorrect.  Please try again.");
		}
		else if(statusCode == sc_UserIDPasswordMismatch)
		{
			MessageScreen::newInstance(mp_OK, "This Serial Number has already been registered with iNetVOD but the PIN entered is incorrect.  Please try again.");
		}
		else
		{
			MessageScreen::newInstance(mp_OK, "Setup cannot continue due to an unexpected error that has occurred.");
		}
	}
}

/******************************************************************************/

void SetupScreen::onSerialNoPinButton()
{
	ContainerControlPtr containerControlPtr = getControl(fStepControlID);
	SessionPtr sessionPtr;
	StatusCode statusCode;

	if(containerControlPtr->unloadData(fSetupDataPtr))
	{
		sessionPtr = MainApp::getThe()->getSession();

		statusCode = sessionPtr->memberSignon(fSetupDataPtr->getUserID(), fSetupDataPtr->getUserPassword(),
			fSetupDataPtr->getRememberPassword());

		if(statusCode == sc_InvalidUserID)
		{
			if(closeStep(false))
				openStep(ss_NameAddressStep);
		}
		else if(statusCode == sc_Success)
		{
			MessageScreen::newInstance(mp_OK, "You are already registered with iNetVOD.  You will now be prompted for a Memory Card to save your settings.");
			saveSettingsToMemoryCard();
			close();
		}
		else if(statusCode == sc_UserIDPasswordMismatch)
		{
			MessageScreen::newInstance(mp_OK, "This Serial Number has already been registered with iNetVOD but the PIN entered is incorrect.  Please try again.");
		}
		else
		{
			MessageScreen::newInstance(mp_OK, "Setup cannot continue due to an unexpected error that has occurred.");
		}
	}
}

/******************************************************************************/

void SetupScreen::onStorePasswordsButton(const ControlID& controlID)
{
	if(controlID == StorePasswordsControl::StoreLocallyID)
	{
		fSetupDataPtr->setStorePasswords(spw_Locally);
	}
	else if(controlID == StorePasswordsControl::StoreServerID)
	{
		fSetupDataPtr->setStorePasswords(spw_Server);
	}
	else //if(controlID == StorePasswordsControl::NotStoredID)
	{
		fSetupDataPtr->setStorePasswords(spw_NotStored);
	}

	if(closeStep())
		openStep(ss_IncludeAdultStep);
}

/******************************************************************************/

void SetupScreen::onIncludeAdultButton(const ControlID& controlID)
{
	if(controlID == IncludeAdultControl::PromptPasswordID)
	{
		fSetupDataPtr->setIncludeAdult(ina_PromptPassword);
	}
	else if(controlID == IncludeAdultControl::AlwaysID)
	{
		fSetupDataPtr->setIncludeAdult(ina_Always);
	}
	else //if(controlID == IncludeAdultControl::NeverID)
	{
		fSetupDataPtr->setIncludeAdult(ina_Never);
	}

	SessionPtr sessionPtr = MainApp::getThe()->getSession();

	// enroll the user
	StatusCode statusCode = sessionPtr->memberEnroll(fSetupDataPtr);

	if(statusCode == sc_UserIDInUse)
	{
		MessageScreen::newInstance(mp_OK, "This Serial Number has already been registered with iNetVOD.");
		close();
		return;
	}
	else if(statusCode != sc_Success)
	{
		MessageScreen::newInstance(mp_OK, "Setup cannot continue due to an unexpected error that has occurred.");
		close();
		return;
	}

	// signon the user
	MessageScreen::newInstance(mp_OK, "You have been successfully signed up to the iNetVOD service.  You will now be logged into the system and prompted for a Memory Card to save your settings.");

	statusCode = sessionPtr->memberSignon(fSetupDataPtr->getUserID(), fSetupDataPtr->getUserPassword(),
		fSetupDataPtr->getRememberPassword());

	if(statusCode == sc_Success)
	{
		saveSettingsToMemoryCard();
	}
	else
		MessageScreen::newInstance(mp_OK, "We were unable to log you onto the system due to an unexpected error that has occurred.");

	close();
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
