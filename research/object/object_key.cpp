#include "object_key.h"

#include <map>
#include <vector>

namespace goat
{
	std::map<std::wstring, unsigned int> __map_keys;
	std::vector<std::wstring> __vector_keys;

	g_object_key::g_object_key(std::wstring key)
	{
		_index = __vector_keys.size();
		auto ret = __map_keys.insert(std::pair<std::wstring, unsigned int>(key, _index));
		if (ret.second == false)
		{
			_index = ret.first->second;
		}
		else
		{
			__vector_keys.push_back(key);
		}
	}

	g_object_type g_object_key::type() const
	{
		return g_object_type::KEY;
	}

	bool g_object_key::less(const g_object *object) const
	{
		g_object_key * object_key = (g_object_key*)object;

		return _index < object_key->_index;
	}

	std::wstring g_object_key::to_string(g_primitive *pri) const
	{
		return __vector_keys[_index];
	}
}
