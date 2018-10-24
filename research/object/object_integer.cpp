#include "object_integer.h"

namespace goat
{
	g_object_integer_proto::g_object_integer_proto()
	{
	}

	g_object * g_object_integer_proto::get_instance()
	{
		static g_object_integer_proto instance;
		return &instance;
	}

	std::wstring g_object_integer_proto::to_string(g_primitive *pri) const
	{
		return std::to_wstring(pri->data.integer);
	}
}
