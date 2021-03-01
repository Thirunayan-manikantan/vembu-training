#pragma once

#include<string>
#include<WS2tcpip.h>  //header file for winsock functions
#pragma comment(lib, "ws2_32.lib")  //winsock library file
#define MAX_BUFFER_SIZE (50000)

class Slistener
{
public:
	Slistener(std::string ipaddress, int port, std::string msg);
	~Slistener();

	//send the msg to the specified client
	int send(int clientsocket, std::string msg);

	//initialize win sock
	bool init();

	//the main loop
	void run();

	void cleanup();

private:

	//create a socket
	SOCKET createsocket();

	//connect to server
	SOCKET connecttoserver();

	std::string m_ipaddress, m_msg;
	int m_port;
};
