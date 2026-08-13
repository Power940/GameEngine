#pragma once
#include <rapidjson/document.h>
#include <string>
#include "Structs.h"

#define JSON_READ(value, data) STR_FALL::Json::Read(value, #data, data)
#define JSON_READ_NAME(value, name, data) STR_FALL::Json::Read(value, name, data)

namespace STR_FALL::Json
{
	bool Load(const std::string& filename, rapidjson::Document& document);
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data);
	bool Read(const rapidjson::Value& value, const std::string& name, int& data);
	bool Read(const rapidjson::Value& value, const std::string& name, float& data);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string& data);
	bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data);
	bool Read(const rapidjson::Value& value, const std::string& name, Vector3& data);
}
