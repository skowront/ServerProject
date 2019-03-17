#pragma once
class Game
{
public:
	Config*config;
	BOOL<unsigned int> fine;
	Game();
	Game(const std::string & configPath);
	~Game();
private:
	void Setup(const std::string & configPath);
};

