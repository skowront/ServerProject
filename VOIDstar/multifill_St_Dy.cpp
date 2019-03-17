// Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//made by TS aka Fanish
#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>



void* DynamicMultifill(void*& src)
{
	void* _ret = (void*)malloc(sizeof(bool));
	void*source;
	size_t sum_count;
	void*dest_mem;
	void*dest_ptr;//the given original
	size_t obj_size;
	source = (void*&)*((char*)src);
	sum_count = *((size_t*)((char*)src + sizeof(void*&)));
	dest_mem = (void*)*((char*)((void*&)*((char*)src + sizeof(void*&) + sizeof(size_t))));
	dest_ptr = ((void*&)*((char*)src + sizeof(void*&) + sizeof(size_t)));
	obj_size = *((size_t*)((char*)src + sizeof(void*&) + sizeof(size_t) + sizeof(void*&)));
	size_t done = 0;
	size_t created = 0;
	size_t left = sum_count;
	if (dest_mem == nullptr)
	{
		dest_mem = (void*)malloc(sum_count * sizeof(void*));
		memcpy(dest_ptr, &dest_mem, sizeof(void*));
	}
	while (left != 0)
	{
		void*val = nullptr;
		size_t count = *(((char*)source) + done * (sizeof(size_t) + obj_size));
		for (size_t i = 0; i < count; i++)
		{
			void *to = ((char*)((void*)(((char*)(dest_mem)) + created * obj_size)));
			val = (void*)malloc(obj_size);
			memcpy(to, &val, obj_size);
			void** from = (void**)(((char*)source) + sizeof(size_t) + done * (sizeof(void*) + sizeof(size_t)));
			void**to_low_ptr = (void**)to;
			memcpy(*to_low_ptr, *from, obj_size);
			created++;
		}
		left = left - count;
		done++;
	}

	return _ret;
}

void* CtDynamicMultifill(void* src, const size_t& sum_count, void* dest, const size_t& obj_size)
{
	void* _ret = (void*)malloc(sizeof(bool));
	void* block = (void*)malloc(sizeof(void*) + sizeof(size_t) + sizeof(void*) + sizeof(size_t));
	memcpy((char*)block, &src, sizeof(void*&));
	memcpy((char*)block + sizeof(void*&), &sum_count, sizeof(size_t));
	memcpy((char*)block + sizeof(void*&) + sizeof(size_t), &dest, sizeof(void*&));
	memcpy((char*)block + sizeof(void*&) + sizeof(size_t) + sizeof(void*&), &obj_size, sizeof(void*&));
	delete DynamicMultifill(block);
	delete block;
	return _ret;
}

void* StaticMultifill(void*& src)
{
	void* _ret = (void*)malloc(sizeof(bool));
	void*source;
	size_t sum_count;
	void*dest_mem;
	void*dest_ptr;//the given original
	size_t obj_size;
	source = (void*&)*((char*)src);
	sum_count = *((size_t*)((char*)src + sizeof(void*&)));
	dest_mem = (void*)*((char*)((void*&)*((char*)src + sizeof(void*&) + sizeof(size_t))));
	dest_ptr = ((void*&)*((char*)src + sizeof(void*&) + sizeof(size_t)));
	obj_size = *((size_t*)((char*)src + sizeof(void*&) + sizeof(size_t) + sizeof(void*&)));
	size_t done = 0;
	size_t created = 0;
	size_t left = sum_count;
	if (dest_mem == nullptr)
	{
		dest_mem = (void*)malloc(sum_count*obj_size);
		memcpy(dest_ptr, &dest_mem, sizeof(void*));
	}
	while (left != 0)
	{
		size_t count = *(((char*)source) + done * (sizeof(size_t) + obj_size));
		for (size_t i = 0; i < count; i++)
		{

			void *to = (void*)(((char*)(dest_mem)) + created * obj_size);
			void *from = (void*)(((char*)source) + sizeof(size_t) + done * (sizeof(void*) + sizeof(size_t)));
			memcpy(to, from, obj_size);
			created++;
		}
		left = left - count;
		done++;
	}
	return _ret;
}

void* CtStaticMultifill(void* src, const size_t& sum_count, void* dest, const size_t& obj_size)
{
	void* _ret = (void*)malloc(sizeof(bool));
	void* block = (void*)malloc(sizeof(void*) + sizeof(size_t) + sizeof(void*) + sizeof(size_t));
	memcpy((char*)block, &src, sizeof(void*&));
	memcpy((char*)block + sizeof(void*&), &sum_count, sizeof(size_t));
	memcpy((char*)block + sizeof(void*&) + sizeof(size_t), &dest, sizeof(void*&));
	memcpy((char*)block + sizeof(void*&) + sizeof(size_t) + sizeof(void*&), &obj_size, sizeof(void*&));
	delete StaticMultifill(block);
	delete block;
	return _ret;
}

//structy mozna sk³adaæ tak albo manualnie do bloku pamiêci :)
struct whateverdynamic
{
	size_t count;//musi byæ size_t
	int *val;//dowolny typ
};

//structy mozna sk³adaæ tak albo manualnie do bloku pamiêci :)
struct whateverstatic
{
	size_t cout;//musibyæ size_t
	int val;//dowolny typ
};


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		whateverdynamic base[3] = { {1,new int},{3,new int},{6,new int} };
		*(base[0].val) = 10;
		*(base[1].val) = 30;
		*(base[2].val) = 60;
		int**out = nullptr;

		delete CtDynamicMultifill(&base, 10, &out, sizeof(int*));

		for (int i = 0; i < 3; i++)
		{
			delete base[i].val;
		}

		for (int i = 0; i < 10; i++)
		{
			std::cout << *out[i] << std::endl;
			delete out[i];
		}
		delete out;
		std::cout << "-----------------------" << std::endl;

		whateverstatic base2[3] = { {1,1}, {2,19},{7,133} };
		int*out2 = nullptr;
		delete CtStaticMultifill((void*)&base2, 10, (void*)&out2, sizeof(int));
		for (int i = 0; i < 10; i++)
		{
			std::cout << out2[i] << std::endl;
		}
		delete out2;
	}
}
