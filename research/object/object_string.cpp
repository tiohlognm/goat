#include "object_string.h"

namespace goat
{
	g_object_string_proto::g_object_string_proto()
	{
	}

	g_object * g_object_string_proto::get_instance()
	{
		static g_object_string_proto instance;
		return &instance;
	}



	g_object_string::g_object_string(std::wstring value)
		: _value(value)
	{
		_proto.push_back(g_object_string_proto::get_instance());
	}

	bool g_object_string::less(const g_object *object) const
	{
		if (object == this)
		{
			return false;
		}

		g_object_string * object_string = object->to_object_string();

		if (object_string == nullptr)
		{
			return this < object;
		}

		return _value < object_string->_value;
	}

	std::wstring g_object_string::to_string(g_primitive *pri) const
	{
		return _value;
	}

	g_object_string * g_object_string::to_object_string() const
	{
		return (g_object_string *)this;
	}
}
