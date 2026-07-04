#pragma once

struct Point;

class Rect2D
{
protected:
	float halfX; float halfY;

public:
	float m_px; float m_py;
	float m_sx; float m_sy;
	float m_r;

	Rect2D(float px, float py, float sx, float sy, float r = 0);
	Point Center() const;

	// safe conversions / setter logic options
	float Deg() const;
	float Rad() const;
	void Deg(float val);
	void Rad(float val);

	float MinX() const;
	float MaxX() const;
	float MinY() const;
	float MaxY() const;

	void UpdateHalfExtends();
};