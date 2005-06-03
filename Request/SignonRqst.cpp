/* SignonRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "SignonRqst.h"

namespace asi
{

/******************************************************************************/

void SignonRqst::readFromFiler(DataFilerPtr filerPtr)
{
	throw ASIException("SignonRqst::readFromFiler", "not implemented");
}

/******************************************************************************/

void SignonRqst::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fUserID.c_str());
	filerPtr->writeString(fPassword.c_str());
	filerPtr->writeObject(fPlayerPtr);
}

/******************************************************************************/
/******************************************************************************/

void SignonResp::readFromFiler(DataFilerPtr filerPtr)
{
	fSessionData = filerPtr->readString();
	fSessionExpires = filerPtr->readDateTime();
	fMemberStatePtr = filerPtr->readObject(MemberStateConstructor());
}

/******************************************************************************/

void SignonResp::writeToFiler(DataFilerPtr filerPtr) const
{
	throw ASIException("SignonResp::writeToFiler", "not implemented");
}


/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
