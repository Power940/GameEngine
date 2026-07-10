#pragma once
#include <vector>
#include "Structs.h"

namespace STR_FALL
{
	bool CheckCollision_NonRotated_RectToRect(Rect2D rect1, Rect2D rect2);
	bool CheckCollision_NonRotated_RectToRects(Rect2D rect1, std::vector<Rect2D> rects);
}