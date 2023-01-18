#include "Client.h"
#include "WebServer.h"

// using namespace std;

void main()
{
	//Client client("0.0.0.0", 54000); //192.168.100.9
	//if (client.init() != 0)
	//	return;

	
	//WebServer webserver("192.168.100.9", 8080);
	//WebServer webserver("172.20.10.2", 8080);
	WebServer webserver("0.0.0.0", 8080);
	
	if (webserver.init() != 0)
		return;


	webserver.run();

	system("pause");
}