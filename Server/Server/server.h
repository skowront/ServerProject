#pragma once
#include "pch.h"

class Server
{
private:
	//listening variables
	WSADATA wsData;
	WORD ver;
	int wsOk;
	SOCKET listening_socket;
	sockaddr_in def_sock_adress;
	//ins
	int base_port;

	//state
	bool running = true;

	//fd socket sets
	fd_set master;
	int socketCount;

public:
	//class methods 

	//defaults
	Server();
	~Server();

	//customs
	Server(int);
	void Run();


private:
	//helping functions for publics
	bool initialize_winsock();
	bool create_listening_socket(int base_port);//expected 54000
	void create_set();
	void handlingloop();
	void clean();
};






