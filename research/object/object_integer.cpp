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

	g_primitive g_object_integer_proto::increment(g_primitive *pri) const
	{
		g_primitive result = *pri;
		result.data.integer++;
		return result;
	}

	g_primitive g_object_integer_proto::less(g_primitive *left, g_primitive *right) const
	{
		g_primitive result;
		result.set(left->data.integer < right->data.integer);
		return result;
	}



	g_object_integer::g_object_integer(g_integer value)
		: _value(value)
	{
		_proto.push_back(g_object_integer_proto::get_instance());
	}

	g_object_type g_object_integer::type() const
	{
		return g_object_type::INTEGER;
	}

	bool g_object_integer::less(const g_object *object) const
	{
		g_object_integer * object_integer = object->to_object_integer();

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
