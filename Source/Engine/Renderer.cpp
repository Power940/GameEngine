#include <iostream>

#include "Renderer.h"

namespace STR_FALL
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

    void Renderer::RenderPoint(Point point) { SDL_RenderPoint(m_renderer, point.x, point.y); }
    void Renderer::RenderPoints(std::vector<Point> points)
    {
        for (const Point point : points)
        {
            SDL_RenderPoint(m_renderer, point.x, point.y);
        }
    }
    void Renderer::RenderLine(Point point1, Point point2) { SDL_RenderLine(m_renderer, point1.x, point1.y, point2.x, point2.y); }
    void Renderer::RenderLines(std::vector<Point> points1, std::vector<Point> points2)
    {
        for (size_t index = 0; index < points1.size(); index++)
        {
            SDL_RenderLine(m_renderer, points1[index].x, points1[index].y, points2[index].x, points2[index].y);
        }
    }
    void Renderer::RenderRectAABB(Rect2D rect)
    {
        SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
        SDL_RenderRect(m_renderer, &drawRect);
    }
    void Renderer::RenderRectsAABB(std::vector<Rect2D> rects)
    {
        for (size_t index = 0; index < rects.size(); index++)
        {
            SDL_FRect drawRect = { rects[index].MinX(), rects[index].MinY(), rects[index].MaxX() - rects[index].MinX(), rects[index].MaxY() - rects[index].MinY() };
            SDL_RenderRect(m_renderer, &drawRect);
        }
    }
    void Renderer::RenderFillRectAABB(Rect2D rect)
    {
        SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
        SDL_RenderFillRect(m_renderer, &drawRect);
    }
    void Renderer::RenderFillRectsAABB(std::vector<Rect2D> rects)
    {
        for (size_t index = 0; index < rects.size(); index++)
        {
            SDL_FRect drawRect = { rects[index].MinX(), rects[index].MinY(), rects[index].MaxX() - rects[index].MinX(), rects[index].MaxY() - rects[index].MinY() };
            SDL_RenderFillRect(m_renderer, &drawRect);
        }
    }
}