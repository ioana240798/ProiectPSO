#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h> // pentru getnameinfo()

// Headere pentru socket-uri
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>

#define SIZE 1024
#define BACKLOG 10  // Transmis catre listen()

void report(struct sockaddr_in *serverAddress);

void setHttpHeader(char httpHeader[])
{
    // Fisier obiect de returnat
    FILE *htmlData = fopen("actiuni.html", "r");

    char line[100];
    char responseData[8000];
    while (fgets(line, 100, htmlData) != 0) {
        strcat(responseData, line);
    }
    // char httpHeader[8000] = "HTTP/1.1 200 OK\r\n\n";
    strcat(httpHeader, responseData);
}

int main(void)
{
    char httpHeader[1000000] = "HTTP/1.1 200 OK\r\n\n";

    // Configurare socket: creeaza socket pentru comunicare, returneaza un descriptor
    // -----------------------------------------------------------------------------------------------------------------
    int serverSocket = socket(
        AF_INET,      // Domeniu: specifică familia de protocol
        SOCK_STREAM,  // Tip: specifică semantica comunicării
        0             // Protocol: 0 deoarece exista un singur protocol pentru familia specificata
    );

    // Structura locala de adrese
    // -----------------------------------------------------------------------------------------------------------------
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8001);
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//inet_addr("127.0.0.1"); 



    // Leg socket-ul la adresa locala
    // -----------------------------------------------------------------------------------------------------------------
    // bind() atribuie socket-ului adresa specificată de serverAddress
    // la care se face referire de către descriptorul de fișier serverSocket.
    bind(
        serverSocket,                         // descriptor de fișier care se referă la un socket
        (struct sockaddr *) &serverAddress,   // Adresa care urmeaza sa fie atribuita socket-ului
        sizeof(serverAddress)                 // Dimensiunea (octeți) a structurii adresei
    );

    // Listen pentru conexiunile de intrare
    // -----------------------------------------------------------------------------------------------------------------
    int listening = listen(serverSocket, BACKLOG);
    if (listening < 0) {
        printf("Eroare: Serverul nu asculta.\n");
        return 1;
    }
    report(&serverAddress);     // Funcție de raport personalizat
    setHttpHeader(httpHeader);  // Funcție personalizată pentru a seta header-ul
    int clientSocket;

    // Astept o conexiune, creez un socket conectat daca o conexiune este in asteptare
    // -----------------------------------------------------------------------------------------------------------------
    while(1) {
        clientSocket = accept(serverSocket, NULL, NULL);
        send(clientSocket, httpHeader, sizeof(httpHeader), 0);
        close(clientSocket);
    }
    return 0;
}

void report(struct sockaddr_in *serverAddress)
{
    char hostBuffer[INET6_ADDRSTRLEN];
    char serviceBuffer[NI_MAXSERV]; // definit in <netdb.h>
    socklen_t addr_len = sizeof(*serverAddress);
    int err = getnameinfo(
        (struct sockaddr *) serverAddress,
        addr_len,
        hostBuffer,
        sizeof(hostBuffer),
        serviceBuffer,
        sizeof(serviceBuffer),
        NI_NUMERICHOST
    );
    if (err != 0) {
        printf("Nu functioneaza!\n");
    }
    printf("\n\n\tServer-ul asculta: http://%s:%s\n", hostBuffer, serviceBuffer);
}