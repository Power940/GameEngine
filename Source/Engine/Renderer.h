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
		Color* m_lastSetColor = nullptr;
	public:
        bool Initialize(const char* name, int WINDOW_WIDTH, int WINDOW_HEIGHT);
		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		void SetColor(Color c);
		void SetColorF(float r, float g, float b, float a = 1.0f);
		void Clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
		void Clear(Color c);
		void ClearF(float r = 0, float g = 0, float b = 0, float a = 1.0f);
        void Present();
		void ShutDown();

		void RenderPoint(Vector2 point);
		void RenderPoints(std::vector<Vector2> points);
		void RenderLine(Line line);
		void RenderLines(std::vector<Line> lines);
		void RenderRectAABB(Rect2D rect);
		void RenderRectsAABB(std::vector<Rect2D> rects);
		void RenderFillRectAABB(Rect2D rect);
		void RenderFillRectsAABB(std::vector<Rect2D> rects);

		void RenderPointColor(Vector2C point);
		void RenderPointsColor(std::vector<Vector2C> points);
		void RenderLineColor(LineC line);
		void RenderLinesColor(std::vector<LineC> lines);
		void RenderRectAABBColor(Rect2D rect);
		void RenderRectsAABBColor(std::vector<Rect2D> rects);
		void RenderFillRectAABBColor(Rect2D rect);
		void RenderFillRectsAABBColor(std::vector<Rect2D> rects);
	};
}