#include "pch.h"

Client::Client()
{
}

Client::~Client()
{
	handle();
	clean();
}

Client::Client(std::string ip, int _port)
{
	serverIpAdress = ip;
	base_port = _port;
}

void Client::Run()
{

	if (!initialize_winsock())
	{
		return;
	}
	if (!create_socket())
	{
		return;
	}
	connectToServer();
}

std::string Client::RecieveMsg(bool wait_for_msg ,bool&msg_recieved,double timeout)
{
	std::clock_t start=std::clock();
	double duration=0;
	do
	{
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		ZeroMemory(buf, 4096);
		int   rc;
		u_long nonblocking_enabled = TRUE;
		ioctlsocket(sock, FIONBIO, &nonblocking_enabled);
		errno = 0;
		rc = recv(sock, buf, 4096, 0);
		if (rc != NOERROR)
		{
			if (rc > 0)
			{
				msg_recieved = true;
				std::string out(buf, 0, rc);
				//for (int k = 0; k < out.length(); k++)
				//{
				//	bool oneenter = false;
				//	if (out[k] == '\n')
				//	{
				//		if (oneenter)
				//		{
				//			out.erase(k);
				//		}
				//		oneenter = true;
				//	}
				//	if (out[k] == '\r')
				//	{
				//		out.erase(k);
				//	}
				//}
				return out;
				break;
			}
		}
	} while (wait_for_msg&&duration<timeout);
}

bool Client::SendMsg(std::string msg)
{
	// Send the text
	int sendResult;
	sendResult = send(sock, msg.c_str(), msg.size() + 1, 0);
	if (sendResult!=SOCKET_ERROR)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

bool Client::initialize_winsock()
{
	ver = MAKEWORD(2, 2);
	wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		print("Cant initialize winsock");
		return false;
	}
	else
	{
		return true;
	}
}

bool Client::create_socket()
{
	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		print("Can't create socket, Err #" + WSAGetLastError());
		WSACleanup();
		return false;
	}

	// Fill in a hint structure
	hint.sin_family = AF_INET;
	hint.sin_port = htons(base_port);
	inet_pton(AF_INET, serverIpAdress.c_str(), &hint.sin_addr);
	return true;
}

bool Client::connectToServer()//error
{
	int connResult= connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		print("Can't connect to server, Err #" + WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return false;
	}
	return true;
}



void Client::handle()
{
	
}

void Client::clean()
{
	closesocket(sock);
	WSACleanup();
}
