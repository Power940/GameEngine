#pragma once

#include "Structs.h"

class Rect2D
{
protected:
	float halfX; float halfY;

public:
	Vector2 m_p;
	float m_sx; float m_sy;
	float m_r;
	Color m_c;

	Rect2D(float px, float py, float sx, float sy, Color c = Color(1.0f, 1.0f, 1.0f), float r = 0);
	Rect2D(Vector2 p, float sx, float sy, Color c = Color(1.0f, 1.0f, 1.0f), float r = 0);

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