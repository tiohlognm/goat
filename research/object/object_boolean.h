#pragma once

#include "object.h"

namespace goat
{
	class g_object_boolean_proto : public g_object
	{
	private:
		g_object_boolean_proto();

	public:
		static g_object * get_instance();
		std::wstring to_string(g_primitive *pri) const override;
	};
}
