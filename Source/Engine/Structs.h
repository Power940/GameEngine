#pragma once

#include <algorithm>
#include <cmath>

#include "Constants.h"

namespace STR_FALL
{
	struct Color
	{
		float r;
		float g;
		float b;
		float a;

		inline Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
	};

	struct Vector2 {
		float x;
		float y;

		inline Vector2(float x = 0, float y = 0) : x(x), y(y) {}

		inline Vector2 operator+(const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
		inline Vector2 operator-(const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
		inline Vector2 operator*(const Vector2& rhs) const { return Vector2(x * rhs.x, y * rhs.y); }
		inline Vector2 operator/(const Vector2& rhs) const { return Vector2(x / rhs.x, y / rhs.y); }

		inline Vector2 operator+(const float& rhs) const { return Vector2(x + rhs, y + rhs); }
		inline Vector2 operator-(const float& rhs) const { return Vector2(x - rhs, y - rhs); }
		inline Vector2 operator*(const float& rhs) const { return Vector2(x * rhs, y * rhs); }
		inline Vector2 operator/(const float& rhs) const { return Vector2(x / rhs, y / rhs); }

		inline Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
		inline Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
		inline Vector2& operator*=(const Vector2& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
		inline Vector2& operator/=(const Vector2& rhs) { x /= rhs.x; y /= rhs.y; return *this; }

		inline Vector2& operator+=(const float& rhs) { x += rhs; y += rhs; return *this; }
		inline Vector2& operator-=(const float& rhs) { x -= rhs; y -= rhs; return *this; }
		inline Vector2& operator*=(const float& rhs) { x *= rhs; y *= rhs; return *this; }
		inline Vector2& operator/=(const float& rhs) { x /= rhs; y /= rhs; return *this; }

		inline bool operator==(const Vector2& rhs) const { return (x == rhs.x) && (y == rhs.y); }

		inline void Clamp(float min, float max) { x = std::clamp(x, min, max); y = std::clamp(y, min, max); }
		inline void ClampX(float min, float max) { x = std::clamp(x, min, max); }
		inline void ClampY(float min, float max) { y = std::clamp(y, min, max); }

		inline float Magnitude() const { return std::sqrt((x * x) + (y * y)); }
		inline float Dot(Vector2& vect) const { return x * vect.x + y * vect.y; }
		Vector2 Normalize() const
		{
			float mag = this->Magnitude();
			if (mag == 0.0f) { return Vector2(); }
			return Vector2(x / mag, y / mag);
		}
	};

	struct Line
	{
		Vector2 point1;
		Vector2 point2;

		inline Line(Vector2 point1, Vector2 point2) : point1(point1), point2(point2) {}
	};

	struct Vector2C : Vector2 {
		Color c;

		inline Vector2C(float x, float y, Color c) : Vector2(x, y), c(c) {}
	};

	struct LineC : Line
	{
		Color c;

		inline LineC(Vector2 point1, Vector2 point2, Color c) : Line(point1, point2), c(c) {}
	};

	struct Rect2D
	{
	protected:
		float halfX; float halfY;

	public:
		Vector2 m_p;
		Vector2 m_s;
		float m_r;
		Color m_c;

		Rect2D(float px = 0, float py = 0, float sx = 1, float sy = 1, Color c = Color(1.0f, 1.0f, 1.0f), float r = 0) :
			m_p(px, py), m_s(sx, sy), m_c(c), m_r(r) {
			UpdateHalfExtends();
		}
		Rect2D(Vector2 p = (0,0), Vector2 s = (1, 1), Color c = Color(1.0f, 1.0f, 1.0f), float r = 0) :
			m_p(p), m_s(s), m_c(c), m_r(r) {
			UpdateHalfExtends();
		}

		// safe conversions / setter logic options
		float Deg() const { return m_r * F_RAD_DEG; }
		float Rad() const { return fmod(m_r, F_PI2); }
		void Deg(float val) { m_r = fmod(val * F_DEG_RAD, F_PI2); }
		void Rad(float val) { m_r = fmod(val, F_PI2); }

		inline float MinX() const { return m_p.x - halfX; }
		inline float MaxX() const { return m_p.x + halfX; }
		inline float MinY() const { return m_p.y - halfY; }
		inline float MaxY() const { return m_p.y + halfY; }

		void UpdateHalfExtends() {
			float c = std::abs(std::cos(m_r));
			float s = std::abs(std::sin(m_r));

			halfX = c * m_s.x * 0.5f + s * m_s.y * 0.5f;
			halfY = s * m_s.x * 0.5f + c * m_s.y * 0.5f;
		}
	};

	struct Vector3 {
		float x;
		float y;
		float z;

		inline Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

		inline Vector3 operator+(const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
		inline Vector3 operator-(const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
		inline Vector3 operator*(const Vector3& rhs) const { return Vector3(x * rhs.x, y * rhs.y, z * rhs.z); }
		inline Vector3 operator/(const Vector3& rhs) const { return Vector3(x / rhs.x, y / rhs.y, z / rhs.z); }

		inline Vector3 operator+(const float& rhs) const { return Vector3(x + rhs, y + rhs, z + rhs); }
		inline Vector3 operator-(const float& rhs) const { return Vector3(x - rhs, y - rhs, z - rhs); }
		inline Vector3 operator*(const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
		inline Vector3 operator/(const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }

		inline Vector3 operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y, z += rhs.z; return *this; }
		inline Vector3 operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y, z -= rhs.z; return *this; }
		inline Vector3 operator*=(const Vector3& rhs) { x *= rhs.x; y *= rhs.y, z *= rhs.z; return *this; }
		inline Vector3 operator/=(const Vector3& rhs) { x /= rhs.x; y /= rhs.y, z /= rhs.z; return *this; }

		inline Vector3 operator+=(const float& rhs) { x += rhs; y += rhs, z += rhs; return *this; }
		inline Vector3 operator-=(const float& rhs) { x -= rhs; y -= rhs, z -= rhs; return *this; }
		inline Vector3 operator*=(const float& rhs) { x *= rhs; y *= rhs, z *= rhs; return *this; }
		inline Vector3 operator/=(const float& rhs) { x /= rhs; y /= rhs, z /= rhs; return *this; }

		inline bool operator==(const Vector3& rhs) const { return (x == rhs.x) && (y == rhs.y) && (z == rhs.z); }

		inline void Clamp(float min, float max) { x = std::clamp(x, min, max); y = std::clamp(y, min, max); z = std::clamp(z, min, max); }
		inline void ClampX(float min, float max) { x = std::clamp(x, min, max); }
		inline void ClampY(float min, float max) { y = std::clamp(y, min, max); }
		inline void ClampZ(float min, float max) { z = std::clamp(z, min, max); }

		inline float Magnitude() const { return std::sqrt((x * x) + (y * y) + (z * z)); }
		inline float Dot(const Vector3& vect) const { return x * vect.x + y * vect.y + z * vect.z; }
		Vector3 Normalize() const
		{
			float mag = this->Magnitude();
			if (mag == 0.0f) { return Vector3(); }
			return Vector3(x / mag, y / mag, z / mag);
		}
		Vector3 Cross(const Vector3& vect) const
		{
			float crossX = y * vect.z - z * vect.y;
			float crossY = z * vect.x - x * vect.z;
			float crossZ = x * vect.y - y * vect.x;
			return Vector3(crossX, crossY, crossZ);
		}
		float Angle(const Vector3& vect) const
		{
			float dotProduct = Dot(vect);
			float magnitudeProduct = Magnitude() * vect.Magnitude();
			return std::acos(dotProduct / magnitudeProduct);
		}
	};

	struct Matrix3
	{
		float m_m[3][3];

		Matrix3()
		{
			m_m[0][0] = 1; m_m[0][1] = 0; m_m[0][2] = 0;
			m_m[1][0] = 0; m_m[1][1] = 1; m_m[1][2] = 0;
			m_m[2][0] = 0; m_m[2][1] = 0; m_m[2][2] = 1;
		}
		Matrix3(float val)
		{
			m_m[0][0] = val; m_m[0][1] = val; m_m[0][2] = val;
			m_m[1][0] = val; m_m[1][1] = val; m_m[1][2] = val;
			m_m[2][0] = val; m_m[2][1] = val; m_m[2][2] = val;
		}
		Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
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
				m_m[0][0] * vect.x + m_m[0][1] * vect.y + m_m[0][2] * vect.z,
				m_m[1][0] * vect.x + m_m[1][1] * vect.y + m_m[1][2] * vect.z,
				m_m[2][0] * vect.x + m_m[2][1] * vect.y + m_m[2][2] * vect.z
			);
		}

		Matrix3 Abs() const
		{
			return Matrix3(
				std::abs(m_m[0][0]), std::abs(m_m[0][1]), std::abs(m_m[0][2]),
				std::abs(m_m[1][0]), std::abs(m_m[1][1]), std::abs(m_m[1][2]),
				std::abs(m_m[2][0]), std::abs(m_m[2][1]), std::abs(m_m[2][2])
			);
		}

		static Matrix3 RotationX(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);

			return Matrix3
			(
				1,0,0,
				0,c,-s,
				0,s,c
			);
		}
		static Matrix3 RotationY(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);

			return Matrix3
			(
				c,0,s,
				0,1,0,
				-s,0,c
			);
		}
		static Matrix3 RotationZ(float r)
		{
			float c = std::cos(r);
			float s = std::sin(r);

			return Matrix3
			(
				c,-s,0,
				s,c,0,
				0,0,1
			);
		}
		static Matrix3 RotationXYZ(float rx, float ry, float rz)
		{
			return RotationZ(rz) * RotationY(ry) * RotationX(rx);
		}
	};

	struct Rect3D
	{
	protected:
		float halfX; float halfY; float halfZ;

	public:
		Vector3 m_p;
		Vector3 m_s;
		Vector3 m_r;
		Color m_c;

		Rect3D(float px = 0, float py = 0, float pz = 0, float sx = 1, float sy = 1, float sz = 1, float rx = 0, float ry = 0, float rz = 0, Color c = Color(1.0f, 1.0f, 1.0f)) :
			m_p(px, py, pz), m_s(sx, sy, sz), m_r(rx, ry, rz), m_c(c) {
			UpdateHalfExtends();
		}
		Rect3D(Vector3 p = Vector3(), Vector3 s = (1, 1, 1), Vector3 r = Vector3(), Color c = Color(1.0f, 1.0f, 1.0f)) :
			m_p(p), m_s(s), m_r(r), m_c(c) {
			UpdateHalfExtends();
		}

		// safe conversions / setter logic options
		float DegX() const { return m_r.x * F_RAD_DEG; }
		float DegY() const { return m_r.y * F_RAD_DEG; }
		float DegZ() const { return m_r.z * F_RAD_DEG; }
		float RadX() const { return fmod(m_r.x, F_PI2); }
		float RadY() const { return fmod(m_r.y, F_PI2); }
		float RadZ() const { return fmod(m_r.z, F_PI2); }
		void DegX(float val) { m_r.x = fmod(val * F_DEG_RAD, F_PI2); }
		void DegY(float val) { m_r.y = fmod(val * F_DEG_RAD, F_PI2); }
		void DegZ(float val) { m_r.z = fmod(val * F_DEG_RAD, F_PI2); }
		void RadX(float val) { m_r.x = fmod(val, F_PI2); }
		void RadY(float val) { m_r.y = fmod(val, F_PI2); }
		void RadZ(float val) { m_r.z = fmod(val, F_PI2); }

		inline float MinX() const { return m_p.x - halfX; }
		inline float MaxX() const { return m_p.x + halfX; }
		inline float MinY() const { return m_p.y - halfY; }
		inline float MaxY() const { return m_p.y + halfY; }
		inline float MinZ() const { return m_p.z - halfZ; }
		inline float MaxZ() const { return m_p.z + halfZ; }

		void UpdateHalfExtends() {
			Matrix3 r = Matrix3::RotationXYZ(m_r.x, m_r.y, m_r.z).Abs();

			Vector3 halfs = r * (m_s / 2.0f);

			halfX = halfs.x;
			halfY = halfs.y;
			halfZ = halfs.z;
		}
	};
}