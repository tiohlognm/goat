#pragma once

#include "object.h"

namespace goat
{
	class g_object_integer_proto : public g_object
	{
	private:
		g_object_integer_proto();

	public:
		static g_object * get_instance();
		std::wstring to_string(g_primitive *pri) const override;
	};

	class g_object_integer : public g_object
	{
	protected:
		g_integer _value;

	public:
		g_object_integer(g_integer value);
		g_object_type type() const override;
		bool less(const g_object *object) const override;
		std::wstring to_string(g_primitive *pri) const override;
		g_object_integer * to_object_integer() const override;
	};
}
