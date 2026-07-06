#include <vector>

#include "Rect2D.h"
bool CheckCollision_NonRotated_RectToRect(Rect2D rect1, Rect2D rect2)
{
	return (rect1.MinX() < rect2.MaxX() && rect1.MaxX() > rect2.MinX())
		&& (rect1.MinY() < rect2.MaxY() && rect1.MaxY() > rect2.MinY());
}
bool CheckCollision_NonRotated_RectToRects(Rect2D rect1, std::vector<Rect2D> rects)
{
	for (int index = 0; index < rects.size(); index++)
	{
		if ((rect1.MinX() < rects.at(index).MaxX() && rect1.MaxX() > rects.at(index).MinX())
		 && (rect1.MinY() < rects.at(index).MaxY() && rect1.MaxY() > rects.at(index).MinY()))
		{
			return true;
		}
	}
	return false;
}