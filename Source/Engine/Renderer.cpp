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
    void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }
    void Renderer::Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
        SDL_RenderClear(m_renderer);
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

    void Renderer::RenderPoint(float x, float y)
    {
        SDL_RenderPoint(m_renderer, x, y);
    }
    void Renderer::RenderLine(float x1, float y1, float x2, float y2)
    {
        SDL_RenderLine(m_renderer, x1, y1, x2, y2);
    }
    void Renderer::RenderRectAABB(Rect2D rect)
    {
        SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
        SDL_RenderRect(m_renderer, &drawRect);
    }
    void Renderer::RenderFillRectAABB(Rect2D rect)
    {
        SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
        SDL_RenderFillRect(m_renderer, &drawRect);
    }
}