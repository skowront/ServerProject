#pragma once
#include "pch.h"

struct UserSocket
{
	int fd_index;
	std::string ip;
	int id;
};

class Server
{
private:
	//listening variables
	WSADATA wsData;
	WORD ver;
	int wsOk;
	SOCKET listening_socket;
	sockaddr_in hint;
	//ins
	int base_port;

	//state
	bool running = true;


	//dodanie socketa do fd_set nie jest rownowazne z zapamietaniem adresu
	//fd socket sets
	fd_set master;
	std::vector<UserSocket> clients;

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
	bool create_listening_socket();//expected 54000
	void create_set();
	void handlingloop();
	void clean();
};






