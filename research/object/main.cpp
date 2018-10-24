#include "object.h"
#include "object_string.h"

#include <iostream>

using namespace goat;

int main(void)
{
	g_object obj0;
	obj0.insert(new g_object_string(L"aaa"), g_primitive::create(1));
	obj0.insert(new g_object_string(L"bb"), g_primitive::create(3));
	obj0.insert(new g_object_string(L"cccc"), g_primitive::create(7));
	obj0.insert(new g_object_string(L"ddddd"), g_primitive::create(11));
	obj0.insert(new g_object_string(L"cccc"), g_primitive::create(13));

	std::wcout << obj0.to_string(nullptr) << std::endl;
	return 0;
}
