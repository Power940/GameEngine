#include <iostream>

#include "Renderer.h"

namespace nu
{
    bool Renderer::Initialize(const char* name, int WINDOW_WIDTH, int WINDOW_HEIGHT)
    {
        SDL_Init(SDL_INIT_VIDEO);

        m_window = SDL_CreateWindow(name, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        return true;
    }

    void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    void Renderer::Clear()
    {
        SDL_RenderClear(m_renderer);
    }

    void Renderer::FillRect(Rect2D rect)
    {
        SDL_FRect drawRect = { rect.X1(), rect.Y1(), rect.W(), rect.H() };
        SDL_RenderFillRect(m_renderer, &drawRect);
    }

    void Renderer::Present()
    {
        SDL_RenderPresent(m_renderer);
    }

    void Renderer::ShutDown()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
}