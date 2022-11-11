#pragma once
#include "TcpListen.h"

class Client : public TcpListen
{
public:

	Client(const char* ipAddress, int port) :
		TcpListen(ipAddress, port) { }

protected:

	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	// Handler for when a message is received from the client
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);
};