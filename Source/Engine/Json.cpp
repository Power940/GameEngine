#include "Json.h"
#include "File.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/error/en.h>
#include <iostream>

namespace STR_FALL::Json
{
    bool Load(const std::string& filename, rapidjson::Document& document)
    {
        std::string buffer;
        if (!ReadTextFile(filename, buffer))
        {
            std::cerr << "Could not read file:" << filename << std::endl;
            return false;
        }

        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);
        document.ParseStream(istream);

        if (document.HasParseError())
        {
            std::cerr << "Could not parse JSON: " << filename << std::endl;
            std::cerr << "Error: " << rapidjson::GetParseError_En(document.GetParseError()) << std::endl;

            return false;
        }

        if (!document.IsObject())
        {
            std::cerr << "JSON root is not an object: " << filename << std::endl;
            return false;
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, bool& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
        {
            std::cerr << "Could not read JSON value (bool): " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetBool();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, int& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
        {
            std::cerr << "Could not read JSON value (int): " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetInt();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, float& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsFloat())
        {
            std::cerr << "Could not read JSON value (float): " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetFloat();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, std::string& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
        {
            std::cerr << "Could not read JSON value (string): " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetString();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            std::cerr << "Could not read JSON value (Vector2): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber()) { std::cerr << "Could not read JSON value (Vector2): " << name << std::endl; return false; }
        data.m_x = array[0].GetFloat();
        if (!array[1].IsNumber()) { std::cerr << "Could not read JSON value (Vector2): " << name << std::endl; return false; }
        data.m_y = array[1].GetFloat();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Vector3& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 3)
        {
            std::cerr << "Could not read JSON value (Vector3): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber()) { std::cerr << "Could not read JSON value (Vector3): " << name << std::endl; return false; }
        data.m_x = array[0].GetFloat();
        if (!array[1].IsNumber()) { std::cerr << "Could not read JSON value (Vector3): " << name << std::endl; return false; }
        data.m_y = array[1].GetFloat();
        if (!array[2].IsNumber()) { std::cerr << "Could not read JSON value (Vector3): " << name << std::endl; return false; }
        data.m_z = array[2].GetFloat();

        return true;
    }
}