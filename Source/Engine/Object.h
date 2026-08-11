#pragma once
#include <string>

namespace STR_FALL
{
	struct Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		bool m_active = true;
		std::string m_name;
	};
}