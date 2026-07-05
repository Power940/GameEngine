#include <iostream>

#include "Renderer.h"
#include "Color.h"

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

        m_lastSetColor = new Color(255,255,255);

        return true;
    }
    void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
        m_lastSetColor->m_r = r;
        m_lastSetColor->m_g = g;
        m_lastSetColor->m_b = b;
        m_lastSetColor->m_a = a;
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
        delete m_lastSetColor;
        m_lastSetColor = nullptr;
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
    void Renderer::RenderLine(Line line) { SDL_RenderLine(m_renderer, line.point1.x, line.point1.y, line.point2.x, line.point2.y); }
    void Renderer::RenderLines(std::vector<Line> lines)
    {
        for (const Line line : lines)
        {
            SDL_RenderLine(m_renderer, line.point1.x, line.point1.y, line.point2.x, line.point2.y);
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
        for (const Rect2D& rect : rects)
        {
            SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
            SDL_RenderFillRect(m_renderer, &drawRect);
        }
    }

    void Renderer::RenderPointColor(PointC point)
    {
        SDL_SetRenderDrawColor(m_renderer, point.c.m_r, point.c.m_g, point.c.m_b, point.c.m_a);
        SDL_RenderPoint(m_renderer, point.x, point.y);
        SDL_SetRenderDrawColor(m_renderer, m_lastSetColor->m_r, m_lastSetColor->m_g, m_lastSetColor->m_b, m_lastSetColor->m_a);
    }
    void Renderer::RenderPointsColor(std::vector<PointC> points)
    {
        for (const PointC& point : points)
        {
            SDL_SetRenderDrawColor(m_renderer, point.c.m_r, point.c.m_g, point.c.m_b, point.c.m_a);
            SDL_RenderPoint(m_renderer, point.x, point.y);
        }
        SDL_SetRenderDrawColor(m_renderer, m_lastSetColor->m_r, m_lastSetColor->m_g, m_lastSetColor->m_b, m_lastSetColor->m_a);
    }
    void Renderer::RenderLineColor(LineC line)
    {
        SDL_SetRenderDrawColor(m_renderer, line.c.m_r, line.c.m_g, line.c.m_b, line.c.m_a);
        SDL_RenderLine(m_renderer, line.point1.x, line.point1.y, line.point2.x, line.point2.y);
        SDL_SetRenderDrawColor(m_renderer, m_lastSetColor->m_r, m_lastSetColor->m_g, m_lastSetColor->m_b, m_lastSetColor->m_a);
    }
    void Renderer::RenderLinesColor(std::vector<LineC> lines)
    {
        for (const LineC& line : lines)
        {
            SDL_SetRenderDrawColor(m_renderer, line.c.m_r, line.c.m_g, line.c.m_b, line.c.m_a);
            SDL_RenderLine(m_renderer, line.point1.x, line.point1.y, line.point2.x, line.point2.y);
        }
        SDL_SetRenderDrawColor(m_renderer, m_lastSetColor->m_r, m_lastSetColor->m_g, m_lastSetColor->m_b, m_lastSetColor->m_a);
    }
    void Renderer::RenderRectAABBColor(Rect2D rect)
    {
        SDL_SetRenderDrawColor(m_renderer, rect.m_c.m_r, rect.m_c.m_g, rect.m_c.m_b, rect.m_c.m_a);
        SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
        SDL_RenderRect(m_renderer, &drawRect);
        SDL_SetRenderDrawColor(m_renderer, m_lastSetColor->m_r, m_lastSetColor->m_g, m_lastSetColor->m_b, m_lastSetColor->m_a);
    }
    void Renderer::RenderRectsAABBColor(std::vector<Rect2D> rects)
    {
        for (const Rect2D& rect : rects)
        {
            SDL_SetRenderDrawColor(m_renderer, rect.m_c.m_r, rect.m_c.m_g, rect.m_c.m_b, rect.m_c.m_a);
            SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
            SDL_RenderRect(m_renderer, &drawRect);
        }
        SDL_SetRenderDrawColor(m_renderer, m_lastSetColor->m_r, m_lastSetColor->m_g, m_lastSetColor->m_b, m_lastSetColor->m_a);
    }
    void Renderer::RenderFillRectAABBColor(Rect2D rect)
    {
        SDL_SetRenderDrawColor(m_renderer, rect.m_c.m_r, rect.m_c.m_g, rect.m_c.m_b, rect.m_c.m_a);
        SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
        SDL_RenderFillRect(m_renderer, &drawRect);
        SDL_SetRenderDrawColor(m_renderer, m_lastSetColor->m_r, m_lastSetColor->m_g, m_lastSetColor->m_b, m_lastSetColor->m_a);
    }
    void Renderer::RenderFillRectsAABBColor(std::vector<Rect2D> rects)
    {
        for (const Rect2D& rect : rects)
        {
            SDL_SetRenderDrawColor(m_renderer, rect.m_c.m_r, rect.m_c.m_g, rect.m_c.m_b, rect.m_c.m_a);
            SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
            SDL_RenderFillRect(m_renderer, &drawRect);
        }
        SDL_SetRenderDrawColor(m_renderer, m_lastSetColor->m_r, m_lastSetColor->m_g, m_lastSetColor->m_b, m_lastSetColor->m_a);
    }
}