#include "pch.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		Server* server = new Server(54000);
		server->Run();
		delete server;
	}
}
