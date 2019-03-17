#pragma once
#include "PreDef.h"

class Person:public Object
{
public:
	static const int DefaultDailyCashIncrement=100;
	Person();
	Person(double WealthScale,Config*cfg);
	~Person();
	std::string name;
	std::string surname;
	double WealthScale=1;
	double cash=0;
	int motivation=0;
	//Club*club;//ptr to favourite club
	void info();
	void DailyEvents();
private:
	void GenerateName();
};


