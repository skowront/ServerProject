#include "pch.h"

Locale::Locale(std::string &localeFilePath)
{
	std::fstream LocFile(localeFilePath);
	if (!LocFile.good())
	{
		correct = false;
		throw LocaleLoadError;
	}
	else
	{
		std::string line;
		while (std::getline(LocFile, line))
		{
			switchOnLine(line);
		}
		LocFile.close();
	}
}

Locale::~Locale()
{

}

void Locale::switchOnLine(std::string & line)
{
	std::stringstream ss(line);
	std::string part1;
	std::string part2;
	std::string part3;
	ss >> part1;
	if (part1 == "#with_cash")
	{
		while (ss)
		{
			std::string temp;
			ss >> temp;
			this->withcash += temp;
			this->withcash += " ";
		}
	}
}