#include "pch.h"

Person::Person()
{

}

Person::Person(double WealthScale, Config*cfg)
{
	this->config = cfg;
	this->cash = DefaultDailyCashIncrement * WealthScale;
	this->GenerateName();
}

Person::~Person()
{

}

void Person::info()
{
	TS::print(name + " " + surname + ":" +config->locale->withcash);
}

void Person::DailyEvents()
{
	this->cash += DefaultDailyCashIncrement * WealthScale;
}

void Person::GenerateName()
{

	int nameid=this->config->names_vec.size();
	int surnameid = this->config->surnames_vec.size();
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist1(0, nameid);
	nameid = dist1(rng);
	std::uniform_int_distribution<std::mt19937::result_type> dist2(0, surnameid);
	nameid = dist1(rng);
	surnameid = dist2(rng);
	this->name = this->config->names_vec[nameid];
	this->surname = this->config->surnames_vec[surnameid];
}