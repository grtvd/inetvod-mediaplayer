/* Currency.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "ShowCost.h"

namespace asi
{

/******************************************************************************/

void Money::readFromFiler(DataFilerPtr filerPtr)
{
	fCurrencyID.copy(filerPtr->readString().c_str());
	fAmount = filerPtr->readDouble();
}

/******************************************************************************/

void Money::writeToFiler(DataFilerPtr filerPtr) const
{
	filerPtr->writeString(fCurrencyID.c_str());
	filerPtr->writeDouble(fAmount);
}

/******************************************************************************/

}; //namespace asi

/******************************************************************************/
/******************************************************************************/
