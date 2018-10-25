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



	g_object_integer::g_object_integer(g_integer value)
		: _value(value)
	{
		_proto.push_back(g_object_integer_proto::get_instance());
	}

	bool g_object_integer::less(const g_object *object) const
	{
		if (object == this)
		{
			return false;
		}

		g_object_string * object_string = object->to_object_string();

		if (object_string != nullptr)
		{
			return true;
		}

		g_object_integer * object_integer = object->to_object_integer();

		if (object_integer == nullptr)
		{
			return this < object;
		}

		return _value < object_integer->_value;
	}

	std::wstring g_object_integer::to_string(g_primitive *pri) const
	{
		return std::to_wstring(_value);
	}

	g_object_integer * g_object_integer::to_object_integer() const
	{
		return (g_object_integer *)this;
	}
}
