#include<iostream>
#include<string>

#include "server1.h"
#include "client1.h"

using namespace std;

void listener_messagereceived(Clistener* listener, int server, string msg);

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
		string ip = "127.0.0.1", userinput;
		int portnum = 54000;
		cout << "> ";
		getline(cin, userinput);
		Slistener client(ip, portnum, userinput);
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
