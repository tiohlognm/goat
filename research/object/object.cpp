#include "object.h"
#include "object_integer.h"

#include <sstream>

namespace goat
{
	g_object::~g_object()
	{
	}

	bool g_object::less(const g_object *object) const
	{
		return this < object;
	}

	std::wstring g_object::to_string(g_primitive *pri) const
	{
		std::wstringstream stream;
		stream << '{';

		int k = 0;
		for (auto pair : _objects)
		{
			if (k)
				stream << ',';
			k++;
			stream << pair.first->to_string(nullptr) << ':' << pair.second.to_string();
		}

		stream << '}';
		return stream.str();
	}

	g_object_string * g_object::to_object_string() const
	{
		return nullptr;
	}

	g_object_integer * g_object::to_object_integer() const
	{
		return nullptr;
	}

	void g_object::insert(g_object* key, g_primitive value)
	{
		_objects[key] = value;
	}



	g_primitive g_primitive::create(g_integer value)
	{
		g_primitive pri;
		pri.object = g_object_integer_proto::get_instance();
		pri.data.integer = value;
		return pri;
	}
}
