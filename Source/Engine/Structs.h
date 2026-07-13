#pragma once
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cassert>

namespace STR_FALL
{
	struct Vector2;
	struct Vector3;
	struct Vector4;

	struct Vector2
	{
		float m_x;
		float m_y;

		inline Vector2(const float x = 0.0f, const float y = 0.0f) : m_x(x), m_y(y) {}
		inline Vector2(const Vector2& ip, const Vector2& fp) : m_x(fp.m_x - ip.m_x), m_y(fp.m_y - ip.m_y) {}
		inline Vector2(const Vector3& vect);
		inline Vector2(const Vector4& vect);

		float operator[](const unsigned int element) const { assert(element < 2); return (&m_x)[element]; }
		float& operator[](const unsigned int element) { assert(element < 2); return (&m_x)[element]; }

		inline Vector2 operator+(const Vector2& rhs) const { return Vector2(m_x + rhs.m_x, m_y + rhs.m_y); }
		inline Vector2 operator-(const Vector2& rhs) const { return Vector2(m_x - rhs.m_x, m_y - rhs.m_y); }
		inline Vector2 operator*(const Vector2& rhs) const { return Vector2(m_x * rhs.m_x, m_y * rhs.m_y); }
		inline Vector2 operator/(const Vector2& rhs) const { return Vector2(m_x / rhs.m_x, m_y / rhs.m_y); }

		inline Vector2 operator+(const float rhs) const { return Vector2(m_x + rhs, m_y + rhs); }
		inline Vector2 operator-(const float rhs) const { return Vector2(m_x - rhs, m_y - rhs); }
		inline Vector2 operator*(const float rhs) const { return Vector2(m_x * rhs, m_y * rhs); }
		inline Vector2 operator/(const float rhs) const { return Vector2(m_x / rhs, m_y / rhs); }

		inline Vector2& operator+=(const Vector2& rhs) { m_x += rhs.m_x; m_y += rhs.m_y; return *this; }
		inline Vector2& operator-=(const Vector2& rhs) { m_x -= rhs.m_x; m_y -= rhs.m_y; return *this; }
		inline Vector2& operator*=(const Vector2& rhs) { m_x *= rhs.m_x; m_y *= rhs.m_y; return *this; }
		inline Vector2& operator/=(const Vector2& rhs) { m_x /= rhs.m_x; m_y /= rhs.m_y; return *this; }

		inline Vector2& operator+=(const float rhs) { m_x += rhs; m_y += rhs; return *this; }
		inline Vector2& operator-=(const float rhs) { m_x -= rhs; m_y -= rhs; return *this; }
		inline Vector2& operator*=(const float rhs) { m_x *= rhs; m_y *= rhs; return *this; }
		inline Vector2& operator/=(const float rhs) { m_x /= rhs; m_y /= rhs; return *this; }

		inline bool operator==(const Vector2& rhs) const { return (m_x == rhs.m_x) && (m_y == rhs.m_y); }
		inline bool operator!=(const Vector2& rhs) const { return (m_x != rhs.m_x) || (m_y != rhs.m_y); }

		inline void Clamp(const float min, const float max) { m_x = std::clamp(m_x, min, max); m_y = std::clamp(m_y, min, max); }
		inline void ClampX(const float min, const float max) { m_x = std::clamp(m_x, min, max); }
		inline void ClampY(const float min, const float max) { m_y = std::clamp(m_y, min, max); }

		inline float Magnitude() const { return std::sqrt((m_x * m_x) + (m_y * m_y)); }
		inline float Dot(const Vector2& vect) const { return m_x * vect.m_x + m_y * vect.m_y; }
		inline float AngleBetween(const Vector2& vect) const { return std::acos(Dot(vect)); }
		inline float Angle() const { return std::atan2(m_y, m_x); }
		Vector2 Normalize() const
		{
			float mag = this->Magnitude();
			if (mag == 0.0f) { return Vector2(); }
			return *this / mag;
		}
		float Distance(const Vector2& vect) const
		{
			float dx = vect.m_x - m_x;
			float dy = vect.m_y - m_y;
			return std::sqrt(dx * dx + dy * dy);
		}
		Vector2 Lerp(const Vector2& vect, const float t = 0.5f) const
		{
			return *this + (vect - *this) * t;
		}
	};

	struct Vector3
	{
		float m_x;
		float m_y;
		float m_z;

		inline Vector3(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f) : m_x(x), m_y(y), m_z(z) {}
		inline Vector3(const Vector3& ip, const Vector3& fp) : m_x(fp.m_x - ip.m_x), m_y(fp.m_y - ip.m_y), m_z(fp.m_z - ip.m_z) {}
		inline Vector3(const Vector2& vect);
		inline Vector3(const Vector4& vect);

		float operator[](const unsigned int element) const { assert(element < 3); return (&m_x)[element]; }
		float& operator[](const unsigned int element) { assert(element < 3); return (&m_x)[element]; }

		inline Vector3 operator+(const Vector3& rhs) const { return Vector3(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z); }
		inline Vector3 operator-(const Vector3& rhs) const { return Vector3(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z); }
		inline Vector3 operator*(const Vector3& rhs) const { return Vector3(m_x * rhs.m_x, m_y * rhs.m_y, m_z * rhs.m_z); }
		inline Vector3 operator/(const Vector3& rhs) const { return Vector3(m_x / rhs.m_x, m_y / rhs.m_y, m_z / rhs.m_z); }

		inline Vector3 operator+(const float rhs) const { return Vector3(m_x + rhs, m_y + rhs, m_z + rhs); }
		inline Vector3 operator-(const float rhs) const { return Vector3(m_x - rhs, m_y - rhs, m_z - rhs); }
		inline Vector3 operator*(const float rhs) const { return Vector3(m_x * rhs, m_y * rhs, m_z * rhs); }
		inline Vector3 operator/(const float rhs) const { return Vector3(m_x / rhs, m_y / rhs, m_z / rhs); }

		inline Vector3& operator+=(const Vector3& rhs) { m_x += rhs.m_x; m_y += rhs.m_y, m_z += rhs.m_z; return *this; }
		inline Vector3& operator-=(const Vector3& rhs) { m_x -= rhs.m_x; m_y -= rhs.m_y, m_z -= rhs.m_z; return *this; }
		inline Vector3& operator*=(const Vector3& rhs) { m_x *= rhs.m_x; m_y *= rhs.m_y, m_z *= rhs.m_z; return *this; }
		inline Vector3& operator/=(const Vector3& rhs) { m_x /= rhs.m_x; m_y /= rhs.m_y, m_z /= rhs.m_z; return *this; }

		inline Vector3& operator+=(const float rhs) { m_x += rhs; m_y += rhs, m_z += rhs; return *this; }
		inline Vector3& operator-=(const float rhs) { m_x -= rhs; m_y -= rhs, m_z -= rhs; return *this; }
		inline Vector3& operator*=(const float rhs) { m_x *= rhs; m_y *= rhs, m_z *= rhs; return *this; }
		inline Vector3& operator/=(const float rhs) { m_x /= rhs; m_y /= rhs, m_z /= rhs; return *this; }

		inline bool operator==(const Vector3& rhs) const { return (m_x == rhs.m_x) && (m_y == rhs.m_y) && (m_z == rhs.m_z); }
		inline bool operator!=(const Vector3& rhs) const { return (m_x != rhs.m_x) || (m_y != rhs.m_y) || (m_z != rhs.m_z); }

		inline void Clamp(const float min, const float max) { m_x = std::clamp(m_x, min, max); m_y = std::clamp(m_y, min, max); m_z = std::clamp(m_z, min, max); }
		inline void ClampX(const float min, const float max) { m_x = std::clamp(m_x, min, max); }
		inline void ClampY(const float min, const float max) { m_y = std::clamp(m_y, min, max); }
		inline void ClampZ(const float min, const float max) { m_z = std::clamp(m_z, min, max); }

		inline float Magnitude() const { return std::sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z)); }
		inline float Dot(const Vector3& vect) const { return m_x * vect.m_x + m_y * vect.m_y + m_z * vect.m_z; }
		inline float Angle(const Vector3& vect) const { return std::acos(Dot(vect)); }
		Vector3 Normalize() const
		{
			float mag = this->Magnitude();
			if (mag == 0.0f) { return Vector3(); }
			return *this / mag;
		}
		inline Vector3 Cross(const Vector3& vect) const
		{
			return Vector3(
				m_y * vect.m_z - m_z * vect.m_y,
				m_z * vect.m_x - m_x * vect.m_z,
				m_x * vect.m_y - m_y * vect.m_x
			);
		}
		float Distance(const Vector3& vect) const
		{
			float dx = vect.m_x - m_x;
			float dy = vect.m_y - m_y;
			float dz = vect.m_z - m_z;
			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}
		Vector3 Lerp(const Vector3& vect, const float t = 0.5f) const
		{
			return *this + (vect - *this) * t;
		}
	};

	struct Vector4
	{
		float m_x;
		float m_y;
		float m_z;
		float m_w;

		inline Vector4(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float w = 0.0f) : m_x(x), m_y(y), m_z(z), m_w(w) {}
		inline Vector4(const Vector4& ip, const Vector4& fp) : m_x(fp.m_x - ip.m_x), m_y(fp.m_y - ip.m_y), m_z(fp.m_z - ip.m_z), m_w(fp.m_w - ip.m_w) {}
		inline Vector4(const Vector2& vect);
		inline Vector4(const Vector3& vect);

		float operator[](const unsigned int element) const { assert(element < 4); return (&m_x)[element]; }
		float& operator[](const unsigned int element) { assert(element < 4); return (&m_x)[element]; }

		inline Vector4 operator+(const Vector4& rhs) const { return Vector4(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z, m_w + rhs.m_w); }
		inline Vector4 operator-(const Vector4& rhs) const { return Vector4(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z, m_w - rhs.m_w); }
		inline Vector4 operator*(const Vector4& rhs) const { return Vector4(m_x * rhs.m_x, m_y * rhs.m_y, m_z * rhs.m_z, m_w * rhs.m_w); }
		inline Vector4 operator/(const Vector4& rhs) const { return Vector4(m_x / rhs.m_x, m_y / rhs.m_y, m_z / rhs.m_z, m_w / rhs.m_w); }

		inline Vector4 operator+(const float rhs) const { return Vector4(m_x + rhs, m_y + rhs, m_z + rhs, m_w + rhs); }
		inline Vector4 operator-(const float rhs) const { return Vector4(m_x - rhs, m_y - rhs, m_z - rhs, m_w - rhs); }
		inline Vector4 operator*(const float rhs) const { return Vector4(m_x * rhs, m_y * rhs, m_z * rhs, m_w * rhs); }
		inline Vector4 operator/(const float rhs) const { return Vector4(m_x / rhs, m_y / rhs, m_z / rhs, m_w / rhs); }

		inline Vector4& operator+=(const Vector4& rhs) { m_x += rhs.m_x; m_y += rhs.m_y; m_z += rhs.m_z; m_w += rhs.m_w; return *this; }
		inline Vector4& operator-=(const Vector4& rhs) { m_x -= rhs.m_x; m_y -= rhs.m_y; m_z -= rhs.m_z; m_w -= rhs.m_w; return *this; }
		inline Vector4& operator*=(const Vector4& rhs) { m_x *= rhs.m_x; m_y *= rhs.m_y; m_z *= rhs.m_z; m_w *= rhs.m_w; return *this; }
		inline Vector4& operator/=(const Vector4& rhs) { m_x /= rhs.m_x; m_y /= rhs.m_y; m_z /= rhs.m_z; m_w /= rhs.m_w; return *this; }

		inline Vector4& operator+=(const float rhs) { m_x += rhs; m_y += rhs; m_z += rhs; m_w += rhs; return *this; }
		inline Vector4& operator-=(const float rhs) { m_x -= rhs; m_y -= rhs; m_z -= rhs; m_w -= rhs; return *this; }
		inline Vector4& operator*=(const float rhs) { m_x *= rhs; m_y *= rhs; m_z *= rhs; m_w *= rhs; return *this; }
		inline Vector4& operator/=(const float rhs) { m_x /= rhs; m_y /= rhs; m_z /= rhs; m_w /= rhs; return *this; }

		inline bool operator==(const Vector4& rhs) const { return (m_x == rhs.m_x) && (m_y == rhs.m_y) && (m_z == rhs.m_z) && (m_w == rhs.m_w); }
		inline bool operator!=(const Vector4& rhs) const { return (m_x != rhs.m_x) || (m_y != rhs.m_y) || (m_z != rhs.m_z) || (m_w != rhs.m_w); }

		inline void Clamp(const float min, const float max) { m_x = std::clamp(m_x, min, max); m_y = std::clamp(m_y, min, max); m_z = std::clamp(m_z, min, max); m_w = std::clamp(m_w, min, max); }
		inline void ClampX(const float min, const float max) { m_x = std::clamp(m_x, min, max); }
		inline void ClampY(const float min, const float max) { m_y = std::clamp(m_y, min, max); }
		inline void ClampZ(const float min, const float max) { m_z = std::clamp(m_z, min, max); }
		inline void ClampW(const float min, const float max) { m_w = std::clamp(m_w, min, max); }

		inline float Magnitude() const { return std::sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z) + (m_w * m_w)); }
		inline float Dot(const Vector4& vect) const { return m_x * vect.m_x + m_y * vect.m_y + m_z * vect.m_z + m_w * vect.m_w; }
		Vector4 Normalize() const
		{
			float mag = this->Magnitude();
			if (mag == 0.0f) { return Vector4(); }
			return *this / mag;
		}
		float Distance(const Vector4& vect) const
		{
			float dx = vect.m_x - m_x;
			float dy = vect.m_y - m_y;
			float dz = vect.m_z - m_z;
			float dw = vect.m_w - m_w;
			return std::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
		}
		Vector4 Lerp(const Vector4& vect, const float t = 0.5f) const
		{
			return *this + (vect - *this) * t;
		}
	};

	inline Vector2::Vector2(const Vector3& vect) : m_x(vect.m_x), m_y(vect.m_y) {}
	inline Vector2::Vector2(const Vector4& vect) : m_x(vect.m_x), m_y(vect.m_y) {}
	inline Vector3::Vector3(const Vector2& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(0.0f) {}
	inline Vector3::Vector3(const Vector4& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(vect.m_z) {}
	inline Vector4::Vector4(const Vector2& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(0.0f), m_w(0.0f) {}
	inline Vector4::Vector4(const Vector3& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(vect.m_z), m_w(0.0f) {}

	struct Matrix2
	{
		float m_m[2][2];

		inline Matrix2()
		{
			m_m[0][0] = 1; m_m[0][1] = 0;
			m_m[1][0] = 0; m_m[1][1] = 1;
		}
		inline Matrix2(float val)
		{
			m_m[0][0] = val; m_m[0][1] = val;
			m_m[1][0] = val; m_m[1][1] = val;
		}
		inline Matrix2(float m00, float m01, float m10, float m11)
		{
			m_m[0][0] = m00; m_m[0][1] = m01;
			m_m[1][0] = m10; m_m[1][1] = m11;
		}

		inline float* operator[](int element) { return m_m[element]; }
		inline const float* operator[](int element) const { return m_m[element]; }
		inline Matrix2 operator*(const Matrix2& rhs) const
		{
			return Matrix2(
				m_m[0][0] * rhs[0][0] + m_m[0][1] * rhs[1][0], m_m[0][0] * rhs[0][1] + m_m[0][1] * rhs[1][1],
				m_m[1][0] * rhs[0][0] + m_m[1][1] * rhs[1][0], m_m[1][0] * rhs[0][1] + m_m[1][1] * rhs[1][1]
			);
		}
		inline Vector2 operator*(const Vector2& vect) const
		{
			return Vector2(
				m_m[0][0] * vect.m_x + m_m[0][1] * vect.m_y,
				m_m[1][0] * vect.m_x + m_m[1][1] * vect.m_y
			);
		}

		inline Matrix2 Abs() const
		{
			return Matrix2(
				std::abs(m_m[0][0]), std::abs(m_m[0][1]),
				std::abs(m_m[1][0]), std::abs(m_m[1][1])
			);
		}

		inline Vector2 Right() const { return Vector2(m_m[0][0], m_m[1][0]); }
		inline Vector2 Up() const { return Vector2(m_m[0][1], m_m[1][1]); }

		static Matrix2 RotationXY(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);
			return Matrix2
			(
				c, s,
				-s, c
			);
		}
	};

	struct Matrix3
	{
		float m_m[3][3];

		inline Matrix3()
		{
			m_m[0][0] = 1; m_m[0][1] = 0; m_m[0][2] = 0;
			m_m[1][0] = 0; m_m[1][1] = 1; m_m[1][2] = 0;
			m_m[2][0] = 0; m_m[2][1] = 0; m_m[2][2] = 1;
		}
		inline Matrix3(float val)
		{
			m_m[0][0] = val; m_m[0][1] = val; m_m[0][2] = val;
			m_m[1][0] = val; m_m[1][1] = val; m_m[1][2] = val;
			m_m[2][0] = val; m_m[2][1] = val; m_m[2][2] = val;
		}
		inline Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
		{
			m_m[0][0] = m00; m_m[0][1] = m01; m_m[0][2] = m02;
			m_m[1][0] = m10; m_m[1][1] = m11; m_m[1][2] = m12;
			m_m[2][0] = m20; m_m[2][1] = m21; m_m[2][2] = m22;
		}

		inline float* operator[](int element) { return m_m[element]; }
		inline const float* operator[](int element) const { return m_m[element]; }
		inline Matrix3 operator*(const Matrix3& rhs) const
		{
			return Matrix3(
				m_m[0][0] * rhs[0][0] + m_m[0][1] * rhs[1][0] + m_m[0][2] * rhs[2][0], m_m[0][0] * rhs[0][1] + m_m[0][1] * rhs[1][1] + m_m[0][2] * rhs[2][1], m_m[0][0] * rhs[0][2] + m_m[0][1] * rhs[1][2] + m_m[0][2] * rhs[2][2],
				m_m[1][0] * rhs[0][0] + m_m[1][1] * rhs[1][0] + m_m[1][2] * rhs[2][0], m_m[1][0] * rhs[0][1] + m_m[1][1] * rhs[1][1] + m_m[1][2] * rhs[2][1], m_m[1][0] * rhs[0][2] + m_m[1][1] * rhs[1][2] + m_m[1][2] * rhs[2][2],
				m_m[2][0] * rhs[0][0] + m_m[2][1] * rhs[1][0] + m_m[2][2] * rhs[2][0], m_m[2][0] * rhs[0][1] + m_m[2][1] * rhs[1][1] + m_m[2][2] * rhs[2][1], m_m[2][0] * rhs[0][2] + m_m[2][1] * rhs[1][2] + m_m[2][2] * rhs[2][2]
			);
		}
		inline Vector3 operator*(const Vector3& vect) const
		{
			return Vector3(
				m_m[0][0] * vect.m_x + m_m[0][1] * vect.m_y + m_m[0][2] * vect.m_z,
				m_m[1][0] * vect.m_x + m_m[1][1] * vect.m_y + m_m[1][2] * vect.m_z,
				m_m[2][0] * vect.m_x + m_m[2][1] * vect.m_y + m_m[2][2] * vect.m_z
			);
		}

		inline Matrix3 Abs() const
		{
			return Matrix3(
				std::abs(m_m[0][0]), std::abs(m_m[0][1]), std::abs(m_m[0][2]),
				std::abs(m_m[1][0]), std::abs(m_m[1][1]), std::abs(m_m[1][2]),
				std::abs(m_m[2][0]), std::abs(m_m[2][1]), std::abs(m_m[2][2])
			);
		}

		inline Vector3 Right() const { return Vector3(m_m[0][0], m_m[1][0], m_m[2][0]); }
		inline Vector3 Up() const { return Vector3(m_m[0][1], m_m[1][1], m_m[2][1]); }
		inline Vector3 Forward() const { return Vector3(m_m[0][2], m_m[1][2], m_m[2][2]); }

		static Matrix3 RotationX(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);
			return Matrix3
			(
				1, 0, 0,
				0, c, -s,
				0, s, c
			);
		}
		static Matrix3 RotationY(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);
			return Matrix3
			(
				c, 0, s,
				0, 1, 0,
				-s, 0, c
			);
		}
		static Matrix3 RotationZ(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);
			return Matrix3
			(
				c, -s, 0,
				s, c, 0,
				0, 0, 1
			);
		}
		static Matrix3 RotationXYZ(float rx, float ry, float rz)
		{
			float cx = std::cos(rx);
			float sx = std::sin(rx);
			float cy = std::cos(ry);
			float sy = std::sin(ry);
			float cz = std::cos(rz);
			float sz = std::sin(rz);

			return Matrix3(
				cz * cy,
				cz * sy * sx - sz * cx,
				cz * sy * cx + sz * sx,
				sz * cy,
				sz * sy * sx + cz * cx,
				sz * sy * cx - cz * sx,
				-sy,
				cy * sx,
				cy * cx
			);
		}
		static Matrix3 RotationXYZ(const Vector3& r)
		{
			float cx = std::cos(r.m_x);
			float sx = std::sin(r.m_x);
			float cy = std::cos(r.m_y);
			float sy = std::sin(r.m_y);
			float cz = std::cos(r.m_z);
			float sz = std::sin(r.m_z);

			return Matrix3(
				cz * cy,
				cz * sy * sx - sz * cx,
				cz * sy * cx + sz * sx,
				sz * cy,
				sz * sy * sx + cz * cx,
				sz * sy * cx - cz * sx,
				-sy,
				cy * sx,
				cy * cx
			);
		}
	};

	struct Matrix4
	{

	};

	struct Triangle2D
	{
		Vector2 m_a;
		Vector2 m_b;
		Vector2 m_c;

		inline Triangle2D(const Vector2& a = Vector2(), const Vector2& b = Vector2(), const Vector2& c = Vector2()) : m_a(a), m_b(b), m_c(c) {}

		inline Vector2& operator[](int element)
		{
			if (element == 0) { return m_a; }
			if (element == 1) { return m_b; }
			if (element == 2) { return m_c; }
			return m_a;
		}
		const inline Vector2& operator[](int element) const
		{
			if (element == 0) { return m_a; }
			if (element == 1) { return m_b; }
			if (element == 2) { return m_c; }
			return m_a;
		}
	};

	struct Triangle3D
	{
		Vector3 m_a;
		Vector3 m_b;
		Vector3 m_c;

		inline Triangle3D(const Vector3& a = Vector3(), const Vector3& b = Vector3(), const Vector3& c = Vector3()) : m_a(a), m_b(b), m_c(c) {}

		inline Vector3& operator[](int element)
		{
			if (element == 0) { return m_a; }
			if (element == 1) { return m_b; }
			if (element == 2) { return m_c; }
			return m_a;
		}
		const inline Vector3& operator[](int element) const
		{
			if (element == 0) { return m_a; }
			if (element == 1) { return m_b; }
			if (element == 2) { return m_c; }
			return m_a;
		}

		inline Vector3 Normal() const
		{
			return Vector3(m_b, m_a).Cross(Vector3(m_b, m_c)).Normalize();
		}
	};

	struct Transform2D
	{
	protected:
		Matrix2 m_rotMat;
	public:
		Vector2 m_pos;
		Vector2 m_scale;
		float m_rot;

		inline Transform2D(const Vector2& pos = Vector2(), const Vector2& scale = Vector2(1.0f, 1.0f), const float rot = 0) :
			m_pos(pos), m_scale(scale), m_rot(rot), m_rotMat(Matrix2::RotationXY(rot)) {
		}

		inline void SetRotation(const float rot)
		{
			if (m_rot != rot)
			{
				m_rot = rot;
				m_rotMat = Matrix2::RotationXY(rot);
			}
		}

		inline Matrix2 GetRotationMatrix()
		{
			return m_rotMat;
		}
	};

	struct Transform3D
	{
	protected:
		Matrix3 m_rotMat;
	public:
		Vector3 m_pos;
		Vector3 m_scale;
		Vector3 m_rot;

		inline Transform3D(const Vector3& pos = Vector3(), const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f), const Vector3& rot = Vector3()) :
			m_pos(pos), m_scale(scale), m_rot(rot), m_rotMat(Matrix3::RotationXYZ(rot)) {
		}

		inline void SetRotation(const Vector3& rot)
		{
			if (m_rot != rot)
			{
				m_rot = rot;
				m_rotMat = Matrix3::RotationXYZ(rot);
			}
		}
		inline void SetRotationX(const float& rot)
		{
			Vector3 prev = m_rot;
			m_rot.m_x = rot;
			if (prev != m_rot)
			{
				m_rotMat = Matrix3::RotationXYZ(rot);
			}
		}
		inline void SetRotationY(const float& rot)
		{
			Vector3 prev = m_rot;
			m_rot.m_y = rot;
			if (prev != m_rot)
			{
				m_rotMat = Matrix3::RotationXYZ(rot);
			}
		}
		inline void SetRotationZ(const float& rot)
		{
			Vector3 prev = m_rot;
			m_rot.m_z = rot;
			if (prev != m_rot)
			{
				m_rotMat = Matrix3::RotationXYZ(rot);
			}
		}

		inline Matrix3 GetRotationMatrix() const
		{
			return m_rotMat;
		}
	};

	struct Camera3D
	{
		Transform3D m_transform;
		Matrix3 m_rotMat;
		float m_fov;
		Vector2 m_ScreenDim;
		float m_aspect;

		inline Camera3D(const Transform3D& t, const float fov, const Vector2& screenDim) :
			m_transform(t), m_fov(fov), m_ScreenDim(screenDim), m_aspect(screenDim.m_x / screenDim.m_y), m_rotMat(Matrix3::RotationXYZ(t.m_rot)) {
		}
	};

	struct Color
	{
		Vector4 m_color;

		inline Color(const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f) : m_color(r, g, b, a) {}
	};

	struct Vector2C : Vector2 {
		Color m_color;

		inline Vector2C(float x, float y, const Color& color) : Vector2(x, y), m_color(color) {}
		inline Vector2C(const Vector2& p, const Color& color) : Vector2(p.m_x, p.m_x), m_color(color) {}
	};

	struct Line2D
	{
		Vector2 m_1;
		Vector2 m_2;

		inline Line2D(const Vector2& p1, const Vector2& p2) : m_1(p1), m_2(p2) {}
	};

	struct Line2DC : Line2D
	{
		Color m_color;

		inline Line2DC(const Vector2& p1, const Vector2& p2, const Color& color) : Line2D(p1, p2), m_color(color) {}
	};
}