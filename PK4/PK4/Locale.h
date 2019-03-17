#pragma once

class Locale
{
public:
	BOOL <unsigned int> correct;
	Locale(std::string &localeFilePath);
	std::string withcash;
	~Locale();
private:
	void switchOnLine(std::string &line);
};

