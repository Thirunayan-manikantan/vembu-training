#pragma once

#include<string>
#include<WS2tcpip.h>  //header file for winsock functions
#pragma comment(lib, "ws2_32.lib")  //winsock library file
#define MAX_BUFFER_SIZE (50000)

//forward dec of class
class Slistener;

//callback to receive data
typedef void(*messagereceivedhandler)(slistener* listener, int socketid, std::string msg);

class Slistener
{
public:
	slistener(std::string ipaddress, int port, messagereceivedhandler handler);
	~slistener();

	//send the msg to the specified client
	void send(int clientsocket, std::string msg);

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

	std::string m_ipaddress;
	int m_port;
	messagereceivedhandler messagereceived;
};
