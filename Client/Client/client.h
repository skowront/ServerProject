#pragma once

class Client
{
private:
	//ins
	std::string serverIpAdress = "83.4.223.224";
	int base_port;

	//variables
	WSAData wsData;
	WORD ver;
	int wsOk;
	SOCKET listening_socket;
	sockaddr_in hint;


public:
	//default contstructors
	Client();
	~Client();

	//custom contstuctors
	Client(std::string, int);
	void Run();
private:
	//help for publics
	bool initialize_winsock();
	bool create_listening_socket();
	bool connectToServer();
	void handlingloop();
	void clean();
};

