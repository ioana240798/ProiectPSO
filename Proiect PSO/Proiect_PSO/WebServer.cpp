#include "WebServer.h"
#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <iterator>

using namespace std;



void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
	// Analizeaza sirul de solicitare al clientului, de ex. GET /index.html HTTP/1.1
	istringstream iss(msg);
	vector<string> parsed((istream_iterator<string>(iss)), istream_iterator<string>());

	// Unele valori implicite pentru iesire catre client (404 file not found)
	string content = "<h1>404 Not Found</h1>";
	string htmlFile = "/index.html";
	int errorCode = 404;

	// Daca solicitarea GET este valida se incerca sa se obtina numele
	if (parsed.size() >= 3 && parsed[0] == "GET")
	{
		htmlFile = parsed[1];

		//if-ul de aici e in caz ca http://localhost:8080/
		if (htmlFile == "/")
		{
			htmlFile = "/index.html";
		}
	}

	//// Deschide documentul din fisierul pagini
	ifstream f(".\\pagini" + htmlFile);

	//Verifica daca s-a deschis si daca a facut-o se ia intregul continut
	if (f.good())
	{
		string str((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
		content = str;
		errorCode = 200;
	}

	f.close();

	// Scrie documentul inapoi catre clientului
	std::ostringstream oss;
	oss << "HTTP/1.1 " << errorCode << " OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n"; 
	//oss << "Content-Type: text/html\r\n"; 
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	std::string output = oss.str();
	int size = output.size() + 1;

	sendToClient(clientSocket, output.c_str(), size);
}



void WebServer::onClientConnected(int clientSocket)
{
	cout << "ClientConnected!\n";
}

void WebServer::onClientDisconnected(int clientSocket)
{
	cout << "ClientDisconnected!\n";
}


