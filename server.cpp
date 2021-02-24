#include<iostream>
#include<string>
#include<ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main()
{
    //initialize winsock
    WSADATA WsData;
    WORD ver = MAKEWORD(2, 2);
    int wsock = WSAStartup(ver, &WsData);
    if(wsock !=0)
    {
        cerr << "cant initialize the winsock" << endl;
       return;
    }

    //create socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == INVALID_SOCKET)
    {
        cerr << "cant create a socket" << endl;
       return;
    }
 
    //bind the ip address and port to socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    //tell winsock the socket is for listening
    listen(listening, SOMAXCONN);

    //wait for a connection
    sockaddr_in client;
    int clientsize = sizeof(client);

    SOCKET clientsocket = accept(listening, (sockaddr*)&client, &clientsize);

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXSERV);

    if(getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0)==0)
    {
        cout << host << "connected on port" << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << "connected on port" << ntohs(client.sin_port) << endl; 
    }

    //close listening socket
    closesocket(listening);

    //while loop to accept and echo msg back to client
    char buf[4096];
    while(true)
    {
        ZeroMemory(buf, 4096);

        //wait for client to send data
        int bytesreceived = recv(clientsocket, buf, 4096, 0);
        if(bytesreceived == SOCKET_ERROR)
        {
            cerr << "error in recv()" << endl;
            break;
        }
        if(bytesreceived == 0)
        {
            cout << "client disconnected" << endl;
            break;
        }

        cout << string(buf, 0, bytesreceived) << endl;

        //echo msg back to client
        send(clientsocket, buf, bytesreceived+1, 0);

    }

    //close socket
    closesocket(clientsocket);

    //close winsock
    WSACleanup();

}