/* TNumeric.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

const short TNumeric<short>::UNDEFINED_VALUE = SHRT_MIN;
const short TNumeric<short>::DEFAULT_VALUE = 0;

const long TNumeric<long>::UNDEFINED_VALUE = LONG_MIN;
const long TNumeric<long>::DEFAULT_VALUE = 0L;

/******************************************************************************/

bool TNumericUtil::isNumericChar(char ch)
{
	if(!isdigit(ch) && (ch != '-'))
		return FALSE;
	return TRUE;
}

/******************************************************************************/

bool TNumericUtil::allNumericString(const char* str)
{
	int len = STRLEN(str);

	for(int i = 0; i < len; i++)
		if(!isNumericChar(str[i]))
			return FALSE;

	return TRUE;
}

/******************************************************************************/

bool TNumericUtil::stringToNumeric(const char* str, long& value)
{
	if(!allNumericString(str))
	{
		value = 0;
		return FALSE;
	}

	value = atol(str);
	return TRUE;
}

/******************************************************************************/

CStr32 TNumericUtil::numericToString(long value)
{
	CStr32 str;
	str.copyVarg("%ld", value);
	return str;
}

/******************************************************************************/
/******************************************************************************/
//
//TNumeric<short>::TNumeric<short>(const char* str)
//{
//	fValue = UNDEFINED_VALUE;
//	if(!tStrHasLen(str))
//		return;
//
//	long value;
//	if(!TNumericUtil::stringToNumeric(str, value))
//		return;
//
//	fValue = value;
//}
//
/******************************************************************************/
//
//const char* TNumeric<short>::c_str() const
//{
//	CStr32 str = TNumericUtil::numericToString(fValue);
//
//	int size = str.len() + 1;
//	(const_cast<TNumeric*>(this))->fFormatted.reset(new char[size]);
//	tStrCpy(fFormatted.get(), size, str.c_str());
//
//	return fFormatted.get();
//}
//
/******************************************************************************/

void TNumeric<short>::readFromFiler(DataFilerPtr filerPtr)
{
	fValue = filerPtr->readShort();
}

/******************************************************************************/

void TNumeric<short>::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeShort(fValue);
}

/******************************************************************************/
/******************************************************************************/

void TNumeric<long>::readFromFiler(DataFilerPtr filerPtr)
{
	fValue = filerPtr->readLong();
}

/******************************************************************************/

void TNumeric<long>::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeLong(fValue);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
