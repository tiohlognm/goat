#pragma once

#include "object.h"

namespace goat
{
	class g_object_key : public g_object
	{
	protected:
		unsigned int _index;

	public:
		g_object_key(std::wstring key);
		g_object_type type() const override;
		bool less(const g_object *object) const override;
		std::wstring to_string(g_primitive *pri) const override;
	};
}
