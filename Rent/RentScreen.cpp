/* RentScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentScreen.h"
#include "AskHaveProviderControl.h"
#include "NeedProviderControl.h"
#include "HaveProviderControl.h"
#include "ConfirmChargeControl.h"

namespace asi
{

/******************************************************************************/

enum RentStep
{
	ss_Undefined = 0,
	ss_AskHaveProviderStep,
	ss_NeedProviderStep,
	ss_HaveProviderStep,
	ss_ConfirmChargeStep
};

/******************************************************************************/
/******************************************************************************/

const ScreenID RentScreen::ID("Rent001");

const ControlID RentScreen::fStepControlID("stepcontrol");

/******************************************************************************/

RentScreen::RentScreen(const ShowDetailPtr& showDetailPtr) : Screen(ID)
{
	fTitle.copy("Membership");
	fRentDataPtr = RentData::newInstance(showDetailPtr);
	fCurStep = ss_AskHaveProviderStep;
}

/******************************************************************************/

RentedShowID RentScreen::newInstance(const ShowDetailPtr& showDetailPtr)
{
	RentScreenPtr RentScreenPtr;
	
	RentScreenPtr = Screen::newInstance(new RentScreen(showDetailPtr));
	MainApp::getThe()->modelLoop(ID);

	return RentScreenPtr->getRentedShowID();
}

/******************************************************************************/

void RentScreen::createControls()
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	ShowDetailPtr showDetailPtr = fRentDataPtr->getShowDetail();

	if((showDetailPtr->getShowCost()->getShowCostType() == sct_Free) ||
		sessionPtr->isMemberOfProvider(fRentDataPtr->getProviderID()))
	{
		RentStep nextStep = checkShowAvail();
		if (nextStep == ss_Undefined)
			close();
		else
			openStep(nextStep);
	}
	else
		openStep(ss_AskHaveProviderStep);
}

/******************************************************************************/

void RentScreen::openStep(int step)
{
	ContainerControlPtr containerControlPtr;

	switch(step)
	{
		case ss_AskHaveProviderStep:
		default:
			containerControlPtr = AskHaveProviderControl::newInstance(fStepControlID, getScreenID(),
				RectWH(0, 0, fContentWidth, fContentHeight));
			break;
		case ss_NeedProviderStep:
			containerControlPtr = NeedProviderControl::newInstance(fStepControlID, getScreenID(),
				RectWH(0, 0, fContentWidth, fContentHeight));
			break;
		case ss_HaveProviderStep:
			containerControlPtr = HaveProviderControl::newInstance(fStepControlID, getScreenID(),
				RectWH(0, 0, fContentWidth, fContentHeight));
			break;
		case ss_ConfirmChargeStep:
			containerControlPtr = ConfirmChargeControl::newInstance(fStepControlID, getScreenID(),
				RectWH(0, 0, fContentWidth, fContentHeight));
			break;
	}

	containerControlPtr->setFocus(true);
	newControl(containerControlPtr);
	fCurStep = step;
	containerControlPtr->loadData(fRentDataPtr);
}

/******************************************************************************/

bool RentScreen::closeStep(bool doUnload)
{
	if(doUnload)
	{
		ContainerControlPtr containerControlPtr = getControl(fStepControlID);
		if(!containerControlPtr->unloadData(fRentDataPtr))
			return false;
	}

	deleteControl(fStepControlID);
	return true;
}

/******************************************************************************/

bool RentScreen::key(int key)
{
	ContainerControlPtr containerControlPtr;

	if(key == ek_Back)
	{
		if(fCurStep == ss_AskHaveProviderStep)
		{
			close();
			return true;
		}
		else if(fCurStep == ss_NeedProviderStep)
		{
			if(closeStep(false))
				openStep(ss_AskHaveProviderStep);

			return true;
		}
		else if(fCurStep == ss_HaveProviderStep)
		{
			if(closeStep(false))
			{
				SessionPtr sessionPtr = MainApp::getThe()->getSession();

				if(sessionPtr->isMemberOfProvider(fRentDataPtr->getProviderID()))
					close();
				else
					openStep(ss_AskHaveProviderStep);
			}

			return true;
		}
		else if(fCurStep == ss_ConfirmChargeStep)
		{
			close();
			return true;
		}
	}

	return Screen::key(key);
}

/******************************************************************************/

void RentScreen::onButton(const ControlID& controlID)
{
	if(fCurStep == ss_AskHaveProviderStep)
	{
		if(controlID == AskHaveProviderControl::HaveMembershipID)
		{
			if(closeStep())
				openStep(ss_HaveProviderStep);
			return;
		}
		else if(controlID == AskHaveProviderControl::NeedMembershipID)
		{
			if(closeStep())
				openStep(ss_NeedProviderStep);
			return;
		}
	}
	else if(fCurStep == ss_NeedProviderStep)
	{
		if(controlID == NeedProviderControl::CreateMembershipID)
		{
			if(closeStep())
			{
				RentStep nextStep = ss_Undefined;

				if(providerEnroll())
				{
					nextStep = checkShowAvail();
				}
				else
					nextStep = ss_NeedProviderStep;

				if (nextStep == ss_Undefined)
					close();
				else
					openStep(nextStep);
			}

			return;
		}
	}
	else if(fCurStep == ss_HaveProviderStep)
	{
		if(controlID == HaveProviderControl::ContinueID)
		{
			if(closeStep())
			{
				RentStep nextStep = ss_Undefined;

				if(setProvider())
					nextStep = checkShowAvail();
				else
					nextStep = ss_HaveProviderStep;

				if (nextStep == ss_Undefined)
					close();
				else
					openStep(nextStep);
			}

			return;
		}
	}
	else if(fCurStep == ss_ConfirmChargeStep)
	{
		if(controlID == ConfirmChargeControl::ChargeAccountID)
		{
			rentShow();
			if(!fRentedShowID.isUndefined())
				close();
			return;
		}
		else if(controlID == ConfirmChargeControl::DontChargeAccountID)
		{
			close();
			return;
		}
	}

	Screen::onButton(controlID);
}

/******************************************************************************/

RentStep RentScreen::checkShowAvail()
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	CheckShowAvailRespPtr checkShowAvailRespPtr;
	StatusCode statusCode;

	checkShowAvailRespPtr = sessionPtr->checkShowAvail(fRentDataPtr->getShowID(), fRentDataPtr->getProviderID(),
		statusCode);
	if(statusCode == sc_InvalidProviderUserIDPassword)
		return ss_HaveProviderStep;
	if(statusCode != sc_Success)
		return ss_Undefined;

	ShowCostPtr showCostPtr = checkShowAvailRespPtr->getShowCost();
	fRentDataPtr->setShowCost(showCostPtr);
	if(showCostPtr->getShowCostType() == sct_PayPerView)
		return ss_ConfirmChargeStep;

	rentShow();
	return ss_Undefined;
}

/******************************************************************************/

void RentScreen::rentShow()
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	RentShowRespPtr rentShowRespPtr;

	rentShowRespPtr = sessionPtr->rentShow(fRentDataPtr->getShowID(), fRentDataPtr->getProviderID(),
		fRentDataPtr->getShowCost());
	if(!rentShowRespPtr.isNull())
		fRentedShowID = rentShowRespPtr->getRentedShowID();
}

/******************************************************************************/

bool RentScreen::setProvider()
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	StatusCode statusCode;

	statusCode = sessionPtr->setProvider(fRentDataPtr->getShowDetail()->getProviderID(),
		fRentDataPtr->getUserID(), fRentDataPtr->getPassword());

	return (statusCode == sc_Success);
}

/******************************************************************************/

bool RentScreen::providerEnroll()
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	StatusCode statusCode;
	CStr256 tempStr;

	statusCode = sessionPtr->providerEnroll(fRentDataPtr->getShowDetail()->getProviderID());

	if(statusCode == sc_Success)
	{
		tempStr.copy("Congratulations! You have been successfully enrolled to ");
		tempStr.concat(fRentDataPtr->getProviderName());
		tempStr.concat("'s membership.");

		MessageScreen::newInstance(mp_OK, tempStr.c_str());
	}

	return true;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
