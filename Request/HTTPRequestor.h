/* HTTPRequestor.h */

/******************************************************************************/
/******************************************************************************/
#ifndef HTTPRequestorH
#define HTTPRequestorH

#include "MemoryStream.h"

namespace asi
{

/******************************************************************************/

class HTTPRequestor;	//forward reference
typedef RefCountPtr<HTTPRequestor> HTTPRequestorPtr;

class HTTPRequestor : public RefCountObject
{
protected:
	HTTPRequestor() {}
	virtual ~HTTPRequestor() {}

private:
	HTTPRequestor(const HTTPRequestor&);						// don't allow copy constructor
	const HTTPRequestor& operator=(const HTTPRequestor&);		// or operator=

public:
	static HTTPRequestorPtr newInstance() { return HTTPRequestorPtr(new HTTPRequestor()); }

	MemoryStreamPtr sendRequest(MemoryStreamPtr rqstPtr);

private:
	MemoryStreamPtr connectAndSend(MemoryStreamPtr sendPtr);
	void sendBuffer(SOCKET sock, const byte* data, ulong dataLen);
	MemoryStreamPtr readResponse(SOCKET sock);
	CStrVar readNextLine(SOCKET sock);
	int readAllHeaders(SOCKET sock, ulong& contentLength, bool& chunked);
	void readNextHeader(SOCKET sock, CStr64& headerName, CStrVar& headerValue);
	ulong readChunkLength(SOCKET sock);
	void readBlankLength(SOCKET sock);
	void receiveBuffer(SOCKET sock, byte* data, ulong dataLen);

	friend class RefCountPtr<HTTPRequestor>;
};

/******************************************************************************/

}; //namespace asi

#endif	//HTTPRequestorH
/******************************************************************************/
/******************************************************************************/
