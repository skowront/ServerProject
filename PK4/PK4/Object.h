#pragma once
class Config;
class Object
{
public:
	Object();
	Object(Config*cfg);
	~Object();
	virtual void info();
	virtual void DailyEvents();
	Config*config=nullptr;
private:
};

