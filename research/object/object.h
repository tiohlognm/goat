#pragma once

#include "type.h"

#include <map>
#include <vector>
#include <string>

namespace goat
{
	class g_object;
	class g_primitive;

	class g_object_string;
	class g_object_integer;

	class g_object_less
	{
	public:
		inline bool operator() (const g_object *a, const g_object *b) const;
	};

	enum g_object_type
	{
		GENERIC,
		STRING,
		INTEGER
	};

	class g_object
	{
	protected:
		std::map<g_object*, g_primitive, g_object_less> _objects;
		std::vector<g_object*> _proto;

	public:
		virtual ~g_object();
		virtual g_object_type type() const;
		virtual bool less(const g_object *object) const;
		virtual std::wstring to_string(g_primitive *pri) const;

		virtual g_object_string * to_object_string() const;
		virtual g_object_integer * to_object_integer() const;

		void insert(g_object* key, g_primitive value);
		g_primitive * find(g_object* key);
	};

	class g_primitive
	{
	public:
		g_object *object;
		union
		{
			g_integer integer;
		} data;

		std::wstring to_string()
		{
			return object->to_string(this);
		}

		void set(g_integer value);
		static g_primitive create(g_integer value);
	};

	bool g_object_less::operator ()(const g_object *a, const g_object *b) const
	{
		g_object_type x = a->type();
		g_object_type y = b->type();

		if (x == y)
			return a->less(b);

		return x < y;
	}
}
