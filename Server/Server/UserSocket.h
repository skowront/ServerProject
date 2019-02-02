#pragma once


struct UserSocket
{
	int fd_index;
	std::string ip;
	int id;
	std::string username;
	std::string password;
	bool authorized;
	bool admin;
	int access_level;
	void* other;



	UserSocket();
	UserSocket(int, int);
	UserSocket(int, const char*, int);
	~UserSocket();
	void UserSocketBase();
};