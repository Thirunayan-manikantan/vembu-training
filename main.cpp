#include<iostream>
#include<string>

#include "listener.h"

using namespace std;

void listener_messagereceived(clistener* listener, int server, string msg);

void main()
{
		string ip = "127.0.0.1";
		int portnum = 54000;
		clistener server(ip, portnum, listener_messagereceived);
		if (server.init())
		{
			server.run();
		}
}
void listener_messagereceived(clistener* listener, int server, string msg)
{
	listener->send(server, msg);
}
