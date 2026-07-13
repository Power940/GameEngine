#pragma once
#include <SDL3/SDL.h>
#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "Constants.h"
#include "Structs.h"

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
		Color GetColor();
		void Clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
		void Clear(Color c);
		void ClearF(float r = 0, float g = 0, float b = 0, float a = 1.0f);
        void Present();
		void ShutDown();

		void RenderDebugText(const std::string& text, const Vector2& point) const;

		void RenderPoint(const Vector2& point) const;
		void RenderPoints(const std::vector<Vector2>& points) const;
		void RenderLine(const Line2D& line) const;
		void RenderLines(const std::vector<Line2D>& lines) const;
		void RenderRectAABB(const Rect2D& rect) const;
		void RenderRectsAABB(const std::vector<Rect2D>& rects) const;
		void RenderFillRectAABB(const Rect2D& rect) const;
		void RenderFillRectsAABB(const std::vector<Rect2D>& rects) const;

		void RenderFillTriangle(const Triangle2D& tri) const;
		void RenderOutlineTriangle(const Triangle2D& tri) const;

		void RenderPointColor(const Vector2C& point) const;
		void RenderPointsColor(const std::vector<Vector2C>& points) const;
		void RenderLineColor(const Line2DC& line) const;
		void RenderLinesColor(const std::vector<Line2DC>& lines) const;
		void RenderRectAABBColor(const Rect2D& rect) const;
		void RenderRectsAABBColor(const std::vector<Rect2D>& rects) const;
		void RenderFillRectAABBColor(const Rect2D& rect) const;
		void RenderFillRectsAABBColor(const std::vector<Rect2D>& rects) const;

		void Render3DFillTriangles(const Camera3D& cam, const std::vector<Triangle3D>& tris) const;
	};
}