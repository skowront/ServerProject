#include "pch.h"


Server::Server()
{
	ServerBase();
}

Server::~Server()
{
	if (dc_command1 != nullptr)
	{
		free(dc_command1);
	}
	if (dc_command2 != nullptr)
	{
		free(dc_command2);
	}
}

void Server::ServerBase()
{
	dc_command1 = (char*)malloc(sizeof(char)*sizeof("\\dc\n"));//alloc
	dc_command2 = (char*)malloc(sizeof(char)*sizeof("\\dc\r\n"));//alloc
	strcpy(dc_command1, "\\dc\n");
	strcpy(dc_command2, "\\dc\r\n");
	
}

Server::Server(int _base_port)
{
	ServerBase();
	base_port = _base_port;
}

void Server::Run()
{
	if (!initialize_winsock())
	{
		return;
	}
	if (!create_listening_socket())
	{
		return;
	}
	create_set();
	handlingloop();
	clean();
}

bool Server::initialize_winsock()
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

bool Server::create_listening_socket()
{
	//Create socket
	listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listening_socket == INVALID_SOCKET)
	{
		print("Can't create a socket! Quitting");
		return false;
	}

	// Bind the ip address and port to a socket

	hint.sin_family = AF_INET;
	hint.sin_port = htons(base_port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	bind(listening_socket, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening_socket, SOMAXCONN);
	
	return true;
}

void Server::create_set()
{
	// Create the master file descriptor set and zero it
	
	clients.clear(); 
	FD_ZERO(&master);
	

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections 
	
	UserSocket* us = new UserSocket(0,nullptr,0);
	clients.push_back(us);
	FD_SET(listening_socket, &master);
	 
	// this will be changed by the \quit command (see below, bonus not in video!)
	
}

void Server::handlingloop()
{
	
	bool running = true;
	while (running)
	{
		// Make a copy of the master file descriptor set, this is SUPER important because
		// the call to select() is _DESTRUCTIVE_. The copy only contains the sockets that
		// are accepting inbound connection requests OR messages. 

		// E.g. You have a server and it's master file descriptor set contains 5 items;
		// the listening socket and four clients. When you pass this set into select(), 
		// only the sockets that are interacting with the server are returned. Let's say
		// only one client is sending a message at that time. The contents of 'copy' will
		// be one socket. You will have LOST all the other sockets.

		// SO MAKE A COPY OF THE MASTER LIST TO PASS INTO select() !!!

		fd_set copy = master;

		// See who's talking to us

		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
		
		// Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
			// Makes things easy for us doing this assignment
			insock = copy.fd_array[i];
			// Is it an inbound communication?
			if (insock == listening_socket)
			{
				// Accept a new connection
				SOCKET client = accept(listening_socket, nullptr, nullptr);
				if (client == INVALID_SOCKET) {
					print("accept failed with error:"+ WSAGetLastError() +'\n');
					closesocket(listening_socket);
					WSACleanup();
					return;
				}
				else
					print("Client connected");
				// Add the new connection to the list of connected clients
				UserSocket* us = new UserSocket(master.fd_count, nullptr, clients[clients.size() - 1]->id + 1);
				clients.push_back(us);
				FD_SET(client, &master);
				//TODO: create copy of socket list or common structure to hold em
				print("connected at: " + std::to_string(i));

				// Send a welcome message to the connected client
				welcomeMsg = "Welcome to the Server!\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
			}
			else // It's an inbound message
			{

				
				ZeroMemory(buf, 4096);

				// Receive message
				int bytesIn = recv(insock, buf, 4096, 0);
				if (bytesIn <= 0||strcmp(buf,dc_command1)==0|| strcmp(buf, dc_command2)==0)
				{
					// Drop the client
					closesocket(insock);
					FD_CLR(insock, &master);
					delete clients[i];
					clients.erase(clients.begin()+i);
					for (int j = i; j < clients.size(); j++)//must decrement indexes
					{
						clients[j]->fd_index--;
					}
					
				}
				else
				{
					// Check to see if it's a command. \quit kills the server
					if (buf[0] == '\\')
					{
						// Is the command quit? 
						std::string cmd = std::string(buf, bytesIn);
						if (strcmp(cmd.c_str(),"\\quit")==0)
						{
							running = false;
							break;
						}

						// Unknown command
						continue;
					}


					// Send message to other clients, and definiately NOT the listening socket
					OnDataRecieved();
				}
				OnTick();
			}
		}
	}
}

void Server::clean()
{
	// Remove the listening socket from the master file descriptor set and close it
	// to prevent anyone else trying to connect.
	delete clients[0];
	clients.erase(clients.begin());
	FD_CLR(listening_socket, &master);
	closesocket(listening_socket);

	// Message to let users know what's happening.
	std::string msg = "Server is shutting down. Goodbye\r\n";
	int i=0;
	while (master.fd_count> 0)
	{
		// Get the socket number
		SOCKET sock = master.fd_array[0];

		// Send the goodbye message
		send(sock, msg.c_str(), msg.size() + 1, 0);

		// Remove it from the master file list and close the socket
		FD_CLR(sock, &master);
		closesocket(sock);
		delete clients[0];
		clients.erase(clients.begin());
	}
	// Cleanup winsock
	WSACleanup();

	system("pause");
}

//the recieved message is in buf
void Server::OnDataRecieved()
{
	ZeroMemory(bufout, 4096);
	for (int i = 0; i < master.fd_count; i++)
	{
		SOCKET outSock = master.fd_array[i];
		if (outSock != listening_socket)
		{
			std::ostringstream ss;
			memcpy(bufout, buf, sizeof(buf));
			ss << "SOCKET #" << insock << ": " << bufout << "\r\n";
			std::string strOut = ss.str();

			send(outSock, strOut.c_str(), strOut.size() + 1, 0);
		}
	}
}

void Server::OnTick()
{

}


