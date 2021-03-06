#pragma once

class Client
{
protected:
	//ins
	std::string serverIpAdress = "83.4.223.224";
	int base_port;

	//variables
	WSAData wsData;
	WORD ver;
	int wsOk;
	SOCKET sock;
	sockaddr_in hint;

	char buf[4096];


public:
	//default contstructors
	Client();
	~Client();

	//custom contstuctors
	Client(std::string, int);
	bool Run(double connectTimeout, bool unconditional);

	
protected:
	//help for publics
	bool initialize_winsock();
	bool create_socket();
	bool connectToServer(double connectTimeout, bool unconditional);
	void clean();

public:
	std::string RecieveMsg(bool wait_for_msg, bool& msg_recieved, double timeout);//recommended to be in a while loop
	bool SendMsg(std::string msg);
};

