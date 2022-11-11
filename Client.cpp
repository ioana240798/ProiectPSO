#include "Client.h"
#include <string>

void Client::onClientConnected(int clientSocket)
{
	std::string welcomeMsg = "Bun venit pe server!\r\n";
	sendToClient(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1);
}

void Client::onClientDisconnected(int clientSocket)
{

}

void Client::onMessageReceived(int clientSocket, const char* msg, int length)
{
	broadcastToClients(clientSocket, msg, length);
}