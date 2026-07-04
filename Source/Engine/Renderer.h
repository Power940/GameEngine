#pragma once

#include <SDL3/SDL.h>
#include <vector>

#include "Structs.h"
#include "Rect2D.h"

namespace STR_FALL
{
	class Renderer
	{
	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
	public:
        bool Initialize(const char* name, int WINDOW_WIDTH, int WINDOW_HEIGHT);
        void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
        void Clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
        void Present();
		void ShutDown();

		void RenderPoint(Point point);
		void RenderPoints(std::vector<Point> points);
		void RenderLine(Point point1, Point point2);
		void RenderLines(std::vector<Point> points1, std::vector<Point> points2);
		void RenderRectAABB(Rect2D rect);
		void RenderRectsAABB(std::vector<Rect2D> rects);
		void RenderFillRectAABB(Rect2D rect);
		void RenderFillRectsAABB(std::vector<Rect2D> rects);
	};
}