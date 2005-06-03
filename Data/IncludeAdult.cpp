/* IncludeAdult.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "IncludeAdult.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

CStr32 ConvertIncludeAdultToString(IncludeAdult ina)
{
	if(ina == ina_Never)
		return CStr32("Never");
	if(ina == ina_PromptPassword)
		return CStr32("PromptPassword");
	if(ina == ina_Always)
		return CStr32("Always");

	throw ASIException("ConvertIncludeAdultToString", "Unknown IncludeAdult(%d)", (int)ina);
}

/******************************************************************************/

IncludeAdult ConvertStringToIncludeAdult(const char* ina)
{
	CStr32 value(ina);
	value.toLower();

	if(value == "never")
		return ina_Never;
	if(value == "promptpassword")
		return ina_PromptPassword;
	if(value == "always")
		return ina_Always;

	throw ASIException("ConvertStringToIncludeAdult", "Unknown IncludeAdult(%s)", ina);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
