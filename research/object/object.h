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

	class g_object
	{
	protected:
		std::map<g_object*, g_primitive, g_object_less> _objects;
		std::vector<g_object*> _proto;

	public:
		virtual ~g_object();
		virtual bool less(const g_object *object) const;
		virtual std::wstring to_string(g_primitive *pri) const;

		virtual g_object_string * to_object_string() const;
		virtual g_object_integer * to_object_integer() const;

		void insert(g_object* key, g_primitive value);
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

		static g_primitive create(g_integer value);
	};

	bool g_object_less::operator ()(const g_object *a, const g_object *b) const
	{
		return a->less(b);
	}
}
