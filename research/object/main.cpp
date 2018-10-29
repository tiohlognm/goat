#include "object.h"
#include "object_key.h"
#include "object_string.h"
#include "object_integer.h"
#include "instruction.h"

#include <iostream>
#include <ctime>

using namespace goat;

int main(void)
{
	g_object_key test_key(L"aa");

	g_object obj0;
	obj0.insert(new g_object_key(L"dd0"), g_primitive::create(0));
	obj0.insert(new g_object_key(L"dd1"), g_primitive::create(0));
	obj0.insert(new g_object_key(L"dd2"), g_primitive::create(0));
	obj0.insert(new g_object_key(L"dd3"), g_primitive::create(0));
	obj0.insert(new g_object_key(L"dd4"), g_primitive::create(0));
	obj0.insert(new g_object_key(L"dd5"), g_primitive::create(false));
	obj0.insert(new g_object_key(L"dd6"), g_primitive::create(false));
	obj0.insert(new g_object_key(L"dd7"), g_primitive::create(false));
	obj0.insert(new g_object_key(L"dd8"), g_primitive::create(false));
	obj0.insert(new g_object_key(L"dd9"), g_primitive::create(false));
	obj0.insert(&test_key, g_primitive::create(1));
	/*
	g_object_string test_key(L"aa");

	g_object obj0;
	obj0.insert(new g_object_string(L"dd0"), g_primitive::create(0));
	obj0.insert(new g_object_string(L"dd1"), g_primitive::create(0));
	obj0.insert(new g_object_string(L"dd2"), g_primitive::create(0));
	obj0.insert(new g_object_string(L"dd3"), g_primitive::create(0));
	obj0.insert(new g_object_string(L"dd4"), g_primitive::create(0));
	obj0.insert(new g_object_string(L"dd5"), g_primitive::create(false));
	obj0.insert(new g_object_string(L"dd6"), g_primitive::create(false));
	obj0.insert(new g_object_string(L"dd7"), g_primitive::create(false));
	obj0.insert(new g_object_string(L"dd8"), g_primitive::create(false));
	obj0.insert(new g_object_string(L"dd9"), g_primitive::create(false));
	obj0.insert(&test_key, g_primitive::create(1));
	*/

	auto p = obj0.find(&test_key);
	if (p)
	{
		std::wcout << p->to_string() << std::endl;
		p->set((g_integer)0);
	}

	std::stack<g_primitive, std::vector<g_primitive>> stack;

	g_i_store store;
	store.key = &test_key;

	g_i_increment incr;
	incr.next = &store;

	g_i_load load_1;
	load_1.key = &test_key;
	load_1.next = &incr;

	g_i_if iif;
	iif.if_true = &load_1;

#if 0
	g_i_less less;
	less.next = &iif;

	g_i_load load_0;
	load_0.key = &test_key;
	load_0.next = &less;

	g_i_load_integer load_int;
	load_int.value = 100000000;
	load_int.next = &load_0;

	store.next = &load_int;

	g_instruction *i = &load_1;
#else

	g_i_less_integer ili;
	ili.key = &test_key;
	ili.next = &iif;
	ili.value = 100000000;

	store.next = &ili;

	g_instruction *i = &ili;

#endif

	clock_t x = clock();

	while (i) {
		i = i->exec(&obj0, &stack);
	}

	x = clock() - x;

	std::wcout << ((float)x / CLOCKS_PER_SEC) << " seconds"<< std::endl;
	std::wcout << obj0.to_string(nullptr) << std::endl;

	return 0;
}
