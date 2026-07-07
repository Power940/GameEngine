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

        m_lastSetColor = new Color(255, 255, 255);

        return true;
    }

    void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        m_lastSetColor->r = r / 255.0f;
        m_lastSetColor->g = g / 255.0f;
        m_lastSetColor->b = b / 255.0f;
        m_lastSetColor->a = a / 255.0f;
    }
    void Renderer::SetColor(Color c)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, c.r, c.g, c.b, c.a);
        m_lastSetColor->r = c.r;
        m_lastSetColor->g = c.g;
        m_lastSetColor->b = c.b;
        m_lastSetColor->a = c.a;
    }
    void Renderer::SetColorF(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
        m_lastSetColor->r = r;
        m_lastSetColor->g = g;
        m_lastSetColor->b = b;
        m_lastSetColor->a = a;
    }

    void Renderer::Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
    }
    void Renderer::Clear(Color c)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, c.r, c.g, c.b, c.a);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
    }
    void Renderer::ClearF(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
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

    void Renderer::RenderPoint(Vector2 point) { SDL_RenderPoint(m_renderer, point.x, point.y); }
    void Renderer::RenderPoints(std::vector<Vector2> points)
    {
        for (const Vector2 point : points)
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

    void Renderer::RenderPointColor(Vector2C point)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, point.c.r, point.c.g, point.c.b, point.c.a);
        SDL_RenderPoint(m_renderer, point.x, point.y);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
    }
    void Renderer::RenderPointsColor(std::vector<Vector2C> points)
    {
        for (const Vector2C& point : points)
        {
            SDL_SetRenderDrawColorFloat(m_renderer, point.c.r, point.c.g, point.c.b, point.c.a);
            SDL_RenderPoint(m_renderer, point.x, point.y);
        }
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
    }
    void Renderer::RenderLineColor(LineC line)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, line.c.r, line.c.g, line.c.b, line.c.a);
        SDL_RenderLine(m_renderer, line.point1.x, line.point1.y, line.point2.x, line.point2.y);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
    }
    void Renderer::RenderLinesColor(std::vector<LineC> lines)
    {
        for (const LineC& line : lines)
        {
            SDL_SetRenderDrawColorFloat(m_renderer, line.c.r, line.c.g, line.c.b, line.c.a);
            SDL_RenderLine(m_renderer, line.point1.x, line.point1.y, line.point2.x, line.point2.y);
        }
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
    }
    void Renderer::RenderRectAABBColor(Rect2D rect)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, rect.m_c.r, rect.m_c.g, rect.m_c.b, rect.m_c.a);
        SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
        SDL_RenderRect(m_renderer, &drawRect);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
    }
    void Renderer::RenderRectsAABBColor(std::vector<Rect2D> rects)
    {
        for (const Rect2D& rect : rects)
        {
            SDL_SetRenderDrawColorFloat(m_renderer, rect.m_c.r, rect.m_c.g, rect.m_c.b, rect.m_c.a);
            SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
            SDL_RenderRect(m_renderer, &drawRect);
        }
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
    }
    void Renderer::RenderFillRectAABBColor(Rect2D rect)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, rect.m_c.r, rect.m_c.g, rect.m_c.b, rect.m_c.a);
        SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
        SDL_RenderFillRect(m_renderer, &drawRect);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
    }
    void Renderer::RenderFillRectsAABBColor(std::vector<Rect2D> rects)
    {
        for (const Rect2D& rect : rects)
        {
            SDL_SetRenderDrawColorFloat(m_renderer, rect.m_c.r, rect.m_c.g, rect.m_c.b, rect.m_c.a);
            SDL_FRect drawRect = { rect.MinX(), rect.MinY(), rect.MaxX() - rect.MinX(), rect.MaxY() - rect.MinY() };
            SDL_RenderFillRect(m_renderer, &drawRect);
        }
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a);
    }
}