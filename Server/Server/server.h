#pragma once
#include "pch.h"

enum ServerAuthenticationMethods
{
	SAUTHM_none = 0,
	SAUTHM_single_step = 1
};

class Server
{
protected:
	//listening variables
	WSADATA wsData;
	WORD ver;
	int wsOk;
	SOCKET listening_socket;
	SOCKET insock;
	sockaddr_in hint;
	char buf[4096];
	char bufout[4096];
	//ins
	int base_port;
	std::string welcomeMsg;
	char* dc_command1=nullptr;
	char* dc_command2=nullptr;
	int authentication_method=SAUTHM_none;
	std::string database_file;
	std::string config_file;
	//state
	bool running = true;


	//dodanie socketa do fd_set nie jest rownowazne z zapamietaniem adresu
	//fd socket sets
	fd_set master;
	std::vector<UserSocket*> clients;

public:
	//class methods 

	//defaults
	Server();
	~Server();

	//customs
	void ServerBase();
	Server(int);
	void Run();

	virtual void OnDataRecieved();
protected:
	//helping functions for publics
	bool initialize_winsock();
	bool create_listening_socket();//expected 54000
	void create_set();
	void handlingloop();
	void clean();
};






