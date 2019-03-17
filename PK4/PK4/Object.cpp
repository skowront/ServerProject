#include "pch.h"

Object::Object()
{

}

Object::Object(Config*cfg)
{
	this->config = cfg;
}

Object::~Object()
{

}

void Object::info()
{
	TS::print("Unknown");
}

void Object::DailyEvents()
{
	
}
