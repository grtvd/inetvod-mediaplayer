/* ShowProviderItem.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ShowProviderItem.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

ShowProviderItem::ShowProviderItem(const ProviderID& providerID, const ShowCostPtr& showCostPtr)
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();

	fProviderPtr = sessionPtr->getProvider(providerID);
	fShowCostPtr = showCostPtr;
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
