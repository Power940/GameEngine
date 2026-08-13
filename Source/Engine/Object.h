#pragma once
#include <string>
#include "Json.h"

namespace STR_FALL
{
	struct Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		bool m_active = true;
		std::string m_name;

		virtual void Read(const rapidjson::Value& value)
		{
			JSON_READ_NAME(value, "name", m_name);
			JSON_READ_NAME(value, "active", m_active);
		}
	};
}