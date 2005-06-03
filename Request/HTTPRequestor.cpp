/* HTTPRequestor.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "MemoryStream.h"
#include "BinaryFiler.h"
#include "HTTPRequestor.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

MemoryStreamPtr HTTPRequestor::sendRequest(MemoryStreamPtr rqstPtr)
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	MemoryStreamPtr sendPtr = MemoryStream::newInstance();
	MemoryStreamPtr recvPtr;
	TextWriterPtr sendWriterPtr = TextWriter::newInstance(sendPtr);
	CStrVar tempStr;
	int tryCount = 1;

	// get IP host
	if(sessionPtr->getNetworkHost() == NULL)
	{
		struct hostent *he = gethostbyname(sessionPtr->getNetworkHostName());
		if(he == NULL)
			return recvPtr;

		sessionPtr->setNetworkHost(he);
	}

	// add HTTP headers
	//sendWriterPtr->writeLine("POST /inetvod/playerapi/xml HTTP/1.1");
	tempStr.copyVarg("POST %s HTTP/1.1", sessionPtr->getNetworkHostPath());
	sendWriterPtr->writeLine(tempStr.c_str());
	tempStr.copyVarg("Host: %s", sessionPtr->getNetworkHostName());
	//sendWriterPtr->writeLine("Host: localhost");
	sendWriterPtr->writeLine(tempStr.c_str());
	sendWriterPtr->writeLine("Content-Type: application/octet-stream");
	tempStr.copyVarg("Content-Length: %ld", rqstPtr->getSize());
	sendWriterPtr->writeLine(tempStr.c_str());
	sendWriterPtr->writeLine("");
	sendPtr->writeBuffer(rqstPtr->getBuffer(), rqstPtr->getSize());

	while(tryCount <= 2)
	{
		try
		{
			recvPtr = connectAndSend(sendPtr);
			if(!recvPtr.isNull())
				break;
		}
		CATCH_ERROR_NOACTION("HTTPRequestor::sendRequest");

		++tryCount;
	}

	return recvPtr;
}

/******************************************************************************/

MemoryStreamPtr HTTPRequestor::connectAndSend(MemoryStreamPtr sendPtr)
{
	SessionPtr sessionPtr = MainApp::getThe()->getSession();
	SOCKET sock = INVALID_SOCKET;
	struct sockaddr_in sockaddr;
	//ulong recvDataLen;
	MemoryStreamPtr recvDataPtr;
	int rc;

	// initialize address
#if TRUE
	const struct hostent *he = sessionPtr->getNetworkHost();
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_family = he->h_addrtype;
	memcpy(&sockaddr.sin_addr, he->h_addr, he->h_length);
	sockaddr.sin_port = htons(sessionPtr->getNetworkHostPort());
#else
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.S_un.S_un_b.s_b1 = 192;
	sockaddr.sin_addr.S_un.S_un_b.s_b2 = 168;
	sockaddr.sin_addr.S_un.S_un_b.s_b3 = 11;
	sockaddr.sin_addr.S_un.S_un_b.s_b4 = 42;
	sockaddr.sin_port = htons(80);
#endif

	// create the socket
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		throw ASIException("HTTPRequestor::connectAndSend", "socket() failed, error:%d", WSAGetLastError());

	try
	{
		// open a connection on the socket
		rc = connect(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
		if(!rc)
		{
			// send the data
			sendBuffer(sock, sendPtr->getBuffer(), sendPtr->getSize());

			// get the response data
			recvDataPtr = readResponse(sock);
		}
		else
			throw ASIException("HTTPRequestor::connectAndSend", "connect() failed, error:%d", WSAGetLastError());
	}
	catch(exception e)
	{
		if (sock != INVALID_SOCKET)
			closesocket(sock);
		throw e;
	}

	if (sock != INVALID_SOCKET)
		closesocket(sock);

	return recvDataPtr;
}

/******************************************************************************/

void HTTPRequestor::sendBuffer(SOCKET sock, const byte* data, ulong dataLen)
{
	const byte* bytesToSend;
	int numBytesToSend;
	int numBytesSent;
	TTick startTick = tGetTickCount();

	// send the data
	bytesToSend = data;
	numBytesToSend = dataLen;
	while(numBytesToSend > 0)
	{
		// check for timeout
		if(tHaveSecsPast(startTick, 30))
			throw ASIException("HTTPRequestor::sendBuffer", "Timeout has expired");

		numBytesSent = send(sock, (const char*)bytesToSend, numBytesToSend, 0);
		if(numBytesSent == SOCKET_ERROR)
			throw ASIException("HTTPRequestor::sendBuffer", "send failed, error:%d", WSAGetLastError());

		bytesToSend += numBytesSent;
		numBytesToSend -= numBytesSent;
	}
}

/******************************************************************************/

MemoryStreamPtr HTTPRequestor::readResponse(SOCKET sock)
{
	MemoryStreamPtr recvDataPtr;
	ulong contentLength;
	bool chunked;
	int status;
	ulong numBytesToRecv;
	ulong numBytesRecvd;

	while(TRUE)
	{
		status = readAllHeaders(sock, contentLength, chunked);
		if(status == 100)
			continue;
		if(status != 200)
			break;	//throw ASIException("HTTPRequestor::readResponse", "Bad HTTP status(%d)", status);
		if((contentLength == 0) && !chunked)
			break;

		recvDataPtr = MemoryStream::newInstance();
		if(!chunked)
		{
			recvDataPtr->setSize(contentLength);
			receiveBuffer(sock, recvDataPtr->getBuffer(), recvDataPtr->getSize());
		}
		else
		{
			numBytesRecvd = 0;
			numBytesToRecv = readChunkLength(sock);
			while(numBytesToRecv > 0)
			{
				recvDataPtr->setSize(numBytesRecvd + numBytesToRecv);
				receiveBuffer(sock, recvDataPtr->getBuffer() + numBytesRecvd, numBytesToRecv);
				numBytesRecvd += numBytesToRecv;

				readBlankLength(sock);
				numBytesToRecv = readChunkLength(sock);
			}
		}
		break;
	}

	return recvDataPtr;
}

/******************************************************************************/

CStrVar HTTPRequestor::readNextLine(SOCKET sock)
{
	CStrVar value;
	byte data;

	while(TRUE)
	{
		receiveBuffer(sock, &data, 1);
		if(data == '\r')
		{
			receiveBuffer(sock, &data, 1);
			if(data != '\n')
				throw ASIException("HTTPRequestor::readNextLine", "Expecting LF, got(%u)", (unsigned)data);
			break;
		}
		value.concatVarg("%c", data);
	}

	return value;
}

/******************************************************************************/

int HTTPRequestor::readAllHeaders(SOCKET sock, ulong& contentLength, bool& chunked)
{
	CStr64 headerName;
	CStrVar headerValue;
	CStrVarVector parts;
	int status;

	status = 0;
	contentLength = 0;
	chunked = FALSE;

	// read Status line
	readNextHeader(sock, headerName, headerValue);
	if(strncmp(headerName.c_str(), "HTTP", 4) != 0)
		throw ASIException("HTTPRequestor::readAllHeaders", "Did not get HTTP response(%s)", headerName.c_str());
	parts.split(headerName.c_str(), " ");
	if(parts.size() >= 2)
	{
		headerValue.copy(parts[1].c_str());
		sscanf(headerValue.c_str(), "%d", &status);
	}
	else
		throw ASIException("HTTPRequestor::readAllHeaders", "Can't parse HTTP response(%s)", headerName.c_str());

	while(TRUE)
	{
		readNextHeader(sock, headerName, headerValue);
		if(headerName.len() == 0)
			break;
		headerName.toLower();
		headerValue.toLower();
		if(headerName == "content-length")
			sscanf(headerValue.c_str(), "%ld", &contentLength);
		else if((headerName == "transfer-encoding") && (headerValue == "chunked"))
			chunked = TRUE;
	}

	return status;
}

/******************************************************************************/

void HTTPRequestor::readNextHeader(SOCKET sock, CStr64& headerName, CStrVar& headerValue)
{
	CStrVar header;
	const char* pos;

	headerName.clear();
	headerValue.clear();

	header = readNextLine(sock);

	pos = strchr(header.c_str(), ':');
	if(pos != NULL)
	{
		headerName.ncopy(header.c_str(), pos - header.c_str());
		pos++;
		headerValue.copy(pos);
		headerValue.compress(csw_Leading);
	}
	else
		headerName.copy(header.c_str());
}

/******************************************************************************/

ulong HTTPRequestor::readChunkLength(SOCKET sock)
{
	CStrVar line;
	CStr32 sizeStr;
	const char* pos;

	line = readNextLine(sock);

	pos = strchr(line.c_str(), ';');
	if(pos != NULL)
		sizeStr.ncopy(line.c_str(), pos - line.c_str());
	else
		sizeStr.copy(line.c_str());

	return tHexStrToULong(sizeStr.c_str());
}

/******************************************************************************/

void HTTPRequestor::readBlankLength(SOCKET sock)
{
	CStrVar line = readNextLine(sock);

	if(line.len() != 0)
		throw ASIException("HTTPRequestor::readBlankLength", "Expecting blank line");
}

/******************************************************************************/

void HTTPRequestor::receiveBuffer(SOCKET sock, byte* data, ulong dataLen)
{
	const byte* bytesToRecv;
	int numBytesToRecv;
	int numBytesRecvd;
	TTick startTick = tGetTickCount();

	// send the data
	bytesToRecv = data;
	numBytesToRecv = dataLen;
	while(numBytesToRecv > 0)
	{
		// check for timeout
		if(tHaveSecsPast(startTick, 30))
			throw ASIException("HTTPRequestor::receiveBuffer", "Timeout has expired");

		numBytesRecvd = recv(sock, (char*)bytesToRecv, numBytesToRecv, 0);
		if(numBytesRecvd == SOCKET_ERROR)
			throw ASIException("HTTPRequestor::receiveBuffer", "recv failed, error:%d", WSAGetLastError());

		bytesToRecv += numBytesRecvd;
		numBytesToRecv -= numBytesRecvd;
	}
}

/******************************************************************************/

}; //namespace asi

/******************************************************************************/
/******************************************************************************/

