#include "iostream"

bool CheckCollision_NonRotated_RectToRect(
	float point1x, float point1y,
	float point2x, float point2y,
	float point3x, float point3y,
	float point4x, float point4y)
{
	return (point1x < point4x && point2x > point3x) && (point1y < point4y && point2y > point3y);
}