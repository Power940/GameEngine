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

		inline Vector2 operator+(const Vector2& rhs) { return Vector2(x + rhs.x, y + rhs.y); }
		inline Vector2 operator-(const Vector2& rhs) { return Vector2(x - rhs.x, y - rhs.y); }
		inline Vector2 operator*(const Vector2& rhs) { return Vector2(x * rhs.x, y * rhs.y); }
		inline Vector2 operator/(const Vector2& rhs) { return Vector2(x / rhs.x, y / rhs.y); }

		inline Vector2 operator+(const float& rhs) { return Vector2(x + rhs, y + rhs); }
		inline Vector2 operator-(const float& rhs) { return Vector2(x - rhs, y - rhs); }
		inline Vector2 operator*(const float& rhs) { return Vector2(x * rhs, y * rhs); }
		inline Vector2 operator/(const float& rhs) { return Vector2(x / rhs, y / rhs); }

		inline Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
		inline Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
		inline Vector2& operator*=(const Vector2& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
		inline Vector2& operator/=(const Vector2& rhs) { x /= rhs.x; y /= rhs.y; return *this; }

		inline Vector2& operator+=(const float& rhs) { x += rhs; y += rhs; return *this; }
		inline Vector2& operator-=(const float& rhs) { x -= rhs; y -= rhs; return *this; }
		inline Vector2& operator*=(const float& rhs) { x *= rhs; y *= rhs; return *this; }
		inline Vector2& operator/=(const float& rhs) { x /= rhs; y /= rhs; return *this; }

		inline void Clamp(float min, float max) { x = std::clamp(x, min, max); y = std::clamp(y, min, max); }
		inline void ClampX(float min, float max) { x = std::clamp(x, min, max); }
		inline void ClampY(float min, float max) { y = std::clamp(y, min, max); }

		inline float const Dot(Vector2& vect1, Vector2& vect2) { return vect1.x * vect2.x + vect1.y * vect2.y; }
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
		float m_sx; float m_sy;
		float m_r;
		Color m_c;

		Rect2D(float px, float py, float sx, float sy, Color c = Color(1.0f, 1.0f, 1.0f), float r = 0) :
			m_p(px, py), m_sx(sx), m_sy(sy), m_c(c), m_r(r) {
			UpdateHalfExtends();
		}
		Rect2D(Vector2 p, float sx, float sy, Color c = Color(1.0f, 1.0f, 1.0f), float r = 0) :
			m_p(p), m_sx(sx), m_sy(sy), m_c(c), m_r(r) {
			UpdateHalfExtends();
		}

		// safe conversions / setter logic options
		float Deg() const { return m_r * (float)RAD_DEG; }
		float Rad() const { return fmod(m_r, (float)PI2); }
		void Deg(float val) { m_r = fmod(val * (float)DEG_RAD, (float)PI2); }
		void Rad(float val) { m_r = fmod(val, (float)PI2); }

		inline float MinX() const { return m_p.x - halfX; }
		inline float MaxX() const { return m_p.x + halfX; }
		inline float MinY() const { return m_p.y - halfY; }
		inline float MaxY() const { return m_p.y + halfY; }

		void UpdateHalfExtends() {
			float c = std::abs(std::cos(m_r));
			float s = std::abs(std::sin(m_r));

			halfX = c * m_sx * 0.5f + s * m_sy * 0.5f;
			halfY = s * m_sx * 0.5f + c * m_sy * 0.5f;
		}
	};
}