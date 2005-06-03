/* MemoryStream.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

/******************************************************************************/

const ulong MemoryStream::fGrowSize = 1024;

/******************************************************************************/

void MemoryStream::readBuffer(void* buffer, ulong bufferSize)
{
	if(fPosition + bufferSize > fSize)
		throw ASIException("MemoryStream::readBuffer", "read past end of buffer");
	memcpy(buffer, fMemory.get() + fPosition, bufferSize);
	fPosition += bufferSize;
}

/******************************************************************************/

void MemoryStream::writeBuffer(const void* buffer, ulong bufferSize)
{
	if(fPosition + bufferSize > fMemorySize)
		setCapacity(fPosition + bufferSize);
	memcpy(fMemory.get() + fPosition, buffer, bufferSize);
	fPosition += bufferSize;
	fSize = fPosition;
}

/******************************************************************************/

void MemoryStream::setSize(ulong newSize)
{
	if(newSize > fMemorySize)
		setCapacity(newSize);
	fSize = newSize;
}

/******************************************************************************/

void MemoryStream::setCapacity(ulong capacity)
{
	ulong newMemorySize;

	if(capacity < fGrowSize)
		capacity = fGrowSize;

	newMemorySize = (((capacity - 1) / fGrowSize) + 1 ) * fGrowSize;
	if(newMemorySize < fMemorySize)
		fMemorySize = newMemorySize;
	else if (newMemorySize > fMemorySize)
	{
		auto_ptr<byte> tempMemory(new byte[newMemorySize]);
		memcpy(tempMemory.get(), fMemory.get(), fMemorySize);
		#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
		fMemory.reset(tempMemory.release());
		#else
		fMemory = auto_ptr<byte>(tempMemory.release());
		#endif
		fMemorySize = newMemorySize;
	}
}

/******************************************************************************/

void MemoryStream::setPosition(ulong newPosition)
{
	if(newPosition > fSize)
		setSize(newPosition);
	fPosition = newPosition;
}

/******************************************************************************/

}; //namespace asi

/******************************************************************************/
/******************************************************************************/
