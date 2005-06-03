/* TStringVector.ccpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/

void CStr32Vector::readFromFiler(DataFilerPtr filerPtr)
{
	long numItems;

	clear();
	numItems = filerPtr->readLong();
	for(int i = 0; i < numItems; ++i)
		push_back(CStr32(filerPtr->readString().c_str()));
}

/******************************************************************************/

void CStr32Vector::writeToFiler(DataFilerPtr filerPtr) const
{
	CStr32Vector::const_iterator iter;

	filerPtr->writeLong(size());
	for(iter = begin(); iter != end(); ++iter)
		filerPtr->writeString((*iter).c_str());
}

/******************************************************************************/

void CStrVarVector::split(const char* data, const char* search)
{
	CStrVar item;
	const char* pos;
	const char* lastPos;
	int searchLen = STRLEN(search);

	clear();
	lastPos = data;
	while((pos = strstr(lastPos, search)) != NULL)
	{
		item.ncopy(lastPos, pos - lastPos);
		push_back(item);
		lastPos = pos + searchLen;
	}
	item.copy(lastPos);
	push_back(item);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
