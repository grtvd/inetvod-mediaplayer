/* Session.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SessionH
#define SessionH

#include "DataID.h"
#include "SetupData.h"
#include "Provider.h"
#include "Category.h"
#include "Rating.h"
#include "StatusCode.h"
#include "DataRequestor.h"
#include "SearchData.h"

namespace asi
{

/******************************************************************************/

enum MemoryCardSlot
{
	mc_Undefined = 0,
	mc_Slot1 = 1,
	mc_Slot2 = 2
};

/******************************************************************************/

class Session;	//forward reference
typedef RefCountPtr<Session> SessionPtr;

class Session : public RefCountObject
{
protected:
	MemoryCardSlot fMemoryCardSlot;
	bool fNetworkInit;
	CStr64 fNetworkHostName;
	ushort fNetworkHostPort;
	CStrVar fNetworkHostPath;
	struct hostent fNetworkHost;
	bool fHaveNetworkHost;
	bool fCanPingServer;

	PlayerPtr fPlayerPtr;

	bool fIsUserLoggedOn;
	CStr64 fUserID;
	CStr32 fUserPassword;
	bool fRememberPassword;
	CStrVar fSessionData;
	TDateTime fSessionExpires;
	MemberPrefsPtr fMemberPrefsPtr;
	MemberProviderVector fMemberProviderVector;

	IncludeAdult fIncludeAdult;
	bool fCanAccessAdult;

	bool fIsSystemDataLoaded;
	ProviderVector fProviderVector;
	CategoryVector fCategoryVector;
	RatingVector fRatingVector;

protected:
	Session();
	virtual ~Session();

private:
	Session(const Session&);						// don't allow copy constructor
	const Session& operator=(const Session&);		// or operator=

public:
	// Construction Methods
	static SessionPtr newInstance();
	bool loadAppSettings();

	// Data Get/Set Methods
	const char* getNetworkHostName() const { return fNetworkHostName.c_str(); }
	ushort getNetworkHostPort() const { return fNetworkHostPort; }
	const char* getNetworkHostPath() const { return fNetworkHostPath.c_str(); }
	void setNetworkHost(struct hostent* he) { memcpy(&fNetworkHost, he, sizeof(fNetworkHost)); fHaveNetworkHost = true; }
	const struct hostent* getNetworkHost() const { return fHaveNetworkHost ? &fNetworkHost : NULL; }
	bool canPingServer() { return fCanPingServer; }
	const char* getVersion() { return fPlayerPtr->getVersion(); }

	bool isUserLoggedOn() { return fIsUserLoggedOn; }
	bool haveUserID() { return fUserID.len() > 0; }
	bool haveUserPassword() { return fUserPassword.len() > 0; }
	void clearLogonInfo() { fIsUserLoggedOn = false; fUserID.clear(); fUserPassword.clear(); }

	IncludeAdult getIncludeAdult() const { return fIncludeAdult; }
	bool canAccessAdult() const { return fCanAccessAdult; }

	// System Data Routines
	bool isSystemDataLoaded() { return fIsSystemDataLoaded; }

	void getProviderVector(ProviderVector& providerVector) const
		{ providerVector.copy(fProviderVector); }
	ProviderPtr getProvider(const ProviderID& providerID) const
		{ return fProviderVector.getByID(providerID); }
	const char* getProviderName(const ProviderID& providerID) const;

	void getCategoryVector(CategoryVector& categoryVector) const
		{ categoryVector.copy(fCategoryVector); }
	const char* getCategoryName(const CategoryID& categoryID);
	CStrVar getCategoryNames(const CategoryIDVector& categoryIDVector);

	void getRatingVector(RatingVector& ratingVector) const
		{ ratingVector.copy(fRatingVector); }
	const char* getRatingName(const RatingID& ratingID);

	// Memory Card Routines
protected:
	bool loadMemCardSettings();
public:
	bool loadMemCardSettings(MemoryCardSlot memoryCardSlot);
	bool findLoadMemCardSettings();
	bool saveMemCardSettings();
	bool saveMemCardSettings(MemoryCardSlot memoryCardSlot);

	void showRequestError(const char* message);

	// Server Requests
	bool pingServer();
	StatusCode enroll(SetupDataPtr setupDataPtr);
	StatusCode signon();
	StatusCode signon(const char* password);
	StatusCode signon(const char* password, bool rememberPassword);
	StatusCode signon(const char* userID, const char* password, bool rememberPassword);

	bool isMemberOfProvider(const ProviderID& providerID);

	bool loadSystemData();
	StatusCode enableAdultAccess(const char* password);

	bool showSearch(const SearchDataPtr& searchDataPtr, ShowSearchVector& showSearchVector);
	ShowDetailPtr showDetail(const ShowID& showID, const ProviderID& providerID);

	StatusCode providerEnroll(const ProviderID& providerID);
	StatusCode setProvider(const ProviderID& providerID, const char* userID, const char* password);

	CheckShowAvailRespPtr checkShowAvail(const ShowID& showID, const ProviderID& providerID,
		StatusCode& statusCode);
	RentShowRespPtr rentShow(const ShowID& showID, const ProviderID& providerID, const ShowCostPtr& approvedCostPtr);

	StatusCode rentedShowList(RentedShowSearchVector& rentedShowSearchVector);
	RentedShowPtr rentedShow(const RentedShowID& rentedShowID);

	WatchShowRespPtr watchShow(const RentedShowID& rentedShowID);
	StatusCode releaseShow(const RentedShowID& rentedShowID);

	friend class RefCountPtr<Session>;
};

/******************************************************************************/

}; //namespace asi

#endif	//SessionH
/******************************************************************************/
/******************************************************************************/
