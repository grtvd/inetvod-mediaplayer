/* BinaryFiler.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include <math.h>
#include "Core.h"

namespace asi
{

/******************************************************************************/

void BinaryFiler::byteFlip(void *buffer, long count)
{
	long i;
	char c;
	
	for (i = 0; i < (count + 1) / 2; i++)
	{
		c = ((char*)buffer)[i];
		((char*)buffer)[i] = ((char*)buffer)[count - i - 1];
		((char*)buffer)[count - i - 1] = c;
	}
}

/******************************************************************************/
/******************************************************************************/

byte BinaryFiler::readByte(short /* width */)
{
	byte data;

	fStreamPtr->readBuffer(&data, sizeof(data));
	return data;
}

/******************************************************************************/

short BinaryFiler::readShort(short /* width */)
{
	short data;

	fStreamPtr->readBuffer(&data, sizeof(data));
	if (fByteOrder == bo_BigEndian)
		byteFlip(&data, sizeof(data));
	return data;
}

/******************************************************************************/

long BinaryFiler::readLong(short /* width */)
{
	long data;

	fStreamPtr->readBuffer(&data, sizeof(data));
	if (fByteOrder == bo_BigEndian)
		byteFlip(&data, sizeof(data));
	return data;
}

/******************************************************************************/

float BinaryFiler::readFloat(short /* width */)
{
	float data;

	fStreamPtr->readBuffer(&data, sizeof(data));
	if (fByteOrder == bo_BigEndian)
		byteFlip(&data, sizeof(data));
	return data;
}

/******************************************************************************/

double BinaryFiler::readDouble(short /* width */)
{
	double data;

	fStreamPtr->readBuffer(&data, sizeof(data));
	if (fByteOrder == bo_BigEndian)
		byteFlip(&data, sizeof(data));
	return data;
}

/******************************************************************************/

CStrVar BinaryFiler::readString(short /* width */)
{
	short len = readShort();

	if(len < 0)		// invalid length
		throw ASIException("BinaryFiler::readString", "invalid length(%d)", (int)len);
	else if(len == 0)
		return CStrVar();

//	EnsureBuffer(len);

	auto_ptr<char> tempStr(new char[len + 1]);
	fStreamPtr->readBuffer(tempStr.get(), len);
	tempStr.get()[len] = '\0';

	return CStrVar(tempStr.get());
}

/******************************************************************************/

TDate BinaryFiler::readDate(short /* format */)
{
	int month, day, year;

	year = readShort();
	month = readByte();
	day = readByte();

	return TDate(month, day, year);
}

/******************************************************************************/

TDateTime BinaryFiler::readDateTime(short /* format */)
{
	int month, day, year, hour, minute, second;

	year = readShort();
	month = readByte();
	day = readByte();
	hour = readByte();
	minute = readByte();
	second = readByte();

	return TDateTime(month, day, year, hour, minute, second);
}

/******************************************************************************/

bool BinaryFiler::readBoolean()
{
	byte b;

	b = readByte();
	if (b == 1)
		return true;
	else
		return false;
}

/******************************************************************************/

StreamablePtr BinaryFiler::readObject(const StreamableConstructor& ctor)
{
	bool isNotNull = (readByte() != 0);
	if(!isNotNull)
		return StreamablePtr();

	return ctor.newInstance(DataFilerPtr(this));
}

/******************************************************************************/
/******************************************************************************/

void BinaryFiler::writeByte(byte data, short /* flag */, short /* width */)
{
	fStreamPtr->writeBuffer(&data, sizeof(data));
}

/******************************************************************************/

void BinaryFiler::writeShort(short data, short /* flag */, short /* width */)
{
	if (fByteOrder == bo_BigEndian)
		byteFlip(&data, sizeof(data));
	fStreamPtr->writeBuffer(&data, sizeof(data));
}

/******************************************************************************/

void BinaryFiler::writeLong(long data, short /* flag */, short /* width */)
{
	if (fByteOrder == bo_BigEndian)
		byteFlip(&data, sizeof(data));
	fStreamPtr->writeBuffer(&data, sizeof(data));
}

/******************************************************************************/

void BinaryFiler::writeFloat(float data, short /* format */, short /* decimals */,
	short /* flag */, short /* width */)
{
	if (fByteOrder == bo_BigEndian)
		byteFlip(&data, sizeof(data));
	fStreamPtr->writeBuffer(&data, sizeof(data));
}

/******************************************************************************/

void BinaryFiler::writeDouble(double data, short /* format */, short /* decimals */,
	short /* flag */, short /* width */)
{
	if (fByteOrder == bo_BigEndian)
		byteFlip(&data, sizeof(data));
	fStreamPtr->writeBuffer(&data, sizeof(data));
}

/******************************************************************************/

void BinaryFiler::writeString(const char* data, short /* width */)
{
	short	len;
	
	len = (short)STRLEN(data);
	writeShort(len);
	fStreamPtr->writeBuffer(data,  len);
}

/******************************************************************************/

void BinaryFiler::writeDate(TDate data, short /* format */, short /* flag */)
{
	int month, day, year;

	data.getMDY(month, day, year);

	writeShort(year);
	writeByte(month);
	writeByte(day);
}

/******************************************************************************/

void BinaryFiler::writeDateTime(TDateTime data, short /* format */, short /* flag */)
{
	int month, day, year, hour, minute, second;

	data.getMDY(month, day, year);
	data.getHMS(hour, minute, second);

	writeShort(year);
	writeByte(month);
	writeByte(day);
	writeByte(hour);
	writeByte(minute);
	writeByte(second);
}

/******************************************************************************/

void BinaryFiler::writeBoolean(bool data)
{
	byte b;

	b = 0;
	if (data)
		b = 1;
		
	writeByte(b);
}

/******************************************************************************/

void BinaryFiler::writeObject(const StreamablePtr streamablePtr)
{
	writeByte(!streamablePtr.isNull() ? (byte)1 : (byte)0);
	if(streamablePtr.isNull())
		return;

	streamablePtr->writeToFiler(DataFilerPtr(this));
}

/******************************************************************************/

}; //namespace asi

/******************************************************************************/
/******************************************************************************/
