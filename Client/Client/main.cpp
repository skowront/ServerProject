#include "pch.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		Client* client = new Client("83.4.79.58", 54000);
		client->Run();
		delete client;
		return 0;
	}
}