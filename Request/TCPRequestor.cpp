/* TCPRequestor.cpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"
#include "MemoryStream.h"
#include "BinaryFiler.h"
#include "TCPRequestor.h"

namespace asi
{

/******************************************************************************/
/******************************************************************************/

MemoryStreamPtr TCPRequestor::sendRequest(MemoryStreamPtr rqstPtr)
{
	MemoryStreamPtr sendPtr = MemoryStream::newInstance();
	DataFilerPtr filerPtr = BinaryFiler::newInstance(sendPtr, bo_BigEndian);

	filerPtr->writeLong(rqstPtr->getSize());
	sendPtr->writeBuffer(rqstPtr->getBuffer(), rqstPtr->getSize());

	return connectAndSend(sendPtr);
}

/******************************************************************************/

MemoryStreamPtr TCPRequestor::connectAndSend(MemoryStreamPtr sendPtr)
{
	SOCKET sock = INVALID_SOCKET;
	struct sockaddr_in sockaddr;
	ulong recvDataLen;
	MemoryStreamPtr recvDataPtr;
	int rc;

	// initialize address
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.S_un.S_un_b.s_b1 = 192;
	sockaddr.sin_addr.S_un.S_un_b.s_b2 = 168;
	sockaddr.sin_addr.S_un.S_un_b.s_b3 = 11;
	sockaddr.sin_addr.S_un.S_un_b.s_b4 = 42;
	sockaddr.sin_port = htons(11000);

	// create the socket
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		throw ASIException("TCPRequestor::connectAndSend", "socket() failed, error:%d", WSAGetLastError());

	try
	{
		// open a connection on the socket
		rc = connect(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
		if(!rc)
		{
			// send the data
			sendBuffer(sock, sendPtr->getBuffer(), sendPtr->getSize());

			// get the response size
			receiveBuffer(sock, (byte*)&recvDataLen, sizeof(recvDataLen));
			BinaryFiler::byteFlip(&recvDataLen, sizeof(recvDataLen));

			// get the response data
			recvDataPtr = MemoryStream::newInstance();
			recvDataPtr->setSize(recvDataLen);
			receiveBuffer(sock, recvDataPtr->getBuffer(), recvDataPtr->getSize());
		}
		else
			throw ASIException("TCPRequestor::connectAndSend", "connect() failed, error:%d", WSAGetLastError());
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

void TCPRequestor::sendBuffer(SOCKET sock, const byte* data, ulong dataLen)
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
			throw ASIException("TCPRequestor::sendBuffer", "Timeout has expired");

		numBytesSent = send(sock, (const char*)bytesToSend, numBytesToSend, 0);
		if(numBytesSent == SOCKET_ERROR)
			throw ASIException("TCPRequestor::sendBuffer", "send failed, error:%d", WSAGetLastError());

		bytesToSend += numBytesSent;
		numBytesToSend -= numBytesSent;
	}
}

/******************************************************************************/

void TCPRequestor::receiveBuffer(SOCKET sock, byte* data, ulong dataLen)
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
			throw ASIException("TCPRequestor::receiveBuffer", "Timeout has expired");

		numBytesRecvd = recv(sock, (char*)bytesToRecv, numBytesToRecv, 0);
		if(numBytesRecvd == SOCKET_ERROR)
			throw ASIException("TCPRequestor::receiveBuffer", "recv failed, error:%d", WSAGetLastError());

		bytesToRecv += numBytesRecvd;
		numBytesToRecv -= numBytesRecvd;
	}
}

/******************************************************************************/

}; //namespace asi

/******************************************************************************/
/******************************************************************************/
