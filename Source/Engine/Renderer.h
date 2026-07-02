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

		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		void Clear();
		void FillRect(Rect2D rect);
		void Present();
		void ShutDown();
	};
}