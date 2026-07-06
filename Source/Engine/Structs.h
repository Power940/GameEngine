#pragma once

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

	inline Vector2(float x, float y) : x(x), y(y) {}
};

struct Line
{
	Vector2 point1;
	Vector2 point2;

	inline Line(Vector2 point1, Vector2 point2) : point1(point1), point2(point2) {}
};

struct Vector2C: Vector2 {
	Color c;

	inline Vector2C(float x, float y, Color c) : Vector2(x, y), c(c) {}
};

struct LineC: Line
{
	Color c;

	inline LineC(Vector2 point1, Vector2 point2, Color c) : Line(point1, point2), c(c) {}
};