#include "pch.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		Client* client = new Client("83.4.217.198", 54000);
		while (!client->Run(1,false))
		{

		}
		bool once = true;
		bool dosend = false;

		//FOREVER
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
				if (userInput=="\\dc")
				{
					break;
				}
				//SEND
				dosend=!(client->SendMsg(userInput));
				dosend = false;
			}
			bool brcv = false;

			//RECIEVE
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