#include "TcpListen.h"
#include <iostream>
#include <string>
#include <sstream>


int TcpListen::init()
{
	
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		return wsOk;
	}

	
	socketul = socket(AF_INET, SOCK_STREAM, 0);
	if (socketul == INVALID_SOCKET)
	{
		return WSAGetLastError();
	}

	
	sockaddr_in adr;
	adr.sin_family = AF_INET;
	adr.sin_port = htons(portul);
	inet_pton(AF_INET, adresaIP, &adr.sin_addr);

	if (bind(socketul, (sockaddr*)&adr, sizeof(adr)) == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}

	
	if (listen(socketul, SOMAXCONN) == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}

	
	FD_ZERO(&filedescriptorul);
	
	FD_SET(socketul, &filedescriptorul);

	return 0;
}

int TcpListen::run()
{
	bool running = true;

	while (running)
	{

		fd_set copie = filedescriptorul;

		
		int socketCount = select(0, &copie, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copie.fd_array[i];

			if (sock == socketul)
			{

				SOCKET client = accept(socketul, nullptr, nullptr);

				FD_SET(client, &filedescriptorul);

				onClientConnected(client);
			}
			else 
			{
				char buf[4096];
				ZeroMemory(buf, 4096);


				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{

					onClientDisconnected(sock);
					closesocket(sock);
					FD_CLR(sock, &filedescriptorul);
				}
				else
				{
					onMessageReceived(sock, buf, bytesIn);
				}
			}
		}
	}


	FD_CLR(socketul, &filedescriptorul);
	closesocket(socketul);

	while (filedescriptorul.fd_count > 0)
	{

		SOCKET sock = filedescriptorul.fd_array[0];


		FD_CLR(sock, &filedescriptorul);
		closesocket(sock);
	}


	WSACleanup();
	return 0;
}


void TcpListen::sendToClient(int clientSocket, const char* msg, int length)
{
	send(clientSocket, msg, length, 0);
	std::cout << "SendToClient\n";
}

void TcpListen::broadcastToClients(int sendingClient, const char* msg, int length)
{
	for (int i = 0; i < filedescriptorul.fd_count; i++)
	{
		SOCKET outSock = filedescriptorul.fd_array[i];
		if (outSock != socketul && outSock != sendingClient)
		{
			sendToClient(outSock, msg, length);
		}
	}
}

void TcpListen::onClientConnected(int clientSocket)
{

}

void TcpListen::onClientDisconnected(int clientSocket)
{
	
}

void TcpListen::onMessageReceived(int clientSocket, const char* msg, int length)
{
	
}
