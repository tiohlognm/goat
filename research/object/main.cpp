#include "object.h"
#include "object_string.h"
#include "object_integer.h"

#include <iostream>

using namespace goat;

int main(void)
{
	g_object obj0;
	obj0.insert(new g_object_string(L"aaa"), g_primitive::create(1));
	obj0.insert(new g_object_string(L"bb"), g_primitive::create(3));
	obj0.insert(new g_object_integer(17), g_primitive::create(17));
	obj0.insert(new g_object_string(L"cccc"), g_primitive::create(7));
	obj0.insert(new g_object_string(L"ddddd"), g_primitive::create(11));
	obj0.insert(new g_object_integer(19), g_primitive::create(19));
	obj0.insert(new g_object_integer(17), g_primitive::create(22));
	obj0.insert(new g_object_integer(17), g_primitive::create(23));
	obj0.insert(new g_object_string(L"cccc"), g_primitive::create(13));

	auto p = obj0.find(new g_object_string(L"ddddd"));
	if (p)
	{
		std::wcout << p->to_string() << std::endl;
		p->set(111);
	}

	std::wcout << obj0.to_string(nullptr) << std::endl;

	return 0;
}
