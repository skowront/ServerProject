#include "pch.h"

Client::Client()
{
}

Client::~Client()
{
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
	handlingloop();
	clean();
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



void Client::handlingloop()
{
	char buf[4096];
	std::string userInput;
	std::string temp;
	bool lineready = false;
	do
	{
		// Prompt the user for some text
		std::getline(std::cin, userInput);

		if (userInput.size() > 0)		// Make sure the user has typed in something
		{
			// Send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					// Echo response to console
					print("SERVER> " + std::string(buf, 0, bytesReceived));
				}
			}
		}

	} while (userInput.size() > 0);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}

void Client::clean()
{
	closesocket(sock);
	WSACleanup();
}
