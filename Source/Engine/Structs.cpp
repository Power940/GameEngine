#include "Structs.h"

using namespace STR_FALL;

inline Vector2::Vector2(const Vector3& vect) : m_x(vect.m_x), m_y(vect.m_y) {}
inline Vector2::Vector2(const Vector4& vect) : m_x(vect.m_x), m_y(vect.m_y) {}
inline Vector3::Vector3(const Vector2& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(0.0f) {}
inline Vector3::Vector3(const Vector4& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(vect.m_z) {}
inline Vector4::Vector4(const Vector2& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(0.0f), m_w(0.0f) {}
inline Vector4::Vector4(const Vector3& vect) : m_x(vect.m_x), m_y(vect.m_y), m_z(vect.m_z), m_w(0.0f) {}

inline Vector2 Vector2::operator*(const Matrix2& rhs) const {
	return Vector2(
		rhs.m_m[0][0] * m_x + rhs.m_m[0][1] * m_y,
		rhs.m_m[1][0] * m_x + rhs.m_m[1][1] * m_y
	);
}
inline Vector2& Vector2::operator*=(const Matrix2& rhs) {
	m_x = rhs.m_m[0][0] * m_x + rhs.m_m[0][1] * m_y;
	m_y = rhs.m_m[1][0] * m_x + rhs.m_m[1][1] * m_y;
	return *this;
}

Vector2 Vector2::Rotate(const float rad) const
{
	return *this * Matrix2::RotationXY(rad);
}