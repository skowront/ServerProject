#include "pch.h"

Client::Client()
{
}

Client::~Client()
{
	clean();
}

Client::Client(std::string ip, int _port)
{
	serverIpAdress = ip;
	base_port = _port;
}

bool Client::Run(double connectTimeout, bool unconditional)
{

	if (!initialize_winsock())
	{
		//clean();
		return false;
	}
	if (!create_socket())
	{
		//clean();
		return false;
	}
	if (!connectToServer(connectTimeout,unconditional))
	{
		//clean();
		return false;
	}
	return true;	
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

bool Client::connectToServer(double connectTimeout,bool unconditional)//error
{
	if (unconditional)
	{
		int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
		if (connResult == SOCKET_ERROR)
		{
			int err = WSAGetLastError();
			print("Can't connect to server, Err #" + WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			return false;
		}
		return true;
	}
	else
	{
		TIMEVAL Timeout;
		Timeout.tv_sec = connectTimeout;
		Timeout.tv_usec = 0;
		struct sockaddr_in address;  /* the libc network address data structure */

			//set the socket in non-blocking
		unsigned long iMode = 1;
		int iResult = ioctlsocket(sock, FIONBIO, &iMode);
		if (iResult != NO_ERROR)
		{
			printf("ioctlsocket failed with error: %ld\n", iResult);
		}

		if (connect(sock, (sockaddr*)&hint, sizeof(hint)) == false)
		{
			return false;
		}

		// restart the socket mode
		iMode = 0;
		iResult = ioctlsocket(sock, FIONBIO, &iMode);
		if (iResult != NO_ERROR)
		{
			printf("ioctlsocket failed with error: %ld\n", iResult);
		}

		fd_set Write, Err;
		FD_ZERO(&Write);
		FD_ZERO(&Err);
		FD_SET(sock, &Write);
		FD_SET(sock, &Err);

		// check if the socket is ready
		select(0, NULL, &Write, &Err, &Timeout);
		if (FD_ISSET(sock, &Write))
		{
			return true;
		}
	}
}

void Client::clean()
{
	closesocket(sock);
	WSACleanup();
}

std::string Client::RecieveMsg(bool wait_for_msg, bool&msg_recieved, double timeout)
{
	std::clock_t start = std::clock();
	double duration = 0;
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
	} while (wait_for_msg&&duration < timeout);
}

bool Client::SendMsg(std::string msg)
{
	// Send the text
	int sendResult;
	sendResult = send(sock, msg.c_str(), msg.size() + 1, 0);
	if (sendResult != SOCKET_ERROR)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}
