#include <cmath>

#include "Rect2D.h"
#include "Constants.h"
#include "Structs.h"


Rect2D::Rect2D(float px, float py, float sx, float sy, Color c, float r) : m_p(px, py), m_sx(sx), m_sy(sy), m_c(c), m_r(r) { UpdateHalfExtends(); }
Rect2D::Rect2D(Vector2 p, float sx, float sy, Color c, float r) : m_p(p), m_sx(sx), m_sy(sy), m_c(c), m_r(r) { UpdateHalfExtends(); }

float Rect2D::Deg() const { return m_r * CONST::RAD_DEG; }
float Rect2D::Rad() const { return fmod(m_r,CONST::PI2); }
void Rect2D::Deg(float val) { m_r = fmod(val * CONST::DEG_RAD, CONST::PI2); }
void Rect2D::Rad(float val) { m_r = fmod(val, CONST::PI2); }

float Rect2D::MinX() const { return m_p.x - halfX; }
float Rect2D::MaxX() const { return m_p.x + halfX; }
float Rect2D::MinY() const { return m_p.y - halfY; }
float Rect2D::MaxY() const { return m_p.y + halfY; }

void Rect2D::UpdateHalfExtends()
{
	float c = std::abs(std::cos(m_r));
	float s = std::abs(std::sin(m_r));

	halfX = c * m_sx * 0.5f + s * m_sy * 0.5f;
	halfY = s * m_sx * 0.5f + c * m_sy * 0.5f;
}
