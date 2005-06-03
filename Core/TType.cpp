/* TType.ccpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/
#if defined(ERRORDEBUGON)

char cast2char(int rhs)
{
	if(rhs > CHAR_MAX)
		throw ASIException("cast2char", "rhs > CHAR_MAX");

	return((char)rhs);
}

/******************************************************************************/

byte cast2byte(short rhs)
{
	if(rhs > UCHAR_MAX)
		throw ASIException("cast2byte", "rhs > UCHAR_MAX");

	return((byte)rhs);
}

/******************************************************************************/

byte cast2byte(int rhs)
{
	if(rhs > UCHAR_MAX)
		throw ASIException("cast2byte", "rhs > UCHAR_MAX");

	return((byte)rhs);
}

/******************************************************************************/

byte cast2byte(long rhs)
{
	if(rhs > UCHAR_MAX)
		throw ASIException("cast2byte", "rhs > UCHAR_MAX");

	return((byte)rhs);
}

/******************************************************************************/

short cast2short(int rhs)
{
	if(rhs > SHRT_MAX)
		throw ASIException("cast2short", "rhs > SHRT_MAX");

	return((short)rhs);
}

/******************************************************************************/

short cast2short(unsigned int rhs)
{
	if(rhs > SHRT_MAX)
		throw ASIException("cast2short", "rhs > SHRT_MAX");

	return((short)rhs);
}

/******************************************************************************/

short cast2short(long rhs)
{
	if(rhs > SHRT_MAX)
		throw ASIException("cast2short", "rhs > SHRT_MAX");

	return((short)rhs);
}

/******************************************************************************/

int cast2int(long rhs)
{
	if(rhs > INT_MAX)
		throw ASIException("cast2int", "rhs > INT_MAX");

	return((int)rhs);
}

/******************************************************************************/

int cast2int(unsigned long rhs)
{
	if(rhs > INT_MAX)
		throw ASIException("cast2int", "rhs > INT_MAX");

	return((int)rhs);
}

/******************************************************************************/

int cast2int(unsigned int rhs)
{
	if(rhs > INT_MAX)
		throw ASIException("cast2int", "rhs > INT_MAX");

	return((int)rhs);
}

/******************************************************************************/

long cast2long(unsigned long rhs)
{
	if(rhs > LONG_MAX)
		throw ASIException("cast2long", "rhs > LONG_MAX");

	return((long)rhs);
}

#endif //defined(ERRORDEBUGON)
/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
