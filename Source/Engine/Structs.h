#pragma once

#include "Color.h"

struct Point {
	float x;
	float y;
};

struct Line
{
	Point point1;
	Point point2;
};

struct PointC {
	float x;
	float y;
	Color c;
};

struct LineC
{
	Point point1;
	Point point2;
	Color c;
};