#pragma once
#include "BOOL.h"

BOOL::BOOL()
{
	this->set(false);
}

BOOL::BOOL(bool i)
{
	this->set(i);
}

BOOL::BOOL(bool & i)
{
	this->set(i);
}

//BOOL::BOOL(const bool i)
//{
//	this->set(i);
//}
//
//BOOL::BOOL(const bool & i)
//{
//	this->set(i);
//}

BOOL::BOOL(unsigned int i)
{
	this->set(i);
}

BOOL::BOOL(unsigned int & i)
{
	this->set(i);
}

BOOL::BOOL(bool val, unsigned int i)
{
	this->set(val,i);
}

//BOOL::BOOL(const int i)
//{
//	this->set(i);
//}
//
//BOOL::BOOL(const int & i)
//{
//	this->set(i);
//}


void BOOL::set(bool val, unsigned int ix)
{
	if (ix > (sizeof(unsigned int) * 8) - 1 || ix < 0)
	{
		return;
	}
	unsigned int* tab = new unsigned int[sizeof(unsigned int) * 8];
	for (int i = 0; i < sizeof(int) * 8; i++)
	{
		tab[i] = 0;
	}
	unsigned int temp = this->b;

	for (int i = (sizeof(unsigned int) * 8) - 1; i >= 0; i--)
	{
		tab[i] = temp % 2;
		temp = temp >> 1;
	}
	tab[ix] = val;
	this->b = 0;
	for (int i = 0; i < (sizeof(unsigned int) * 8) ; i++)
	{
		this->b += tab[i];
		i != (sizeof(unsigned int) * 8) - 1 ? this->b = this->b << 1:false;
	}

	delete[]tab;
}

void BOOL::set(bool val)
{
	this->set(val, 0);
}

void BOOL::set(bool tab[], unsigned int count, bool val)
{
	for (int i = 0; i < count; i++)
	{
		this->set(val,tab[i]);
	}
}

bool BOOL::get(unsigned int ix)
{
	if (ix > (sizeof(int) * 8) - 1 || ix < 0)
	{
		return 0;
	}
	unsigned int temp = this->b;
	temp = (temp >> ((sizeof(int) * 8) - ix -1));
	temp = temp % 2;
	return temp;
}

bool BOOL::get()
{
	return this->get(0);
}

BOOL::operator int()
{
	return (int)this->get();
}

BOOL::operator bool()
{
	return this->get();
}

BOOL BOOL::operator[](unsigned int ix)
{
	BOOL ret(this->get(ix),ix);
	return ret;
}

void BOOL::operator=(unsigned int &other)
{
	this->b = other;
	return;
}

void BOOL::operator=(const unsigned int &other)
{
	this->b = other;
	return;
}

void BOOL::operator=(bool &other)
{
	this->b = other;
	return;
}

void BOOL::operator=(const bool &other)
{
	this->b = other;
	return;
}

void BOOL::operator=(BOOL &other)
{
	this->b = other.b;
	return;
}

void BOOL::operator=(const BOOL &other)
{
	this->b = other.b;
	return;
}