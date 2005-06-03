/* TCPRequestor.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TCPRequestorH
#define TCPRequestorH

#include "MemoryStream.h"

namespace asi
{

/******************************************************************************/

class TCPRequestor;	//forward reference
typedef RefCountPtr<TCPRequestor> TCPRequestorPtr;

class TCPRequestor : public RefCountObject
{
protected:
	TCPRequestor() { /*fResponseDataLen = 0;*/ }
	virtual ~TCPRequestor() {}

private:
	TCPRequestor(const TCPRequestor&);						// don't allow copy constructor
	const TCPRequestor& operator=(const TCPRequestor&);		// or operator=

public:
	static TCPRequestorPtr newInstance() { return TCPRequestorPtr(new TCPRequestor()); }

	MemoryStreamPtr sendRequest(MemoryStreamPtr rqstPtr);

private:
	MemoryStreamPtr connectAndSend(MemoryStreamPtr sendPtr);
	void sendBuffer(SOCKET sock, const byte* data, ulong dataLen);
	void receiveBuffer(SOCKET sock, byte* data, ulong dataLen);

	friend class RefCountPtr<TCPRequestor>;
};

/******************************************************************************/

}; //namespace asi

#endif	//TCPRequestorH
/******************************************************************************/
/******************************************************************************/
