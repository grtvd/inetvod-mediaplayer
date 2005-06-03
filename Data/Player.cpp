/* Player.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "Player.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

void Player::readFromFiler(DataFilerPtr filerPtr)
{
	fManufacturerID = ManufacturerID(filerPtr->readString().c_str());
	fModelNo.copy(filerPtr->readString().c_str());
	fSerialNo.copy(filerPtr->readString().c_str());
	fVersion.copy(filerPtr->readString().c_str());
}

/******************************************************************************/

void Player::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fManufacturerID.c_str());
	filerPtr->writeString(fModelNo.c_str());
	filerPtr->writeString(fSerialNo.c_str());
	filerPtr->writeString(fVersion.c_str());
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
