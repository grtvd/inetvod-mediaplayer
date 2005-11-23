/* RentData.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RentData.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

RentData::RentData(const ShowDetailPtr& showDetailPtr)
{
	fShowDetailPtr = showDetailPtr;

	ShowProviderVector showProviderVector;
	showDetailPtr->getShowProviderVector(showProviderVector);

	ShowProviderPtr showProviderPtr = showProviderVector[0];		//TODO: just get first provider for now
	ShowCostVector showCostVector;
	showProviderPtr->getShowCostVector(showCostVector);
	fShowCostPtr = showCostVector[0];								//TODO: just get first show cost for now

	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	fProviderPtr = sessionPtr->getProvider(showProviderVector[0]->getProviderID());
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
