/* DataRequestor.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "DataRequestor.h"
#include "TCPRequestor.h"
#include "HTTPRequestor.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

INetVODPlayerRqstPtr DataRequestor::createHeader(StreamablePtr payloadPtr)
{
	INetVODPlayerRqstPtr requestPtr;
	RequestDataPtr requestDataPtr;

	requestPtr = INetVODPlayerRqst::newInstance();
	requestPtr->setVersion("1.0.0");	//TODO:
	requestPtr->setRequestID("1");	//TODO:
	requestPtr->setSessionData(fSessionData.c_str());

	requestDataPtr = RequestData::newInstance();
	requestDataPtr->setRequest(payloadPtr);
	requestPtr->setRequestData(requestDataPtr);

	return requestPtr;
}

/******************************************************************************/

StreamablePtr DataRequestor::parseHeader(INetVODPlayerRespPtr responsePtr)
{
	fStatusCode = responsePtr->getStatusCode();
	fStatusMessage = responsePtr->getStatusMessage();

	if(fStatusCode == sc_InvalidSession)
		MainApp::getThe()->reset();

	if(responsePtr->getResponseDataPtr().isNull())
	{
		if(fStatusCode == sc_Success)
			fStatusCode = sc_GeneralError;
		return StreamablePtr();
	}

	return responsePtr->getResponseDataPtr()->getResponse();
}

/******************************************************************************/

StreamablePtr DataRequestor::sendRequest(StreamablePtr payloadPtr)
{
	INetVODPlayerRqstPtr requestPtr;
	INetVODPlayerRespPtr responsePtr;
	StreamablePtr payloadRespPtr;
	MemoryStreamPtr rqstStreamPtr;
	BinaryFilerPtr rqstFilerPtr;
	MemoryStreamPtr respStreamPtr;
	BinaryFilerPtr respFilerPtr;
//	TCPRequestorPtr tcpRequestorPtr;
	HTTPRequestorPtr httpRequestorPtr;

	// build the request header
	requestPtr = createHeader(payloadPtr);

	// build request data
	rqstStreamPtr = MemoryStream::newInstance();
	rqstFilerPtr = BinaryFiler::newInstance(rqstStreamPtr, bo_BigEndian);
	rqstFilerPtr->resetForWrite();
	rqstFilerPtr->writeObject(requestPtr);

	// send request
//	tcpRequestorPtr = TCPRequestor::newInstance();
//	respStreamPtr = tcpRequestorPtr->sendRequest(rqstStreamPtr);
	httpRequestorPtr = HTTPRequestor::newInstance();
	respStreamPtr = httpRequestorPtr->sendRequest(rqstStreamPtr);
	if(respStreamPtr.isNull())
		throw ASIException("DataRequestor::sendRequest", "respStreamPtr.isNull()"); 

	// parse response
	respFilerPtr = BinaryFiler::newInstance(respStreamPtr, bo_BigEndian);
	respFilerPtr->setupForRead();

	responsePtr = respFilerPtr->readObject(INetVODPlayerRespConstructor());

	// check RequestID
	if(strcmp(requestPtr->getRequestID(), responsePtr->getRequestID()) != 0)
		throw ASIException("DataRequestor::sendRequest", "RequestID mismatch");

	return parseHeader(responsePtr);
}

/******************************************************************************/

StatusCode DataRequestor::pingRequest()
{
	PingRespPtr pingRespPtr = sendRequest(PingRqst::newInstance());

	return fStatusCode;
}

/******************************************************************************/

EnrollRespPtr DataRequestor::enrollRequest(EnrollRqstPtr enrollRqstPtr)
{
//TODO: DO request here
	tPauseTenths(10);	// simulate request latency

	EnrollRespPtr enrollRespPtr = EnrollResp::newInstance();
	fStatusCode = sc_Success;
//TODO: DO request here

	return enrollRespPtr;
}

/******************************************************************************/

SignonRespPtr DataRequestor::signonRequest(SignonRqstPtr signonRqstPtr)
{
	return sendRequest(signonRqstPtr);
}

/******************************************************************************/

SystemDataRespPtr DataRequestor::systemDataRequest()
{
	return sendRequest(SystemDataRqst::newInstance());
}

/******************************************************************************/

StatusCode DataRequestor::enableAdultAccessRequest(
	EnableAdultAccessRqstPtr enableAdultAccessRqstPtr)
{
	EnableAdultAccessRespPtr enableAdultAccessRespPtr = sendRequest(enableAdultAccessRqstPtr);

	return fStatusCode;
}

/******************************************************************************/

ShowSearchRespPtr DataRequestor::showSearchRequest(ShowSearchRqstPtr showSearchRqstPtr)
{
	return sendRequest(showSearchRqstPtr);
}

/******************************************************************************/

ShowDetailRespPtr DataRequestor::showDetailRequest(ShowDetailRqstPtr showDetailRqstPtr)
{
	return sendRequest(showDetailRqstPtr);
}

/******************************************************************************/

StatusCode DataRequestor::providerEnrollRequest(ProviderEnrollRqstPtr providerEnrollRqstPtr)
{
	ProviderEnrollRespPtr providerEnrollRespPtr = sendRequest(providerEnrollRqstPtr);

	return fStatusCode;
}

/******************************************************************************/

StatusCode DataRequestor::setProviderRequest(SetProviderRqstPtr setProviderRqstPtr)
{
	SetProviderRespPtr setProviderRespPtr = sendRequest(setProviderRqstPtr);

	return fStatusCode;
}

/******************************************************************************/

CheckShowAvailRespPtr DataRequestor::checkShowAvailRequest(
	CheckShowAvailRqstPtr checkShowAvailRqstPtr)
{
	return sendRequest(checkShowAvailRqstPtr);
}

/******************************************************************************/

RentShowRespPtr DataRequestor::rentShowRequest(RentShowRqstPtr rentShowRqstPtr)
{
	return sendRequest(rentShowRqstPtr);
}

/******************************************************************************/

RentedShowListRespPtr DataRequestor::rentedShowListRequest(
	RentedShowListRqstPtr rentedShowListRqstPtr)
{
	return sendRequest(rentedShowListRqstPtr);
}

/******************************************************************************/

RentedShowRespPtr DataRequestor::rentedShowRequest(
	RentedShowRqstPtr rentedShowRqstPtr)
{
	return sendRequest(rentedShowRqstPtr);
}

/******************************************************************************/

WatchShowRespPtr DataRequestor::watchShowRequest(
	WatchShowRqstPtr watchShowRqstPtr)
{
	return sendRequest(watchShowRqstPtr);
}

/******************************************************************************/

ReleaseShowRespPtr DataRequestor::releaseShowRequest(
	ReleaseShowRqstPtr releaseShowRqstPtr)
{
	return sendRequest(releaseShowRqstPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
