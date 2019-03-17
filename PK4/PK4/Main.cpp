#include "pch.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game *game= new Game(CFG_PATH);
	
	Person* waldek = new Person(1,game->config);
	delete game;
	delete waldek;
	return 0;
}