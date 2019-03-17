#pragma once
#define eif ,true:false;
#define _eif true:false;

#define CFG_PATH "Config\\Config.ini"
#define KURWA "Config\\Locale\\EN\\EN.txt"
enum errors
{
	ConfigLoadError=0,
	ConfigNamesError,
	ConfigSurnamesError,
	LocaleLoadError,
};