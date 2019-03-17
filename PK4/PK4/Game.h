#pragma once
class Game
{
public:
	Config*config;
	BOOL<unsigned int> fine;
	int day;
	Game();
	Game(const std::string & configPath);
	~Game();
private:
	void Setup(const std::string & configPath);
	void Run();
};

