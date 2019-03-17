#include "pch.h"

Game::Game()
{
	Setup(CFG_PATH);
}

Game::Game(const std::string& configPath)
{
	Setup(configPath);
}

Game::~Game()
{
	delete config;
}

void Game::Setup(const std::string &configPath)
{
	this->config ? delete this->config eif;
	try { config = new Config(configPath); }
	catch (...) {
		TS::log("Error ConfigError");
		this->fine = false;
	}
}

