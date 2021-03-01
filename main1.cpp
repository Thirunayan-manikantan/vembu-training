#include<iostream>
#include<string>

#include "server1.h"
#include "client1.h"

using namespace std;

void listener_messagereceived(Clistener* listener, int server, string msg);
void listener_messagereceived1(Slistener* listener, int client, string msg);

void main()
{
	string choice;
	cout << "1) server \t 2) client" << endl;
	getline(cin, choice);

	if (choice == "server")
	{
		string ip = "127.0.0.1";
		int portnum = 54000;
		Clistener server(ip, portnum, listener_messagereceived);
		if (server.init())
		{
			server.run();
		}
	}

	if (choice == "client")
	{
		string ip = "127.0.0.1";
		int portnum = 54000;
		Slistener client(ip, portnum, listener_messagereceived1);
		if (client.init())
		{
			client.run();
		}
	}
}
void listener_messagereceived(Clistener* listener, int server, string msg)
{
	listener->send(server, msg);
}
void listener_messagereceived1(Slistener* listener, int client, string msg)
{
	getline(cin, msg);
	listener->send(client, msg);
}
