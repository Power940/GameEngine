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

        SDL_SetRenderVSync(m_renderer, 1);

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

    void Renderer::RenderFillTriangle(Triangle2D tri) {
        std::vector<SDL_Vertex> vertices;

        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[0].x, tri[0].y),
            SDL_FColor(m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a),
            SDL_FPoint(0, 0)
        ));
        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[1].x, tri[1].y),
            SDL_FColor(m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a),
            SDL_FPoint(0, 0)
        ));
        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[2].x, tri[2].y),
            SDL_FColor(m_lastSetColor->r, m_lastSetColor->g, m_lastSetColor->b, m_lastSetColor->a),
            SDL_FPoint(0, 0)
        ));

        SDL_RenderGeometry(m_renderer, NULL, vertices.data(), vertices.size(), NULL, 0);
    }
    void Renderer::RenderOutlineTriangle(Triangle2D tri) {

        SDL_RenderLine(m_renderer, tri[0].x, tri[0].y, tri[1].x, tri[1].y);
        SDL_RenderLine(m_renderer, tri[1].x, tri[1].y, tri[2].x, tri[2].y);
        SDL_RenderLine(m_renderer, tri[2].x, tri[2].y, tri[0].x, tri[0].y);
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

    void Renderer::Render3DFillTriangles(Camera3D cam, std::vector<Triangle3D> tris)
    {
        float FOVScaling = 1 / std::tan((cam.m_fov / 2) * STR_FALL::F_DEG_RAD);

        std::vector<Triangle2D> drawTriangles;

        float x1 = 0.0f, x2 = 0.0f, x3 = 0.0f;
        float y1 = 0.0f, y2 = 0.0f, y3 = 0.0f;
        float z1 = 0.0f, z2 = 0.0f, z3 = 0.0f;

        float px1 = 0.0f, py1 = 0.0f;
        float px2 = 0.0f, py2 = 0.0f;
        float px3 = 0.0f, py3 = 0.0f;

        Vector2 screenPos1;
        Vector2 screenPos2;
        Vector2 screenPos3;

        Vector3 pointVector;

        for (const Triangle3D& tri : tris)
        {
            pointVector = Vector3(cam.m_p, tri[0]);
            x1 = pointVector.Dot(cam.m_r.Right());
            y1 = pointVector.Dot(cam.m_r.Up());
            z1 = pointVector.Dot(cam.m_r.Forward());
            pointVector = Vector3(cam.m_p, tri[1]);
            x2 = pointVector.Dot(cam.m_r.Right());
            y2 = pointVector.Dot(cam.m_r.Up());
            z2 = pointVector.Dot(cam.m_r.Forward());
            pointVector = Vector3(cam.m_p, tri[2]);
            x3 = pointVector.Dot(cam.m_r.Right());
            y3 = pointVector.Dot(cam.m_r.Up());
            z3 = pointVector.Dot(cam.m_r.Forward());

            if ((z1 + z2 + z3) / 3.0f < 0.0f) { continue; }

            px1 = x1 / ((z1 < 0.001f) ? -0.01f : z1) * FOVScaling / cam.m_aspect;
            px2 = x2 / ((z2 < 0.001f) ? -0.01f : z2) * FOVScaling / cam.m_aspect;
            px3 = x3 / ((z3 < 0.001f) ? -0.01f : z3) * FOVScaling / cam.m_aspect;
            py1 = y1 / ((z1 < 0.001f) ? -0.01f : z1) * FOVScaling;
            py2 = y2 / ((z2 < 0.001f) ? -0.01f : z2) * FOVScaling;
            py3 = y3 / ((z3 < 0.001f) ? -0.01f : z3) * FOVScaling;

            screenPos1 = Vector2((px1 + 1) * 0.5f * cam.m_screenDimension.x, (1 - py1) * 0.5f * cam.m_screenDimension.y);
            screenPos2 = Vector2((px2 + 1) * 0.5f * cam.m_screenDimension.x, (1 - py2) * 0.5f * cam.m_screenDimension.y);
            screenPos3 = Vector2((px3 + 1) * 0.5f * cam.m_screenDimension.x, (1 - py3) * 0.5f * cam.m_screenDimension.y);

            drawTriangles.push_back(Triangle2D(screenPos1, screenPos2, screenPos3));
        }
        for (const Triangle2D& tri : drawTriangles)
        {
            RenderOutlineTriangle(tri);
        }
    }
}