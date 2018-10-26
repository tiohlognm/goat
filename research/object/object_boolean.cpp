#include "object_boolean.h"

namespace goat
{
	g_object_boolean_proto::g_object_boolean_proto()
	{
	}

	g_object * g_object_boolean_proto::get_instance()
	{
		static g_object_boolean_proto instance;
		return &instance;
	}

	std::wstring g_object_boolean_proto::to_string(g_primitive *pri) const
	{
		return pri->data.boolean ? L"true" : L"false";
	}
}
