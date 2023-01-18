#pragma once
#pragma once
#include "TcpListen.h"

class WebServer : public TcpListen
{
public:

	WebServer(const char* ipAddress, int port) :
		TcpListen(ipAddress, port) { } 

protected:

	virtual void onClientConnected(int clientSocket);

	virtual void onClientDisconnected(int clientSocket);

	virtual void onMessageReceived(int clientSocket, const char* msg, int length);
};
