/* DataFiler.h */

/******************************************************************************/
/******************************************************************************/
#ifndef DataFilerH
#define DataFilerH

#include "Stream.h"
#include "Streamable.h"
#include "StreamableConstructor.h"

namespace asi
{

/******************************************************************************/

class DataFiler;	//forward reference
typedef RefCountPtr<DataFiler> DataFilerPtr;

class DataFiler : public RefCountObject
{
protected:
	StreamPtr fStreamPtr;

protected:
	DataFiler();
	DataFiler(StreamPtr& streamPtr);
	virtual ~DataFiler() {}

private:
	DataFiler(const DataFiler&);						// don't allow copy constructor
	const DataFiler& operator=(const DataFiler&);		// or operator=

public:
	StreamPtr getStream() const { return fStreamPtr; }
	void setupForRead() { fStreamPtr->setPosition(0); }
	void resetForWrite();
	long size() const { return (fStreamPtr->getSize()); }

	virtual byte readByte(short width = 0) = 0;
	virtual short readShort(short width = 0) = 0;
	virtual long readLong(short width = 0) = 0;
	virtual float readFloat(short width = 0) = 0;
	virtual double readDouble(short width = 0) = 0;
	virtual CStrVar readString(short width = 0) = 0;
	virtual TDate readDate(short format = 0) = 0;
	virtual TDateTime readDateTime(short format = 0) = 0;
	virtual bool readBoolean() = 0;
	virtual StreamablePtr readObject(const StreamableConstructor& ctor) = 0;

	virtual void writeByte(byte data, short flag = 0, short width = 0) = 0;
	virtual	void writeShort(short data, short flag = 0, short width = 0) = 0;
	virtual void writeLong(long data, short flag = 0, short width = 0) = 0;
	virtual void writeFloat(float data, short format = 0, short decimals = 0,
		short flag = 0, short width = 0) = 0;
	virtual void writeDouble(double data, short format = 0, short decimals = 0,
		short flag = 0, short width = 0) = 0;
	virtual void writeString(const char* data, short width = 0) = 0;
	virtual void writeDate(TDate data, short format = 0, short flag = 0) = 0;
	virtual void writeDateTime(TDateTime data, short format = 0, short flag = 0) = 0;
	virtual void writeBoolean(bool data) = 0;
	virtual void writeObject(const StreamablePtr streamablePtr) = 0;

	virtual bool isMoreDataAvailable();

	friend class RefCountPtr<DataFiler>;
};

/******************************************************************************/

}; //namespace asi

#endif	//DataFilerH
/******************************************************************************/
/******************************************************************************/
