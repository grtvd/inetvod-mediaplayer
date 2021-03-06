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
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	ShowProviderVector showProviderVector;
	ShowProviderPtr showProviderPtr;
	ShowCostVector showCostVector;
	
	fShowDetailPtr = showDetailPtr;

	fHasMultipleRentals = true;

	showDetailPtr->getShowProviderVector(showProviderVector);
	if(showProviderVector.size() == 1)
	{
		showProviderPtr = showProviderVector[0];
		showProviderPtr->getShowCostVector(showCostVector);
		if(showCostVector.size() == 1)
		{
			fHasMultipleRentals = false;
			fProviderPtr = sessionPtr->getProvider(showProviderPtr->getProviderID());
			fShowCostPtr = showCostVector[0];
		}
	}
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
