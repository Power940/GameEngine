#include <vector>

#include "Rect2D.h"


bool CheckCollision_NonRotated_RectToRect(
	float point1x, float point1y,
	float point2x, float point2y,
	float point3x, float point3y,
	float point4x, float point4y)
{
	return (point1x < point4x && point2x > point3x)
		&& (point1y < point4y && point2y > point3y);
}

bool CheckCollision_NonRotated_RectToRect(Rect2D rect1, Rect2D rect2)
{
	return (rect1.X1() < rect2.X2() && rect1.X2() > rect2.X1())
		&& (rect1.Y1() < rect2.Y2() && rect1.Y2() > rect2.Y1());
}

bool CheckCollision_NonRotated_RectToRects(
	float point1x, float point1y,
	float point2x, float point2y,
	std::vector<float> point3x, std::vector<float> point3y,
	std::vector<float> point4x, std::vector<float> point4y)
{
	for (int index = 0; index < point3x.size(); index++)
	{
		if ((point1x < point4x.at(index) && point2x > point3x.at(index))
		 && (point1y < point4y.at(index) && point2y > point3y.at(index)))
		{
			return true;
		}
	}
	return false;
}

bool CheckCollision_NonRotated_RectToRects(Rect2D rect1, std::vector<Rect2D> rects)
{
	for (int index = 0; index < rects.size(); index++)
	{
		if ((rect1.X1() < rects.at(index).X2() && rect1.X2() > rects.at(index).X1())
		 && (rect1.Y1() < rects.at(index).Y2() && rect1.Y2() > rects.at(index).Y1()))
		{
			return true;
		}
	}
	return false;
}