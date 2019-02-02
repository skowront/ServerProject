#include "pch.h"



UserSocket::UserSocket()
{
	UserSocketBase();
}

UserSocket::UserSocket(int _fd_index, const char*_ip, int _id)
{
	fd_index = _fd_index;
	if (_ip != nullptr)
	{
		ip = std::string(_ip);
	}
	id = _id;
	other = nullptr;
}

UserSocket::UserSocket(int _fd_index, int _id)
{
	fd_index = _fd_index;
	id = _id;
	other = nullptr;
}

UserSocket::~UserSocket()
{
	if (other)
	{
		delete other;
	}
	other = nullptr;
}

void UserSocket::UserSocketBase()
{
	fd_index = 0;
	ip = "";
	id = 0;
	username = "";
	password = "";
	authorized = false;
	admin = false;
	access_level = 0;
	other = nullptr;
}