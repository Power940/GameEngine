#pragma once

#include <vector>
#include "Rect2D.h"
#include "Renderer.h"

bool CheckCollision_NonRotated_RectToRect(
	float point1x, float point1y,
	float size1x, float size1y,
	float point2x, float point2y,
	float size2x, float size2y
);

bool CheckCollision_NonRotated_RectToRect(Rect2D rect1, Rect2D rect2);

bool CheckCollision_NonRotated_RectToRects(
	float point1x, float point1y,
	float point2x, float point2y,
	std::vector<float> point3x, std::vector<float> point3y,
	std::vector<float> point4x, std::vector<float> point4y
);

bool CheckCollision_NonRotated_RectToRects(Rect2D rect1, std::vector<Rect2D> rects);