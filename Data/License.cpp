/* License.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "License.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

CStr32 ConvertLicenseMethodToString(LicenseMethod lm)
{
	if(lm == lm_URLOnly)
		return CStr32("URLOnly");
	if(lm == lm_LicenseServer)
		return CStr32("LicenseServer");

	throw ASIException("ConvertLicenseMethodToString", "Unknown LicenseMethod(%d)", (int)lm);
}

/******************************************************************************/

LicenseMethod ConvertStringToLicenseMethod(const char* lm)
{
	CStr32 value(lm);
	value.toLower();

	if(value == "urlonly")
		return lm_URLOnly;
	if(value == "licenseserver")
		return lm_LicenseServer;

	throw ASIException("ConvertStringToLicenseMethod", "Unknown LicenseMethod(%s)", lm);
}

/******************************************************************************/
/******************************************************************************/

void License::readFromFiler(DataFilerPtr filerPtr)
{
	fLicenseMethod = ConvertStringToLicenseMethod(filerPtr->readString().c_str());
	fShowURL = filerPtr->readString();
	fLicenseURL = filerPtr->readString();
	fContentID.copy(filerPtr->readString().c_str());
	fUserID.copy(filerPtr->readString().c_str());
	fPassword.copy(filerPtr->readString().c_str());
}

/******************************************************************************/

void License::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(ConvertLicenseMethodToString(fLicenseMethod).c_str());
	filerPtr->writeString(fShowURL.c_str());
	filerPtr->writeString(fLicenseURL.c_str());
	filerPtr->writeString(fContentID.c_str());
	filerPtr->writeString(fUserID.c_str());
	filerPtr->writeString(fPassword.c_str());
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
