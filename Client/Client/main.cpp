#include "pch.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		Client* client = new Client("83.4.79.58", 54000);
		client->Run();
		bool once = true;
		bool dosend = false;
		while (true)
		{
			std::string userInput;
			if (once)
			{
				std::getline(std::cin, userInput);
				dosend = true;
				once = false;
			}

			if (_kbhit())
			{
				std::getline(std::cin, userInput);
				dosend = true;
			}

			if (userInput.size() > 0)		// Make sure the user has typed in something
			{
				
				dosend=!(client->SendMsg(userInput));
				dosend = false;
			}
			bool brcv = false;
			std::string rcv = client->RecieveMsg(false, brcv, 0);
			if (brcv)
			{
				print(rcv);
				brcv = false;
			}
		}
		delete client;
		return 0;
	}
}