/* MemberState.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "MemberState.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

void MemberState::readFromFiler(DataFilerPtr filerPtr)
{
	fMemberPrefsPtr = filerPtr->readObject(MemberPrefsConstructor());
	fMemberProviderVector.readFromFiler(filerPtr);
}

/******************************************************************************/

void MemberState::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeObject(fMemberPrefsPtr);
	fMemberProviderVector.writeToFiler(filerPtr);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
