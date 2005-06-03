/* RequestData.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "RequestData.h"

namespace asi
{

/******************************************************************************/

void RequestData::setRequest(StreamablePtr requestPtr)
{
	fRequestPtr = requestPtr;
	fRequestType.copy(fRequestPtr->className());
}

/******************************************************************************/

void RequestData::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("RequestData::readFromFiler", "not implemented");
}

/******************************************************************************/

void RequestData::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fRequestType.c_str());
	filerPtr->writeObject(fRequestPtr);
}

/******************************************************************************/
/******************************************************************************/

void ResponseData::readFromFiler(DataFilerPtr filerPtr)
{
	auto_ptr<StreamableConstructor> ctor;

	fResponseType.copy(filerPtr->readString().c_str());

	#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
	if(fResponseType == "PingResp")
		ctor.reset(new PingRespConstructor());
	else if(fResponseType == "SignonResp")
		ctor.reset(new SignonRespConstructor());
	else if(fResponseType == "SystemDataResp")
		ctor.reset(new SystemDataRespConstructor());
	else if(fResponseType == "EnableAdultAccessResp")
		ctor.reset(new EnableAdultAccessRespConstructor());
	else if(fResponseType == "ShowSearchResp")
		ctor.reset(new ShowSearchRespConstructor());
	else if(fResponseType == "ShowDetailResp")
		ctor.reset(new ShowDetailRespConstructor());
	else if(fResponseType == "ProviderEnrollResp")
		ctor.reset(new ProviderEnrollRespConstructor());
	else if(fResponseType == "SetProviderResp")
		ctor.reset(new SetProviderRespConstructor());
	else if(fResponseType == "CheckShowAvailResp")
		ctor.reset(new CheckShowAvailRespConstructor());
	else if(fResponseType == "RentShowResp")
		ctor.reset(new RentShowRespConstructor());
	else if(fResponseType == "RentedShowListResp")
		ctor.reset(new RentedShowListRespConstructor());
	else if(fResponseType == "RentedShowResp")
		ctor.reset(new RentedShowRespConstructor());
	else if(fResponseType == "WatchShowResp")
		ctor.reset(new WatchShowRespConstructor());
	else if(fResponseType == "ReleaseShowResp")
		ctor.reset(new ReleaseShowRespConstructor());
	else
		throw ASIException("ResponseData::readFromFiler", "Unknown ResponseType(%s)", fResponseType.c_str());
	#else
	if(fResponseType == "PingResp")
		ctor = auto_ptr<StreamableConstructor>(new PingRespConstructor());
	else if(fResponseType == "SignonResp")
		ctor = auto_ptr<StreamableConstructor>(new SignonRespConstructor());
	else if(fResponseType == "SystemDataResp")
		ctor = auto_ptr<StreamableConstructor>(new SystemDataRespConstructor());
	else if(fResponseType == "EnableAdultAccessResp")
		ctor = auto_ptr<StreamableConstructor>(new EnableAdultAccessRespConstructor());
	else if(fResponseType == "ShowSearchResp")
		ctor = auto_ptr<StreamableConstructor>(new ShowSearchRespConstructor());
	else if(fResponseType == "ShowDetailResp")
		ctor = auto_ptr<StreamableConstructor>(new ShowDetailRespConstructor());
	else if(fResponseType == "ProviderEnrollResp")
		ctor = auto_ptr<StreamableConstructor>(new ProviderEnrollRespConstructor());
	else if(fResponseType == "SetProviderResp")
		ctor = auto_ptr<StreamableConstructor>(new SetProviderRespConstructor());
	else if(fResponseType == "CheckShowAvailResp")
		ctor = auto_ptr<StreamableConstructor>(new CheckShowAvailRespConstructor());
	else if(fResponseType == "RentShowResp")
		ctor = auto_ptr<StreamableConstructor>(new RentShowRespConstructor());
	else if(fResponseType == "RentedShowListResp")
		ctor = auto_ptr<StreamableConstructor>(new RentedShowListRespConstructor());
	else if(fResponseType == "RentedShowResp")
		ctor = auto_ptr<StreamableConstructor>(new RentedShowRespConstructor());
	else if(fResponseType == "WatchShowResp")
		ctor = auto_ptr<StreamableConstructor>(new WatchShowRespConstructor());
	else if(fResponseType == "ReleaseShowResp")
		ctor = auto_ptr<StreamableConstructor>(new ReleaseShowRespConstructor());
	else
		throw ASIException("ResponseData::readFromFiler", "Unknown ResponseType(%s)", fResponseType.c_str());
	#endif

	fResponsePtr = filerPtr->readObject(*ctor.get());
}

/******************************************************************************/

void ResponseData::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("ResponseData::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
