#include<iostream>
#include<string>

#include "client1.h"

Slistener::Slistener(std::string ipaddress, int port, messagereceivedhandler handler)
	: m_ipaddress(ipaddress), m_port(port), messagereceived(handler) {}

Slistener::~Slistener()
{
	cleanup();
}

//send the msg to the specified client
void Slistener::send(int clientsocket, std::string msg)
{
	send(clientsocket, msg.c_str());
}

//initialize win sock
bool Slistener::init()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsinit = WSAStartup(ver, &data);
	return wsinit == 0;

}

//the main loop
void Slistener::run()
{
	char buf[MAX_BUFFER_SIZE];
	while (true)
	{
		//create listening socket
		SOCKET sock = createsocket();
		if (sock == INVALID_SOCKET)
		{
			break;
		}

		SOCKET client = connecttoserver();

		if (client != INVALID_SOCKET)
		{
			closesocket(sock);
			int bytesreceived = 0;
			do
			{
				//send text
				if (messagereceived  > 0)
				{
						//wait for response
						ZeroMemory(buf, 4096);
						bytesreceived = recv(sock, buf, 4096, 0);
						if (bytesreceived > 0)
						{
							//echo response
							cout << "SERVER> " << string(buf, 0, bytesreceived);
						}
				}
			} while (messagereceived > 0);

			closesocket(client);
		}
	}
} 

void Slistener::cleanup()
{
	WSACleanup();
}

//create a socket
SOCKET Slistener::createsocket()
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock != INVALID_SOCKET)
	{
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ipaddress.c_str(), &hint.sin_addr);

		int bindok = bind(sock, (sockaddr*)&hint, sizeof(hint));
		if (bindok != SOCKET_ERROR)
		{
			int listenok = listen(sock, SOMAXCONN);
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
	return sock;
}

//connect to server
SOCKET Slistener::connecttoserver()
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ipaddress.c_str(), &hint.sin_addr);
	int connresult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	return connresult;
}
