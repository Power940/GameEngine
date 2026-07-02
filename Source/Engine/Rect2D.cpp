#include "Rect2D.h"

struct Point {
	float x;
	float y;
};

Rect2D::Rect2D(float x1, float y1, float x2, float y2) :
	m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2) {}

Point Rect2D::Point1() const { return { m_x1, m_y1 }; }
Point Rect2D::Point2() const { return { m_x2, m_y2 }; }
float Rect2D::X1() const { return m_x1; }
float Rect2D::Y1() const { return m_y1; }
float Rect2D::X2() const { return m_x2; }
float Rect2D::Y2() const { return m_y2; }
float Rect2D::W() const { return m_x2 - m_x1; }
float Rect2D::H() const { return m_y2 - m_y1; }
void Rect2D::Update(float x1, float y1, float x2, float y2) { m_x1 = x1; m_y1 = y1; m_x2 = x2; m_y2 = y2; }
void Rect2D::X1(float val) { m_x1 = val; }
void Rect2D::Y1(float val) { m_y1 = val; }
void Rect2D::X2(float val) { m_x2 = val; }
void Rect2D::Y2(float val) { m_y2 = val; }
void Rect2D::X(float val)
{
	m_x2 = val + (m_x2 - m_x1);
	m_x1 = val;
}
void Rect2D::Y(float val)
{
	m_y2 = val + (m_y2 - m_y1);
	m_y1 = val;
}