#pragma once

class Locale;
class Config
{
public:
	BOOL <unsigned int> correct;
	Config();
	Config(const std::string &configFilePath);
	~Config();
	std::string localization_file_path;
	std::string config_file_path;
	std::string names_file_path;
	std::string	surnames_file_path;
	std::vector <std::string> names_vec;
	std::vector <std::string> surnames_vec;
	Locale*locale=nullptr;
private:
	void switchOnLine(const std::string &line);
	void loadNames(const std::string& filename);
	void loadSurnames(const std::string& filename);
};


