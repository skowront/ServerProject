#include "pch.h"

Config::Config()
{
}

Config::Config(const std::string &configFilePath)
{

	std::fstream CfgFile(configFilePath);
	if (!CfgFile.good())
	{
		correct = false;
	}
	else
	{
		std::string line;
		while (std::getline(CfgFile, line))
		{
			switchOnLine(line);
		}
		CfgFile.close();
	}
	try { locale = new Locale(localization_file_path); }
	catch(...) {
		TS::log("Error LocaleError");
		throw ConfigLoadError;
	}
	try { this->loadNames(names_file_path); }
	catch (...)
	{
		TS::log("Error NamesError");
		throw ConfigLoadError;
	}
	try { this->loadSurnames(surnames_file_path); }
	catch (...)
	{
		TS::log("Error SurnamesError");
		throw ConfigLoadError;
	}
}

Config::~Config()
{
	delete this->locale;
}

void Config::switchOnLine(const std::string & line)
{
	std::stringstream ss(line);
	std::string part1;
	std::string part2;
	std::string part3;
	ss >> part1;
	ss >> part2;
	ss >> part3;
	if (part1 == "#namefile")
	{
		this->names_file_path = part2;
		return;
	}
	if (part1 == "#surnamefile")
	{
		this->surnames_file_path = part2;
		return;
	}
	if (part1 == "#localefile")
	{
		this->localization_file_path = part2;
		return;
	}
	if (part1 == "#clubsfile")
	{
		this->clubs_file_path = part2;
		return;
	}
}

void Config::loadNames(const std::string & filename)
{
	std::fstream CfgFile(filename);
	if (!CfgFile.good())
	{
		correct = false;
		throw ConfigNamesError;
	}
	else
	{
		std::string line;
		while (std::getline(CfgFile, line))
		{
			this->names_vec.push_back(line);
		}
		CfgFile.close();
	}
}

void Config::loadSurnames(const std::string & filename)
{
	std::fstream CfgFile(filename);
	if (!CfgFile.good())
	{
		correct = false;
		throw ConfigSurnamesError;
	}
	else
	{
		std::string line;
		while (std::getline(CfgFile, line))
		{
			this->surnames_vec.push_back(line);
		}
		CfgFile.close();
	}
}

void Config::loadClubs(const std::string & filename)
{
	std::fstream CfgFile(filename);
	if (!CfgFile.good())
	{
		correct = false;
		throw ConfigSurnamesError;
	}
	else
	{
		std::string line;//TODO
		while (std::getline(CfgFile, line))
		{
			Club *club = new Club();
			std::stringstream ss(line);
			std::string part1;
			std::string part2;
			std::string part3;
			ss >> part1;
			if (part1 == "#club")
			{
				
				while (ss)
				{

				}
			}
		}
		CfgFile.close();
	}
}
