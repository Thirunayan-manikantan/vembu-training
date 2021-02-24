#include<iostream>
#include<string>
#include<ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main()
{
    //ip address of server
    string ipaddress = "127.0.0.1";

    //listening port num of server
    int port = 54000;

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
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        cerr << "cant create a socket" << endl;
        WSACleanup();
        return;
    }

    //bind the ip address and port to socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipaddress.cstr(), &hint.sin_addr);

    //connect to server
    int connresult = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if(connresult == SOCKET_ERROR)
    {
        cerr << "cant connect to server" << endl;
        closesocket(sock);
        WSACleanup();
        return;
    }

    //do-while loop to send and receive data
    char buf[4096];
    string userinput;
    do
    {
        //prompt user for text
        cout << "> ";
        getline(cin, userinput);

        //send text
        if(userinput.size() > 0)
        {
            int sendresult = send(sock, userinput.c_str(), userinput.size()+1, 0);
            if(sendresult != SOCKET_ERROR)
            {
                //wait for response
                ZeroMemory(buf ,4096);
                int bytesreceived = recv(sock, buf, 4096, 0);
                if(bytesreceived > 0)
                {
                    //echo response
                    cout << "SERVER> " << string(buf, 0, bytesreceived) << endl;
                }
            }
        }
    } while(userinput.size() > 0);

    //close socket
    closesocket(sock);

    //close winsock
    WSACleanup();
}