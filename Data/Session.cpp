/* Session.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "Session.h"
#include "DataRequestor.h"

namespace asi
{

/******************************************************************************/

Session::Session()
{
	fMemoryCardSlot = mc_Slot1;
	fNetworkInit = false;
	fNetworkHostName.copy("api.inetvod.com");
	fNetworkHostPort = 80;
	fNetworkHostPath.copy("/inetvod/playerapi/binary");
	memset(&fNetworkHost, 0, sizeof(fNetworkHost));
	fHaveNetworkHost = false;
	fCanPingServer = false;
	fIsUserLoggedOn = false;
	fIncludeAdult = ina_Never;
	fCanAccessAdult = false;

	fRememberPassword = false;
	fIsSystemDataLoaded = false;

	fPlayerPtr = Player::newInstance();
	fPlayerPtr->setManufacturerID(ManufacturerID("inetvod"));
	fPlayerPtr->setModelNo("ps2");
	fPlayerPtr->setSerialNo("1234567890");
	fPlayerPtr->setVersion("1.0.0000");
}

/******************************************************************************/

Session::~Session()
{
#if defined(WIN32)
	if(fNetworkInit)
		WSACleanup();
#endif
}

/******************************************************************************/

SessionPtr Session::newInstance()
{ 
	SessionPtr sessionPtr(new Session());

	// Network startup code
#if defined(WIN32)
	WSADATA wsaData;
	int rc = WSAStartup(MAKEWORD(1,1), &wsaData);
	if(rc != 0)
		throw ASIException("Session::Session", "WSAStartup() failed, error:%d", rc);
#endif
	sessionPtr->fNetworkInit = true;
	sessionPtr->loadAppSettings();

	return sessionPtr;
}

/******************************************************************************/

bool Session::loadAppSettings()
{
	FILE* fp;
	char data[1024];
	ushort dataShort;

	if((fp = fopen("app.config", "rt")) != NULL)
	{
		fNetworkHostPort = 0xffff;

		if(fscanf(fp, "%s", data) != EOF)
			fNetworkHostName.copy(data);
		if(fscanf(fp, "%hu", &dataShort) != EOF)
			fNetworkHostPort = dataShort;
		if(fscanf(fp, "%s", data) != EOF)
			fNetworkHostPath.copy(data);

		if(fscanf(fp, "%s", data) != EOF)
			fPlayerPtr->setManufacturerID(ManufacturerID(data));
		if(fscanf(fp, "%s", data) != EOF)
			fPlayerPtr->setModelNo(data);
		if(fscanf(fp, "%s", data) != EOF)
			fPlayerPtr->setSerialNo(data);
		if(fscanf(fp, "%s", data) != EOF)
			fPlayerPtr->setVersion(data);

		fclose(fp);

		return true;
	}

	return false;
}

/******************************************************************************/

const char* Session::getProviderName(const ProviderID& providerID) const
{
	ProviderPtr providerPtr;

	if(providerID == Provider::AllProvidersID)
		return Provider::AllProvidersName.c_str();

	if(providerID == Provider::MyProvidersID)
		return Provider::MyProvidersName.c_str();

	return fProviderVector.getByID(providerID)->getName();
}

/******************************************************************************/

const char* Session::getCategoryName(const CategoryID& categoryID)
{
	CategoryPtr categoryPtr;

	if(categoryID == Category::AllCategoriesID)
		return Category::AllCategoriesName.c_str();

	return fCategoryVector.getByID(categoryID)->getName();
}

/******************************************************************************/

CStrVar Session::getCategoryNames(const CategoryIDVector& categoryIDVector)
{
	CStrVar names;
	CategoryIDVector::const_iterator iter;

	for(iter = categoryIDVector.begin(); iter != categoryIDVector.end(); ++iter)
	{
		if(names.hasLen())
			names.concat(", ");
		names.concat(getCategoryName(*iter));
	}

	return names;
}

/******************************************************************************/

const char* Session::getRatingName(const RatingID& ratingID)
{
	RatingPtr ratingPtr;

	if(ratingID == Rating::AllRatingsID)
		return Rating::AllRatingsName.c_str();

	return fRatingVector.getByID(ratingID)->getName();
}

/******************************************************************************/

bool Session::loadMemCardSettings()
{
	CStr32 filename;
	FILE* fp;
	char userID[256];
	char userPassword[256];

	fUserID.clear();
	fUserPassword.clear();

	tPauseTenths(2);	//TODO: remove tests
	filename.copyVarg("MemCard%d.txt", fMemoryCardSlot);
	if((fp = fopen(filename.c_str(), "rt")) != NULL)
	{
		if(fscanf(fp, "%s", userID) != EOF)
			fUserID.copy(userID);
		if(fscanf(fp, "%s", userPassword) != EOF)
		{
			fUserPassword.copy(userPassword);
			fRememberPassword = true;
		}
		fclose(fp);

		return (fUserID.len() > 0);
	}

	return false;
}

/******************************************************************************/

bool Session::loadMemCardSettings(MemoryCardSlot memoryCardSlot)
{
	if((memoryCardSlot != mc_Slot1) && (memoryCardSlot != mc_Slot2))
		throw ASIException("Session::loadMemCardSettings", "Invalid memoryCardSlot");

	fMemoryCardSlot = memoryCardSlot;

	return loadMemCardSettings();
}

/******************************************************************************/

bool Session::findLoadMemCardSettings()
{
	bool success;

	success = loadMemCardSettings();
	if(!success)
	{
		if(fMemoryCardSlot == mc_Slot1)
			fMemoryCardSlot = mc_Slot2;
		else
			fMemoryCardSlot = mc_Slot1;

		success = loadMemCardSettings();
	}

	return success;
}

/******************************************************************************/

bool Session::saveMemCardSettings()
{
	CStr32 filename;
	FILE* fp;
	bool success = false;

	MainAppPtr mainAppPtr = MainApp::getThe();
	ScreenPtr waitScreenPtr = WaitScreen::newInstance("Please wait while your settings are saved...");
	//TODO: ScreenPtr waitScreenPtr = WaitScreen::newInstance("Please wait while your settings are save to the Memory Card. Do not remove the Memory Card or data could be lost.");
	try
	{
		mainAppPtr->processAvail();

		tPauseTenths(10);	//TODO: remove tests
		filename.copyVarg("MemCard%d.txt", fMemoryCardSlot);
		if((fp = fopen(filename.c_str(), "wt")) != NULL)
		{
			fprintf(fp, "%s\n", fUserID.c_str());
			if(fRememberPassword)
				fprintf(fp, "%s\n", fUserPassword.c_str());
			fclose(fp);

			success = true;
		}
	}
	CATCH_ERROR_NOACTION("Session::saveMemCardSettings")
	waitScreenPtr->close();

	return success;
}

/******************************************************************************/

bool Session::saveMemCardSettings(MemoryCardSlot memoryCardSlot)
{
	if((memoryCardSlot != mc_Slot1) && (memoryCardSlot != mc_Slot2))
		throw ASIException("Session::saveMemCardSettings", "Invalid memoryCardSlot");

	fMemoryCardSlot = memoryCardSlot;

	return saveMemCardSettings();
}

/******************************************************************************/

void Session::showRequestError(const char* message)
{
	if(!tStrHasLen(message))
		MessageScreen::newInstance(mp_OK, "An error occurred trying to communicate with the iNetVOD servers. Please check you network connection and try again.");
	else
		MessageScreen::newInstance(mp_OK, message);
}

/******************************************************************************/

bool Session::pingServer()
{
	StatusCode statusCode;
	CStrVar statusMessage;

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance();
		statusCode = dataRequestorPtr->pingRequest();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
		{
			fCanPingServer = true;
			return fCanPingServer;
		}

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::pingServer")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return fCanPingServer;
}

/******************************************************************************/

StatusCode Session::enroll(SetupDataPtr setupDataPtr)
{
	StatusCode statusCode = sc_GeneralError;

	EnrollRqstPtr enrollRqstPtr = EnrollRqst::newInstance();
	EnrollRespPtr enrollRespPtr;

	enrollRqstPtr->setUserID(setupDataPtr->getUserID());
	enrollRqstPtr->setPassword(setupDataPtr->getUserPassword());
	enrollRqstPtr->setFirstName(setupDataPtr->getFirstName());
	enrollRqstPtr->setLastName(setupDataPtr->getLastName());
	enrollRqstPtr->setAddrStreet1(setupDataPtr->getAddrStreet1());
	enrollRqstPtr->setAddrStreet2(setupDataPtr->getAddrStreet2());
	enrollRqstPtr->setCity(setupDataPtr->getCity());
	enrollRqstPtr->setState(setupDataPtr->getState());
	enrollRqstPtr->setPostalCode(setupDataPtr->getPostalCode());
	enrollRqstPtr->setPhone(setupDataPtr->getPhone());
	enrollRqstPtr->setBirthDate(setupDataPtr->getBirthDate());
	enrollRqstPtr->setCurrencyID(cur_USD);
	//TODO: MemberPrefsPtr

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance();
		enrollRespPtr = dataRequestorPtr->enrollRequest(enrollRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();
	}
	CATCH_ERROR_NOACTION("Session::enroll")
	waitScreenPtr->close();

	return statusCode;
}

/******************************************************************************/

StatusCode Session::signon()
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	fIsUserLoggedOn = false;

	if(fUserID.len() == 0)
		throw ASIException("Session::signon", "Missing UserID");
	if(fUserPassword.len() == 0)
		throw ASIException("Session::signon", "Missing UserPassword");

	SignonRqstPtr signonRqstPtr;
	SignonRespPtr signonRespPtr;
	
	signonRqstPtr = SignonRqst::newInstance();
	signonRqstPtr->setUserID(fUserID.c_str());
	signonRqstPtr->setPassword(fUserPassword.c_str());
	signonRqstPtr->setPlayer(fPlayerPtr);

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance();
		signonRespPtr = dataRequestorPtr->signonRequest(signonRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
		{
			fSessionData.copy(signonRespPtr->getSessionData());
			fSessionExpires = signonRespPtr->getSessionExpires();
			fMemberPrefsPtr = signonRespPtr->getMemberState()->getMemberPrefs();
			fIncludeAdult = fMemberPrefsPtr->getIncludeAdult();
			fCanAccessAdult = (fIncludeAdult == ina_Always);
			signonRespPtr->getMemberState()->getMemberProviderVector(fMemberProviderVector);

			fIsUserLoggedOn = true;
			return statusCode;
		}
		else if((statusCode == sc_UserIDPasswordMismatch) || (statusCode == sc_InvalidUserID))
			fUserPassword.clear();

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::signon")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return statusCode;
}

/******************************************************************************/

StatusCode Session::signon(const char* password)
{
	fUserPassword.copy(password);

	return signon();
}

/******************************************************************************/

StatusCode Session::signon(const char* password, bool rememberPassword)
{
	fUserPassword.copy(password);
	fRememberPassword = rememberPassword;

	return signon();
}

/******************************************************************************/

StatusCode Session::signon(const char* userID, const char* password, bool rememberPassword)
{
	fUserID.copy(userID);
	fUserPassword.copy(password);
	fRememberPassword = rememberPassword;

	return signon();
}

/******************************************************************************/

bool Session::isMemberOfProvider(const ProviderID& providerID)
{
	return !fMemberProviderVector.findByID(providerID).isNull();
}

/******************************************************************************/

bool Session::loadSystemData()
{
	StatusCode statusCode;
	CStrVar statusMessage;

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		SystemDataRespPtr systemDataRespPtr = dataRequestorPtr->systemDataRequest();
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
		{
			systemDataRespPtr->getProviderVector(fProviderVector);
			systemDataRespPtr->getCategoryVector(fCategoryVector);
			systemDataRespPtr->getRatingVector(fRatingVector);

			fIsSystemDataLoaded = true;
			return fIsSystemDataLoaded;
		}

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::loadSystemData")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return fIsSystemDataLoaded;
}

/******************************************************************************/

StatusCode Session::enableAdultAccess(const char* password)
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	EnableAdultAccessRqstPtr enableAdultAccessRqstPtr;
	EnableAdultAccessRespPtr enableAdultAccessRespPtr;
	
	enableAdultAccessRqstPtr = EnableAdultAccessRqst::newInstance();
	enableAdultAccessRqstPtr->setPassword(password);

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		enableAdultAccessRespPtr = dataRequestorPtr->enableAdultAccessRequest(enableAdultAccessRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
		{
			fCanAccessAdult = true;
			return statusCode;
		}

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::enableAdultAccess")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return statusCode;
}

/******************************************************************************/

bool Session::showSearch(const SearchDataPtr& searchDataPtr, ShowSearchVector& showSearchVector)
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	ShowSearchRqstPtr showSearchRqstPtr;
	ShowSearchRespPtr showSearchRespPtr;
	
	ProviderIDVector providerIDVector;
	CategoryIDVector categoryIDVector;
	RatingIDVector ratingIDVector;

	if(searchDataPtr->getProviderID() != Provider::AllProvidersID)
		providerIDVector.push_back(searchDataPtr->getProviderID());
	if(searchDataPtr->getCategoryID() != Category::AllCategoriesID)
		categoryIDVector.push_back(searchDataPtr->getCategoryID());
	if(searchDataPtr->getRatingID() != Rating::AllRatingsID)
		ratingIDVector.push_back(searchDataPtr->getRatingID());

	showSearchRqstPtr = ShowSearchRqst::newInstance();
	showSearchRqstPtr->setPartialName(searchDataPtr->getPartialName());
	showSearchRqstPtr->setProviderIDVector(providerIDVector);
	showSearchRqstPtr->setCategoryIDVector(categoryIDVector);
	showSearchRqstPtr->setRatingIDVector(ratingIDVector);
	//TODO: showSearchRqstPtr->setIncludeAdult();
	//TODO: showSearchRqstPtr->setShowFormatVector
	//TODO: showSearchRqstPtr->setDetails

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		showSearchRespPtr = dataRequestorPtr->showSearchRequest(showSearchRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
		{
			showSearchRespPtr->getShowSearchVector(showSearchVector);
			return true;
		}

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::showSearch")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return false;
}

/******************************************************************************/

ShowDetailPtr Session::showDetail(const ShowID& showID, const ProviderID& providerID)
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	ShowDetailRqstPtr showDetailRqstPtr;
	ShowDetailRespPtr showDetailRespPtr;
	
	showDetailRqstPtr = ShowDetailRqst::newInstance();
	showDetailRqstPtr->setShowID(showID);
	showDetailRqstPtr->setProviderID(providerID);

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		showDetailRespPtr = dataRequestorPtr->showDetailRequest(showDetailRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
			return showDetailRespPtr->getShowDetail();

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::showDetail")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return ShowDetailPtr();
}

/******************************************************************************/

StatusCode Session::providerEnroll(const ProviderID& providerID)
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	ProviderEnrollRqstPtr providerEnrollRqstPtr;
	
	providerEnrollRqstPtr = ProviderEnrollRqst::newInstance();
	providerEnrollRqstPtr->setProviderID(providerID);

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		statusCode = dataRequestorPtr->providerEnrollRequest(providerEnrollRqstPtr);

		waitScreenPtr->close();
		if(statusCode == sc_Success)
		{
			fMemberProviderVector.push_back(MemberProvider::newInstance(providerID));
			return sc_Success;
		}

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::providerEnroll")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return statusCode;
}

/******************************************************************************/

StatusCode Session::setProvider(const ProviderID& providerID, const char* userID, const char* password)
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	SetProviderRqstPtr setProviderRqstPtr;
	
	setProviderRqstPtr = SetProviderRqst::newInstance();
	setProviderRqstPtr->setProviderID(providerID);
	setProviderRqstPtr->setUserID(userID);
	setProviderRqstPtr->setPassword(password);

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		statusCode = dataRequestorPtr->setProviderRequest(setProviderRqstPtr);

		waitScreenPtr->close();
		if(statusCode == sc_Success)
			return sc_Success;

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::setProvider")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return statusCode;
}

/******************************************************************************/

CheckShowAvailRespPtr Session::checkShowAvail(const ShowID& showID, const ProviderID& providerID,
	StatusCode& statusCode)
{
	CStrVar statusMessage;

	statusCode = sc_GeneralError;

	CheckShowAvailRqstPtr checkShowAvailRqstPtr;
	CheckShowAvailRespPtr checkShowAvailRespPtr;
	
	checkShowAvailRqstPtr = CheckShowAvailRqst::newInstance();
	checkShowAvailRqstPtr->setShowID(showID);
	checkShowAvailRqstPtr->setProviderID(providerID);

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		checkShowAvailRespPtr = dataRequestorPtr->checkShowAvailRequest(checkShowAvailRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
			return checkShowAvailRespPtr;

		statusMessage = dataRequestorPtr->getStatusMessage();
	}
	CATCH_ERROR_NOACTION("Session::checkShowAvail")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return CheckShowAvailRespPtr();
}

/******************************************************************************/

RentShowRespPtr Session::rentShow(const ShowID& showID, const ProviderID& providerID,
	const ShowCostPtr& approvedCostPtr)
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	RentShowRqstPtr rentShowRqstPtr;
	RentShowRespPtr rentShowRespPtr;
	
	rentShowRqstPtr = RentShowRqst::newInstance();
	rentShowRqstPtr->setShowID(showID);
	rentShowRqstPtr->setProviderID(providerID);
	rentShowRqstPtr->setApprovedCost(approvedCostPtr);

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		rentShowRespPtr = dataRequestorPtr->rentShowRequest(rentShowRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
			return rentShowRespPtr;

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::rentShow")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return RentShowRespPtr();
}

/******************************************************************************/

StatusCode Session::rentedShowList(RentedShowSearchVector& rentedShowSearchVector)
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	rentedShowSearchVector.empty();

	RentedShowListRqstPtr rentedShowListRqstPtr;
	RentedShowListRespPtr rentedShowListRespPtr;
	
	rentedShowListRqstPtr = RentedShowListRqst::newInstance();

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		rentedShowListRespPtr = dataRequestorPtr->rentedShowListRequest(rentedShowListRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
		{
			rentedShowListRespPtr->getRentedShowSearchVector(rentedShowSearchVector);
			return sc_Success;
		}

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::rentedShowList")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return statusCode;
}

/******************************************************************************/

RentedShowPtr Session::rentedShow(const RentedShowID& rentedShowID)
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	RentedShowRqstPtr rentedShowRqstPtr;
	RentedShowRespPtr rentedShowRespPtr;
	
	rentedShowRqstPtr = RentedShowRqst::newInstance();
	rentedShowRqstPtr->setRentedShowID(rentedShowID);

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		rentedShowRespPtr = dataRequestorPtr->rentedShowRequest(rentedShowRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
			return rentedShowRespPtr->getRentedShow();

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::rentedShow")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return RentedShowPtr();
}

/******************************************************************************/

WatchShowRespPtr Session::watchShow(const RentedShowID& rentedShowID)
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	WatchShowRqstPtr watchShowRqstPtr;
	WatchShowRespPtr watchShowRespPtr;
	
	watchShowRqstPtr = WatchShowRqst::newInstance();
	watchShowRqstPtr->setRentedShowID(rentedShowID);

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		watchShowRespPtr = dataRequestorPtr->watchShowRequest(watchShowRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
			return watchShowRespPtr;

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::watchShow")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return WatchShowRespPtr();
}

/******************************************************************************/

StatusCode Session::releaseShow(const RentedShowID& rentedShowID)
{
	StatusCode statusCode = sc_GeneralError;
	CStrVar statusMessage;

	ReleaseShowRqstPtr releaseShowRqstPtr;
	ReleaseShowRespPtr releaseShowRespPtr;
	
	releaseShowRqstPtr = ReleaseShowRqst::newInstance();
	releaseShowRqstPtr->setRentedShowID(rentedShowID);

	ScreenPtr waitScreenPtr = WaitScreen::newInstance();
	try
	{
		MainApp::getThe()->processAvail();

		DataRequestorPtr dataRequestorPtr = DataRequestor::newInstance(fSessionData.c_str());
		releaseShowRespPtr = dataRequestorPtr->releaseShowRequest(releaseShowRqstPtr);
		statusCode = dataRequestorPtr->getStatusCode();

		waitScreenPtr->close();
		if(statusCode == sc_Success)
			return statusCode;

		statusMessage.copy(dataRequestorPtr->getStatusMessage());
	}
	CATCH_ERROR_NOACTION("Session::releaseShow")
	waitScreenPtr->close();

	showRequestError(statusMessage.c_str());

	return statusCode;
}

/******************************************************************************/

}; //namespace asi

/******************************************************************************/
/******************************************************************************/
