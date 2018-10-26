#include "object.h"
#include "object_string.h"
#include "object_integer.h"
#include "instruction.h"

#include <iostream>
#include <ctime>

using namespace goat;

int main(void)
{
	g_object_string test_key(L"ddddd");

	g_object obj0;
	obj0.insert(new g_object_string(L"aaa"), g_primitive::create(1));
	obj0.insert(new g_object_string(L"bb"), g_primitive::create(3));
	obj0.insert(new g_object_integer(17), g_primitive::create(17));
	obj0.insert(new g_object_string(L"cccc"), g_primitive::create(7));
	obj0.insert(&test_key, g_primitive::create(11));
	obj0.insert(new g_object_integer(19), g_primitive::create(19));
	obj0.insert(new g_object_integer(17), g_primitive::create(22));
	obj0.insert(new g_object_integer(17), g_primitive::create(23));
	obj0.insert(new g_object_string(L"cccc"), g_primitive::create(13));

	auto p = obj0.find(&test_key);
	if (p)
	{
		std::wcout << p->to_string() << std::endl;
		p->set((g_integer)0);
	}

	std::stack<g_primitive> stack;

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
