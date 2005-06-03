/* NowPlayingScreen.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "NowPlayingScreen.h"
#include "RentedShowListControl.h"
#include "RentedShowDetailScreen.h"

using namespace asi;

/******************************************************************************/
/******************************************************************************/

const ScreenID NowPlayingScreen::ID("Show002");

const ControlID NowPlayingScreen::fShowListID("showlist");
const ControlID NowPlayingScreen::fNoShowsTextID("noshows");

/******************************************************************************/

NowPlayingScreen::NowPlayingScreen() : Screen(ID)
{
	fTitle.copy("Now Playing");
}

/******************************************************************************/

ScreenPtr NowPlayingScreen::newInstance()
{
	NowPlayingScreen* pScreen = new NowPlayingScreen();
	try
	{
		if(pScreen->fetchData())
			return Screen::newInstance(pScreen);
	}
	catch(...)
	{
		delete pScreen;
		throw;
	}

	return ScreenPtr();
}

/******************************************************************************/

void NowPlayingScreen::removeRentedShow(const RentedShowID& rentedShowID)
{
	if(fRentedShowSearchVector.size() > 0)
		fRentedShowSearchVector.removeByID(rentedShowID);

	if(fRentedShowSearchVector.size() > 0)
	{
		RentedShowListControlPtr rentedShowListControlPtr = getControl(fShowListID);
		rentedShowListControlPtr->setRentedShowSearchVector(fRentedShowSearchVector);
	}
	else
	{
		deleteControl(fShowListID);
		createNoItemsControl();
	}
}

/******************************************************************************/

bool NowPlayingScreen::fetchData()
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	
	return (sessionPtr->rentedShowList(fRentedShowSearchVector) == sc_Success);
}

/******************************************************************************/

void NowPlayingScreen::createControls()
{
	if(fRentedShowSearchVector.size() > 0)
	{
		RentedShowListControlPtr rentedShowListControlPtr = RentedShowListControl::newInstance(
			fShowListID, getScreenID(), RectWH(10, 15, fContentWidth - 20, fContentHeight - 25));
		rentedShowListControlPtr->setFocus(true);
		rentedShowListControlPtr->setRentedShowSearchVector(fRentedShowSearchVector);
		newControl(rentedShowListControlPtr);
	}
	else
		createNoItemsControl();
}

/******************************************************************************/

void NowPlayingScreen::createNoItemsControl()
{
	int top = 20;
	ControlPtr controlPtr = TextControl::newInstance(fNoShowsTextID, getScreenID(), RectWH(10,
		top, fContentWidth - 20, 196), "Your Now Playing List is empty. Shows that you rent will be listed here.\n\nIt is a good idea to rent multiple shows at a time. This will allow new shows to be downloaded while you are watching another show.");
	newControl(controlPtr);
}

/******************************************************************************/

void NowPlayingScreen::onButton(const ControlID& controlID)
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();

	if(controlID == fShowListID)
	{
		RentedShowListControlPtr rentedShowListControlPtr = getControl(fShowListID);
		RentedShowPtr rentedShowPtr = sessionPtr->rentedShow(
			rentedShowListControlPtr->getFocusedItemValue()->getRentedShowID());

		if(!rentedShowPtr.isNull())
			RentedShowDetailScreen::newInstance(rentedShowPtr);

		return;
	}

	Screen::onButton(controlID);
}

/******************************************************************************/
/******************************************************************************/
