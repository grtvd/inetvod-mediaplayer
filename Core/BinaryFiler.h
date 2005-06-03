/* BinaryFiler.h */

/******************************************************************************/
/******************************************************************************/
#ifndef BinaryFilerH
#define BinaryFilerH

#include "DataFiler.h"

namespace asi
{

/******************************************************************************/

enum ByteOrder
{
	bo_BigEndian,
	bo_LittleEndian
};

/******************************************************************************/

class BinaryFiler : public DataFiler
{
protected:
	ByteOrder fByteOrder;

protected:
	BinaryFiler(StreamPtr streamPtr, ByteOrder byteOrder) : DataFiler(streamPtr) { fByteOrder = byteOrder; }
	virtual ~BinaryFiler() {}

public:
	static void byteFlip(void *buffer, long count);

	static DataFilerPtr newInstance(StreamPtr streamPtr, ByteOrder byteOrder)
		{ return DataFilerPtr(new BinaryFiler(streamPtr, byteOrder)); }

	virtual byte readByte(short width = 0);
	virtual short readShort(short width = 0);
	virtual long readLong(short width = 0);
	virtual float readFloat(short width = 0);
	virtual double readDouble(short width = 0);
	virtual CStrVar readString(short width = 0);
	virtual TDate readDate(short format = 0);	//TODO: should this be here?
	virtual TDateTime readDateTime(short format = 0);	//TODO: should this be here?
	virtual bool readBoolean();
	virtual StreamablePtr readObject(const StreamableConstructor& ctor);

	virtual void writeByte(byte data, short flag = 0, short width = 0);
	virtual	void writeShort(short data, short flag = 0, short width = 0);
	virtual void writeLong(long data, short flag = 0, short width = 0);
	virtual void writeFloat(float data, short format = 0, short decimals = 0,
		short flag = 0, short width = 0);
	virtual void writeDouble(double data, short format = 0, short decimals = 0,
		short flag = 0, short width = 0);
	virtual void writeString(const char* data, short width = 0);
	virtual void writeDate(TDate data, short format = 0, short flag = 0);	//TODO: should this be here?
	virtual void writeDateTime(TDateTime data, short format = 0, short flag = 0);	//TODO: should this be here?
	virtual void writeBoolean(bool data);
	virtual void writeObject(const StreamablePtr streamablePtr);

	friend class RefCountPtr<BinaryFiler>;
};

class BinaryFilerPtr : public RefCountPtr<BinaryFiler>
{
public:
	BinaryFilerPtr(DataFilerPtr dataFilerPtr = DataFilerPtr()) : 
		RefCountPtr<BinaryFiler>(dataFilerPtr.isNull() ? NULL :
		&dynamic_cast<BinaryFiler&>(*dataFilerPtr)) {}

	operator DataFilerPtr() { return(DataFilerPtr(fT)); }
};


/******************************************************************************/

}; //namespace asi

#endif	//BinaryFilerH
/******************************************************************************/
/******************************************************************************/

