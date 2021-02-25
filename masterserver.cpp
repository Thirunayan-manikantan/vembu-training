#include<iostream>
#include<string>
#include<sstream>
#include<ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    //initialize winsock
    WSADATA WsData;
    WORD ver = MAKEWORD(2, 2);
    int wsock = WSAStartup(ver, &WsData);
    if (wsock != 0)
    {
        cerr << "cant initialize the winsock" << endl;
        return;
    }

    //create socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET)
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

    fd_set master;
    FD_ZERO(&master);
    FD_SET(listening, &master);
    try
    {
        while (true)
        {
            fd_set copy = master;

            int socketcount = select(0, &copy, nullptr, nullptr, nullptr);
            for (int i = 0; i < socketcount; i++)
            {
                SOCKET sock = copy.fd_array[i];

                if (sock == listening)
                {
                    //accept the new connection
                    SOCKET client = accept(listening, nullptr, nullptr);

                    //add the new connection to the list of connected clients
                    FD_SET(client, &master);

                    //send a welcome message to the connected client
                    string welcomemsg = "Welcome to chatbox !!\r\n";
                    send(client, welcomemsg.c_str(), welcomemsg.size() + 1, 0);
                }

                else
                {
                    char buf[4096];
                    ZeroMemory(buf, 4096);

                    //receive msg
                    int bytesreceived = recv(sock, buf, 4096, 0);
                    if (bytesreceived <= 0)
                    {
                        //close client
                        closesocket(sock);
                        FD_CLR(sock, &master);
                    }
                    else
                    {
                        //send msg to other clients
                        for (int i = 0; i < master.fd_count; i++)
                        {
                            SOCKET outsock = master.fd_array[i];
                            if (outsock != listening && outsock != sock)
                            {
                                ostringstream ss;
                                ss << "SOCKET " << sock << ":" << buf << "\r\n";
                                string strout = ss.str();

                                send(outsock, strout.c_str(), strout.size() + 1, 0);
                            }
                        }
                    }
                }
            }
        }
    }
    catch (SocketException& e)
    {
        cout << "Exception caught" << e.description();
    }

    //cleanup winsock
    WSACleanup();
}
