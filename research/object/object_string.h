#pragma once

#include "object.h"

namespace goat
{
	class g_object_string_proto : public g_object
	{
	private:
		g_object_string_proto();

	public:
		static g_object * get_instance();
	};

	class g_object_string : public g_object
	{
	protected:
		std::wstring _value;

	public:
		g_object_string(std::wstring value);
		bool less(const g_object *object) const override;
		std::wstring to_string(g_primitive *pri) const override;
		g_object_string * to_object_string() const override;
	};
}
