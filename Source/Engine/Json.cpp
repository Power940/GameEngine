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
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
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
    bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            std::cerr << "Could not read JSON value (string vector): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        for (int index = 0; index < value[name.c_str()].Size(); index++)
        {
            data.push_back(array[index].GetString());
        }

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
    bool Read(const rapidjson::Value& value, const std::string& name, Vector4& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            std::cerr << "Could not read JSON value (Vector4): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber()) { std::cerr << "Could not read JSON value (Vector4): " << name << std::endl; return false; }
        data.m_x = array[0].GetFloat();
        if (!array[1].IsNumber()) { std::cerr << "Could not read JSON value (Vector4): " << name << std::endl; return false; }
        data.m_y = array[1].GetFloat();
        if (!array[2].IsNumber()) { std::cerr << "Could not read JSON value (Vector4): " << name << std::endl; return false; }
        data.m_z = array[2].GetFloat();
        if (!array[3].IsNumber()) { std::cerr << "Could not read JSON value (Vector4): " << name << std::endl; return false; }
        data.m_w = array[3].GetFloat();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Matrix2& data)
    {
        if (value.HasMember(name.c_str()) && value[name.c_str()].IsNumber())
        {
            data = Matrix2::RotationXY(value[name.c_str()].GetFloat());
        }
        else if (value.HasMember(name.c_str()) && value[name.c_str()].IsArray() || value[name.c_str()].Size() == 4)
        {
            auto& array = value[name.c_str()];
            data = Matrix2(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat(), array[3].GetFloat());
        }

        std::cerr << "Could not read JSON value (Matrix2): " << name << std::endl;
        return false;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Matrix3& data)
    {
        if (value.HasMember(name.c_str()) && value[name.c_str()].IsNumber())
        {
            data = Matrix3(value[name.c_str()].GetFloat());
        }
        else if (value.HasMember(name.c_str()) && value[name.c_str()].IsArray() || value[name.c_str()].Size() == 3)
        {
            auto& array = value[name.c_str()];
            data = Matrix3::RotationXYZ(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
        }
        else if (value.HasMember(name.c_str()) && value[name.c_str()].IsArray() || value[name.c_str()].Size() == 9)
        {
            auto& array = value[name.c_str()];
            data = Matrix3(
                array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat(),
                array[3].GetFloat(), array[4].GetFloat(), array[5].GetFloat(),
                array[6].GetFloat(), array[7].GetFloat(), array[8].GetFloat()
            );
        }

        std::cerr << "Could not read JSON value (Matrix3): " << name << std::endl;
        return false;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Transform3D& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 9)
        {
            std::cerr << "Could not read JSON value (Transform3D): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber() || !array[1].IsNumber() || !array[2].IsNumber()) { std::cerr << "Could not read JSON value (Transform3D): " << name << std::endl; return false; }
        data.m_pos = Vector3(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
        if (!array[3].IsNumber() || !array[4].IsNumber() || !array[5].IsNumber()) { std::cerr << "Could not read JSON value (Transform3D): " << name << std::endl; return false; }
        data.m_scale = Vector3(array[3].GetFloat(), array[4].GetFloat(), array[5].GetFloat());
        if (!array[6].IsNumber() || !array[7].IsNumber() || !array[8].IsNumber()) { std::cerr << "Could not read JSON value (Transform3D): " << name << std::endl; return false; }
        data.m_rotMat = Matrix3::RotationXYZ(array[6].GetFloat(), array[7].GetFloat(), array[8].GetFloat());

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Camera3D& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 12)
        {
            std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl;
            return false;
        }

        Transform3D t;
        float fov;
        Vector2 sd;

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber() || !array[1].IsNumber() || !array[2].IsNumber()) { std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl; return false; }
        t.m_pos = Vector3(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
        if (!array[3].IsNumber() || !array[4].IsNumber() || !array[5].IsNumber()) { std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl; return false; }
        t.m_scale = Vector3(array[3].GetFloat(), array[4].GetFloat(), array[5].GetFloat());
        if (!array[6].IsNumber() || !array[7].IsNumber() || !array[8].IsNumber()) { std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl; return false; }
        t.m_rotMat = Matrix3::RotationXYZ(array[6].GetFloat(), array[7].GetFloat(), array[8].GetFloat());

        if (!array[9].IsNumber()) { std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl; return false; }
        fov = array[9].GetFloat();

        if (!array[10].IsNumber() || !array[11].IsNumber()) { std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl; return false; }
        sd = Vector2(array[10].GetFloat(), array[11].GetFloat());

        data = Camera3D(t, fov, sd);

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Color& data)
    {
        return false;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, BitMaskInt& data)
    {
        return false;
    }
}