#include "server1.h"
#include<iostream>
#include<string>

Clistener::Clistener(std::string ipaddress, int port, messagereceivedhandler handler) 
	: m_ipaddress(ipaddress), m_port(port), messagereceived(handler) {}

Clistener::~Clistener()
{
	cleanup();
}

//send the msg 
void Clistener::send(int clientsocket, std::string msg)
{
	send(clientsocket, msg.c_str());
}

//initialize win sock
bool Clistener::init()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsinit = WSAStartup(ver, &data);
	return wsinit == 0;

}

//the main loop
void Clistener::run()
{
	char buf[MAX_BUFFER_SIZE];
	while (true)
	{
		//create listening socket
		SOCKET listening = createsocket();
		if (listening == INVALID_SOCKET)
		{
			break;
		}

		SOCKET client = waitforconnection(listening);

		if (client != INVALID_SOCKET)
		{
			closesocket(listening);
			int bytesreceived = 0;
			do
			{
				ZeroMemory(buf, MAX_BUFFER_SIZE);
				bytesreceived = recv(client, buf, MAX_BUFFER_SIZE, 0);
				if (bytesreceived > 0)
				{
					if (messagereceived != NULL)
					{
						messagereceived(this, client, std::string(buf, 0, bytesreceived));
					}
				}
			} while (bytesreceived > 0);

			//cout << string(buf, 0, bytesreceived) << endl;
			
			closesocket(client);
		}
	}
}

void Clistener::cleanup()
{
	WSACleanup();
}

//create a socket
SOCKET Clistener::createsocket()
{
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening != INVALID_SOCKET)
	{
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(m_port);
		hint.sin_addr.S_un.S_addr = INADDR_ANY;

		int bindok = bind(listening, (sockaddr*)&hint, sizeof(hint));
		if (bindok != SOCKET_ERROR)
		{
			int listenok = listen(listening, SOMAXCONN);
			if (listenok == SOCKET_ERROR)
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	return listening;
}

//wait for connection
SOCKET Clistener::waitforconnection(SOCKET listening)
{
	SOCKET client = accept(listening, NULL, NULL);
	return client;
}
