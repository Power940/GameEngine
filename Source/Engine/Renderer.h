#pragma once

#include <SDL3/SDL.h>
#include "Rect2D.h"

namespace nu
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

		void RenderPoint(float x, float y);
		void RenderLine(float x1, float y1, float x2, float y2);
		void RenderRectAABB(Rect2D rect);
		void RenderFillRectAABB(Rect2D rect);
	};
}