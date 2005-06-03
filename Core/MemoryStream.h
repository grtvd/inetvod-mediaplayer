/* MemoryStream.h */

/******************************************************************************/
/******************************************************************************/
#ifndef MemoryStreamH
#define MemoryStreamH

#include "Stream.h"

namespace asi
{

/******************************************************************************/

class MemoryStream : public Stream
{
protected:
	static const ulong fGrowSize;

	auto_ptr<byte> fMemory;
	ulong fMemorySize;

	ulong fSize;
	ulong fPosition;

protected:
	MemoryStream() { fMemorySize = 0; fSize = 0; fPosition = 0; }
	virtual ~MemoryStream() {}

public:
	// Construction Methods
	static StreamPtr newInstance() { return StreamPtr(new MemoryStream()); }

	virtual void readBuffer(void* buffer, ulong bufferSize);
	virtual void writeBuffer(const void* buffer, ulong bufferSize);

	byte* getBuffer() { return fMemory.get(); }
	const byte* getBuffer() const { return fMemory.get(); }

	virtual void setSize(ulong newSize);
	virtual ulong getSize() const { return fSize; }

	void setCapacity(ulong capacity);
	ulong getCapacity() const { return fMemorySize; }

	virtual void setPosition(ulong newPosition);
	virtual ulong getPosition() const { return fPosition; }

	friend class RefCountPtr<MemoryStream>;
};

class MemoryStreamPtr : public RefCountPtr<MemoryStream>
{
public:
	MemoryStreamPtr(StreamPtr streamPtr = StreamPtr()) : 
		RefCountPtr<MemoryStream>(streamPtr.isNull() ? NULL :
		&dynamic_cast<MemoryStream&>(*streamPtr)) {}

	operator StreamPtr() { return(StreamPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//MemoryStreamH
/******************************************************************************/
/******************************************************************************/
