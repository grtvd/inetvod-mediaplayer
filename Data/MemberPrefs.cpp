/* MemberPrefs.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "MemberPrefs.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

void MemberPrefs::readFromFiler(DataFilerPtr filerPtr)
{
	fIncludeAdult = ConvertStringToIncludeAdult(filerPtr->readString().c_str());
}

/******************************************************************************/

void MemberPrefs::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(ConvertIncludeAdultToString(fIncludeAdult).c_str());
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
