#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

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

		Rect2D(float px = 0.0f, float py = 0.0f, float sx = 1.0f, float sy = 1.0f, Color c = Color(1.0f, 1.0f, 1.0f), float r = 0.0f) :
			m_p(px, py), m_s(sx, sy), m_c(c), m_r(r) {
			UpdateHalfExtends();
		}
		Rect2D(Vector2 p = (0.0f, 0.0f), Vector2 s = (1.0f, 1.0f), Color c = Color(1.0f, 1.0f, 1.0f), float r = 0.0f) :
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

	struct Triangle2D
	{
		Vector2 m_a;
		Vector2 m_b;
		Vector2 m_c;

		inline Triangle2D(Vector2 a = Vector2(), Vector2 b = Vector2(), Vector2 c = Vector2()) : m_a(a), m_b(b), m_c(c) {}

		inline Vector2 operator[](int element)
		{
			if (element == 0) { return m_a; }
			if (element == 1) { return m_b; }
			if (element == 2) { return m_c; }
		}
	};

	struct Vector3 {
		float x;
		float y;
		float z;

		inline Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
		inline Vector3(Vector3 initialPoint, Vector3 finalPoint):
			x(finalPoint.x - initialPoint.x), y(finalPoint.y - initialPoint.y), z(finalPoint.z - initialPoint.z) {}

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
				m_m[0][0] * vect.x + m_m[0][1] * vect.y + m_m[0][2] * vect.z,
				m_m[1][0] * vect.x + m_m[1][1] * vect.y + m_m[1][2] * vect.z,
				m_m[2][0] * vect.x + m_m[2][1] * vect.y + m_m[2][2] * vect.z
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

	struct Triangle3D
	{
		Vector3 m_a;
		Vector3 m_b;
		Vector3 m_c;

		inline Triangle3D(Vector3 a = Vector3(), Vector3 b = Vector3(), Vector3 c = Vector3()) : m_a(a), m_b(b), m_c(c) {}

		inline Vector3& operator[](int element) { if (element >= 0 && element < 3) { return (&m_a)[element]; } }
		inline const Vector3& operator[](int element) const { if (element >= 0 && element < 3) { return (&m_a)[element]; } }

		inline Vector3 Normal()
		{
			return Vector3(m_b, m_a).Cross(Vector3(m_b, m_c)).Normalize();
		}
	};

	struct Rect3D
	{
	protected:
		float m_halfX; float m_halfY; float m_halfZ;
		Matrix3 m_rm;
		std::vector<Triangle3D> m_Tris;

	public:
		Vector3 m_p;
		Vector3 m_s;
		Vector3 m_r;
		Color m_c;

		Rect3D(float px = 0, float py = 0, float pz = 0, float sx = 1, float sy = 1, float sz = 1, float rx = 0, float ry = 0, float rz = 0, Color c = Color(1.0f, 1.0f, 1.0f)) :
			m_p(px, py, pz), m_s(sx, sy, sz), m_r(rx, ry, rz), m_c(c) {
			UpdateRotationMarix();
			UpdateHalfExtends();
			UpdateTriangles();
		}
		Rect3D(Vector3 p = Vector3(), Vector3 s = (1,1,1), Vector3 r = Vector3(), Color c = Color(1.0f, 1.0f, 1.0f)) :
			m_p(p), m_s(s), m_r(r), m_c(c) {
			UpdateRotationMarix();
			UpdateHalfExtends();
			UpdateTriangles();
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

		inline float MinX() const { return m_p.x - m_halfX; }
		inline float MaxX() const { return m_p.x + m_halfX; }
		inline float MinY() const { return m_p.y - m_halfY; }
		inline float MaxY() const { return m_p.y + m_halfY; }
		inline float MinZ() const { return m_p.z - m_halfZ; }
		inline float MaxZ() const { return m_p.z + m_halfZ; }

		void UpdateRotationMarix()
		{
			m_rm = Matrix3::RotationXYZ(m_r.x, m_r.y, m_r.z);
		}
		void UpdateHalfExtends() {
			Vector3 halfs = m_rm.Abs() * (m_s / 2.0f);

			m_halfX = halfs.x;
			m_halfY = halfs.y;
			m_halfZ = halfs.z;
		}
		void UpdateTriangles()
		{
			Vector3 hs = m_s / 2.0f;

			std::vector<Vector3> p = {
				m_rm * Vector3(m_p.x + hs.x, m_p.y + hs.y, m_p.z + hs.z),
				m_rm * Vector3(m_p.x + hs.x, m_p.y + hs.y, m_p.z - hs.z),
				m_rm * Vector3(m_p.x + hs.x, m_p.y - hs.y, m_p.z + hs.z),
				m_rm * Vector3(m_p.x + hs.x, m_p.y - hs.y, m_p.z - hs.z),
				m_rm * Vector3(m_p.x - hs.x, m_p.y + hs.y, m_p.z + hs.z),
				m_rm * Vector3(m_p.x - hs.x, m_p.y + hs.y, m_p.z - hs.z),
				m_rm * Vector3(m_p.x - hs.x, m_p.y - hs.y, m_p.z + hs.z),
				m_rm * Vector3(m_p.x - hs.x, m_p.y - hs.y, m_p.z - hs.z)
			};
			m_Tris = {
				Triangle3D(p[2], p[0], p[1]),
				Triangle3D(p[1], p[3], p[2]),
				Triangle3D(p[6], p[2], p[3]),
				Triangle3D(p[3], p[7], p[6]),
				Triangle3D(p[4], p[6], p[7]),
				Triangle3D(p[7], p[5], p[4]),
				Triangle3D(p[0], p[4], p[5]),
				Triangle3D(p[5], p[1], p[0]),
				Triangle3D(p[4], p[0], p[2]),
				Triangle3D(p[2], p[6], p[4]),
				Triangle3D(p[5], p[7], p[3]),
				Triangle3D(p[3], p[1], p[5])
			};
		}
		std::vector<Triangle3D> GetTris() const
		{
			return m_Tris;
		}
	};

	struct Camera3D
	{
		Vector3 m_p;
		float m_fov;
		Matrix3 m_r;
		float m_aspect;
		Vector2 m_screenDimension;

		inline Camera3D(Vector3 p, float fov, Vector3 r, Vector2 screenDimension) : m_p(p), m_fov(fov), m_screenDimension(screenDimension), m_aspect(screenDimension.x / screenDimension.y) { m_r = Matrix3::RotationXYZ(r.x, r.y, r.z); }
	};
}