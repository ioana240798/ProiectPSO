#pragma once

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

class TcpListen
{

public:

	TcpListen(const char* ipAddress, int port) :
		adresaIP(ipAddress), portul(port) { }

	int init();

	int run();

protected:

	
	virtual void onClientConnected(int clientSocket);

	
	virtual void onClientDisconnected(int clientSocket);

	
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);

	
	void sendToClient(int clientSocket, const char* msg, int length);

	
	void broadcastToClients(int sendingClient, const char* msg, int length);

private:

	const char* adresaIP;	
	int				portul;			
	int				socketul;		
	fd_set			filedescriptorul;		
};