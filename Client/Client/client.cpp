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
	bool once = true;
	bool dosend = false;
	do
	{
		if (once)
		{
			std::getline(std::cin, userInput);
			dosend = true;
			once = false;	
		}
		// Prompt the user for some text
		if (_kbhit())
		{
			std::getline(std::cin, userInput);
			dosend = true;
		}
		

		if (userInput.size() > 0)		// Make sure the user has typed in something
		{
			// Send the text
			int sendResult;
			dosend? sendResult=send(sock, userInput.c_str(), userInput.size() + 1, 0):false;
			dosend = false;
			//if (sendResult != SOCKET_ERROR)
			/*fd_set master;
			FD_ZERO(&master);
			listen(sock,SOMAXCONN);
			FD_SET(sock, &master);
			fd_set copy=master;*/
			{
				//if (select(0,&copy,nullptr,nullptr,nullptr)!=0)
				//{
				//	ZeroMemory(buf, 4096);
				//	int bytesReceived = recv(sock, buf, 4096, 0);
				//	if (bytesReceived > 0)
				//	{
				//		// Echo response to console
				//		print("SERVER> " + std::string(buf, 0, bytesReceived));
				//	}
				//}
				// Wait for response
				
				
				ZeroMemory(buf, 4096);
				int   rc;
				u_long nonblocking_enabled = TRUE;
				ioctlsocket(sock, FIONBIO, &nonblocking_enabled);
				errno = 0;
				rc = recv(sock, buf, 4096,0);
				if (rc !=NOERROR)
				{
						if (rc > 0)
						{
							std::string out(buf, 0, rc);
							for (int k = 0; k < out.length(); k++)
							{
								bool oneenter = false;
								if (out[k]=='\n')
								{
									if (oneenter)
									{
										out.erase(k);
									}
									oneenter = true;
								}
								if (out[k]=='\r')
								{
									out.erase(k);
								}
							}
								print("SERVER> " + out);
						}
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
