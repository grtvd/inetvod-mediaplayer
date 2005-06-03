/* INetVODPlayerRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "INetVODPlayerRqst.h"

namespace asi
{

/******************************************************************************/

void INetVODPlayerRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("INetVODPlayerRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void INetVODPlayerRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fVersion.c_str());
	filerPtr->writeString(fRequestID.c_str());
	filerPtr->writeString(fSessionData.c_str());
	filerPtr->writeObject(fRequestDataPtr);
}

/******************************************************************************/
/******************************************************************************/

void INetVODPlayerResp::readFromFiler(DataFilerPtr filerPtr)
{
	fRequestID.copy(filerPtr->readString().c_str());
	fStatusCode = (StatusCode)filerPtr->readLong();
	fStatusMessage = filerPtr->readString();
	fResponseDataPtr = filerPtr->readObject(ResponseDataConstructor());

	if(fResponseDataPtr.isNull() && (fStatusCode == sc_Success))
		throw ASIException("INetVODPlayerResp::readFromFiler", "fStatusCode == sc_Success, but no ResponseData");
}

/******************************************************************************/

void INetVODPlayerResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("INetVODPlayerResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
