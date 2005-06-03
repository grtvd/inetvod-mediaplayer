/* DataRequestor.h */

/******************************************************************************/
/******************************************************************************/
#ifndef DataRequestorH
#define DataRequestorH

#include "INetVODPlayerRqst.h"
#include "PingRqst.h"
#include "SignonRqst.h"
#include "EnrollRqst.h"
#include "ShowSearchRqst.h"
#include "SystemDataRqst.h"
#include "ShowDetailRqst.h"
#include "EnableAdultAccessRqst.h"
#include "ProviderEnrollRqst.h"
#include "SetProviderRqst.h"
#include "CheckShowAvailRqst.h"
#include "RentShowRqst.h"
#include "RentedShowListRqst.h"
#include "RentedShowRqst.h"
#include "WatchShowRqst.h"
#include "ReleaseShowRqst.h"

namespace asi
{

/******************************************************************************/

class DataRequestor;	//forward reference
typedef RefCountPtr<DataRequestor> DataRequestorPtr;

class DataRequestor : public RefCountObject
{
protected:
	CStrVar fSessionData;
	StatusCode fStatusCode;
	CStrVar fStatusMessage;

protected:
	DataRequestor(const char* sessionData) { fSessionData.copy(sessionData); fStatusCode = sc_Success; }
	virtual ~DataRequestor() {}

private:
	DataRequestor(const DataRequestor&);						// don't allow copy constructor
	const DataRequestor& operator=(const DataRequestor&);		// or operator=

public:
	static DataRequestorPtr newInstance(const char* sessionData = NULL)
		{ return DataRequestorPtr(new DataRequestor(sessionData)); }

protected:
	INetVODPlayerRqstPtr createHeader(StreamablePtr payloadPtr);
	StreamablePtr parseHeader(INetVODPlayerRespPtr responsePtr);
	StreamablePtr sendRequest(StreamablePtr payloadPtr);

public:
	StatusCode getStatusCode() const { return fStatusCode; }
	const char* getStatusMessage() const { return fStatusMessage.c_str(); }

	StatusCode pingRequest();
	EnrollRespPtr enrollRequest(EnrollRqstPtr enrollRqstPtr);
	SignonRespPtr signonRequest(SignonRqstPtr signonRqstPtr);

	SystemDataRespPtr systemDataRequest();
	EnableAdultAccessRespPtr enableAdultAccessRequest(EnableAdultAccessRqstPtr enableAdultAccessRqstPtr);

	ShowSearchRespPtr showSearchRequest(ShowSearchRqstPtr showSearchRqstPtr);
	ShowDetailRespPtr showDetailRequest(ShowDetailRqstPtr showDetailRqstPtr);

	StatusCode providerEnrollRequest(ProviderEnrollRqstPtr providerEnrollRqstPtr);
	StatusCode setProviderRequest(SetProviderRqstPtr setProviderRqstPtr);
	CheckShowAvailRespPtr checkShowAvailRequest(CheckShowAvailRqstPtr checkShowAvailRqstPtr);
	RentShowRespPtr rentShowRequest(RentShowRqstPtr rentShowRqstPtr);

	RentedShowListRespPtr rentedShowListRequest(RentedShowListRqstPtr rentedShowListRqstPtr);
	RentedShowRespPtr rentedShowRequest(RentedShowRqstPtr rentedShowRqstPtr);

	WatchShowRespPtr watchShowRequest(WatchShowRqstPtr watchShowRqstPtr);
	ReleaseShowRespPtr releaseShowRequest(ReleaseShowRqstPtr releaseShowRqstPtr);

	friend class RefCountPtr<DataRequestor>;
};

/******************************************************************************/

}; //namespace asi

#endif	//DataRequestorH
/******************************************************************************/
/******************************************************************************/
