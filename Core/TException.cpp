/* TException.ccpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

ASIException::ASIException(const char* method, const char* msg, ...)
{
	va_list argList;

	fMethod.copy(method);
	va_start(argList, msg);
	fMsg.copyVargList(msg, argList, true);
}

/******************************************************************************/

ASIException::ASIException(const char* file, const int line, const char* msg, ...)
{
	va_list argList;

	fMsg.copyVarg("[%s: %d] ", file, line);
	va_start(argList, msg);
	fMsg.copyVargList(msg, argList, true);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
