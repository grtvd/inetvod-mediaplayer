/* Stream.h */

/******************************************************************************/
/******************************************************************************/
#ifndef StreamH
#define StreamH

namespace asi
{

/******************************************************************************/

class Stream;	//forward reference
typedef RefCountPtr<Stream> StreamPtr;

class Stream : public RefCountObject
{
protected:

protected:
	Stream() {}
	virtual ~Stream() {}

private:
	Stream(const Stream&);						// don't allow copy constructor
	const Stream& operator=(const Stream&);		// or operator=

public:
	virtual void readBuffer(void* buffer, ulong bufferSize) = 0;
	virtual void writeBuffer(const void* buffer, ulong bufferSize) = 0;

	virtual void setSize(ulong newSize) = 0;
	virtual ulong getSize() const = 0;

	virtual void setPosition(ulong newPosition) = 0;
	virtual ulong getPosition() const = 0;

	friend class RefCountPtr<Stream>;
};


/******************************************************************************/

}; //namespace asi

#endif	//StreamH
/******************************************************************************/
/******************************************************************************/
