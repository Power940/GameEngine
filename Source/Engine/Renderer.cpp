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

        m_lastSetColor = new Color(1.0f, 1.0f, 1.0f);
        m_WINDOW_WIDTH = WINDOW_WIDTH;
        m_WINDOW_HEIGHT = WINDOW_HEIGHT;

        return true;
    }

    void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        m_lastSetColor->m_x = r / 255.0f;
        m_lastSetColor->m_y = g / 255.0f;
        m_lastSetColor->m_z = b / 255.0f;
        m_lastSetColor->m_w = a / 255.0f;
    }
    void Renderer::SetColor(Color c)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, c.m_x, c.m_y, c.m_z, c.m_w);
        m_lastSetColor->m_x = c.m_x;
        m_lastSetColor->m_y = c.m_y;
        m_lastSetColor->m_z = c.m_z;
        m_lastSetColor->m_w = c.m_w;
    }
    void Renderer::SetColorF(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
        m_lastSetColor->m_x = r;
        m_lastSetColor->m_y = g;
        m_lastSetColor->m_z = b;
        m_lastSetColor->m_w = a;
    }

    Color Renderer::GetColor() { return *m_lastSetColor; }

    void Renderer::Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::Clear(Color c)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, c.m_x, c.m_y, c.m_z, c.m_w);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::ClearF(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
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

    void Renderer::RenderDebugText(const std::string& text, const Vector2& point) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, 1.0f, 1.0f, 1.0f, 1.0f);
        SDL_RenderDebugText(m_renderer, point.m_x, point.m_y, text.c_str());
    }

    void Renderer::RenderPoint(const Vector2& point) const { SDL_RenderPoint(m_renderer, point.m_x, point.m_y); }
    void Renderer::RenderPoints(const std::vector<Vector2>& points) const
    {
        for (const Vector2 point : points)
        {
            SDL_RenderPoint(m_renderer, point.m_x, point.m_y);
        }
    }
    void Renderer::RenderLine(const Line2D& line) const { SDL_RenderLine(m_renderer, line.m_1.m_x, line.m_1.m_y, line.m_2.m_x, line.m_2.m_y); }
    void Renderer::RenderLines(const std::vector<Line2D>& lines) const
    {
        for (const Line2D line : lines)
        {
            SDL_RenderLine(m_renderer, line.m_1.m_x, line.m_1.m_y, line.m_2.m_x, line.m_2.m_y);
        }
    }
    void Renderer::RenderFillTriangle(const Triangle2D& tri) const {
        std::vector<SDL_Vertex> vertices;

        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[0].m_x, tri[0].m_y),
            SDL_FColor(m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w),
            SDL_FPoint(0, 0)
        ));
        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[1].m_x, tri[1].m_y),
            SDL_FColor(m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w),
            SDL_FPoint(0, 0)
        ));
        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[2].m_x, tri[2].m_y),
            SDL_FColor(m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w),
            SDL_FPoint(0, 0)
        ));

        SDL_RenderGeometry(m_renderer, nullptr, vertices.data(), 3, nullptr, 0);
    }
    void Renderer::RenderOutlineTriangle(const Triangle2D& tri) const {

        SDL_RenderLine(m_renderer, tri[0].m_x, tri[0].m_y, tri[1].m_x, tri[1].m_y);
        SDL_RenderLine(m_renderer, tri[1].m_x, tri[1].m_y, tri[2].m_x, tri[2].m_y);
        SDL_RenderLine(m_renderer, tri[2].m_x, tri[2].m_y, tri[0].m_x, tri[0].m_y);
    }
    void Renderer::RenderCustomFilled(const std::vector<Vector2>& points, const std::vector<int>& indices) const
    {
        if (points.size() > 1)
        {
            std::vector<SDL_Vertex> vertices;

            for (const Vector2& point : points)
            {
                vertices.push_back(SDL_Vertex(
                    SDL_FPoint(point.m_x, point.m_y),
                    SDL_FColor(m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w),
                    SDL_FPoint(0, 0)
                ));
            }
            SDL_RenderGeometry(m_renderer, nullptr, vertices.data(), static_cast<int>(vertices.size()), indices.data(), static_cast<int>(indices.size()));
        }
    }
    void Renderer::RenderCustomOutline(const std::vector<Vector2>& points) const
    {
        unsigned int size = static_cast<unsigned int>(points.size());
        if (size > 1)
        {
            for (unsigned int index = 0; index < size; index++)
            {
                SDL_RenderLine(m_renderer,
                    points[index].m_x, points[index].m_y,
                    points[(index + 1) % size].m_x, points[(index + 1) % size].m_y
                );
            }
        }
    }

    void Renderer::RenderPointColor(const Vector2C& point) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, point.m_color.m_x, point.m_color.m_y, point.m_color.m_z, point.m_color.m_w);
        SDL_RenderPoint(m_renderer, point.m_x, point.m_y);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::RenderPointsColor(const std::vector<Vector2C>& points) const
    {
        for (const Vector2C& point : points)
        {
            SDL_SetRenderDrawColorFloat(m_renderer, point.m_color.m_x, point.m_color.m_y, point.m_color.m_z, point.m_color.m_w);
            SDL_RenderPoint(m_renderer, point.m_x, point.m_y);
        }
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::RenderLineColor(const Line2DC& line) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, line.m_color.m_x, line.m_color.m_y, line.m_color.m_z, line.m_color.m_w);
        SDL_RenderLine(m_renderer, line.m_1.m_x, line.m_1.m_y, line.m_2.m_x, line.m_2.m_y);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::RenderLinesColor(const std::vector<Line2DC>& lines) const
    {
        for (const Line2DC& line : lines)
        {
            SDL_SetRenderDrawColorFloat(m_renderer, line.m_color.m_x, line.m_color.m_y, line.m_color.m_z, line.m_color.m_w);
            SDL_RenderLine(m_renderer, line.m_1.m_x, line.m_1.m_y, line.m_2.m_x, line.m_2.m_y);
        }
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::RenderFillTriangleColor(const Triangle2DC& tri) const
    {
        std::vector<SDL_Vertex> vertices;

        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[0].m_x, tri[0].m_y),
            SDL_FColor(tri.m_color.m_x, tri.m_color.m_y, tri.m_color.m_z, tri.m_color.m_w),
            SDL_FPoint(0, 0)
        ));
        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[1].m_x, tri[1].m_y),
            SDL_FColor(tri.m_color.m_x, tri.m_color.m_y, tri.m_color.m_z, tri.m_color.m_w),
            SDL_FPoint(0, 0)
        ));
        vertices.push_back(SDL_Vertex(
            SDL_FPoint(tri[2].m_x, tri[2].m_y),
            SDL_FColor(tri.m_color.m_x, tri.m_color.m_y, tri.m_color.m_z, tri.m_color.m_w),
            SDL_FPoint(0, 0)
        ));

        SDL_RenderGeometry(m_renderer, NULL, vertices.data(), 3, NULL, 0);
    }
    void Renderer::RenderOutlineTriangleColor(const Triangle2DC& tri) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, tri.m_color.m_x, tri.m_color.m_y, tri.m_color.m_z, tri.m_color.m_w);
        SDL_RenderLine(m_renderer, tri[0].m_x, tri[0].m_y, tri[1].m_x, tri[1].m_y);
        SDL_RenderLine(m_renderer, tri[1].m_x, tri[1].m_y, tri[2].m_x, tri[2].m_y);
        SDL_RenderLine(m_renderer, tri[2].m_x, tri[2].m_y, tri[0].m_x, tri[0].m_y);
        SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
    }
    void Renderer::RenderCustomFilledColor(const std::vector<Vector2C>& points, const std::vector<int>& indices) const
    {
        if (points.size() > 1)
        {
            std::vector<SDL_Vertex> vertices;

            for (const Vector2C& point : points)
            {
                vertices.push_back(SDL_Vertex(
                    SDL_FPoint(point.m_x, point.m_y),
                    SDL_FColor(point.m_color.m_x, point.m_color.m_y, point.m_color.m_z, point.m_color.m_w),
                    SDL_FPoint(0, 0)
                ));
            }
            SDL_RenderGeometry(m_renderer, nullptr, vertices.data(), static_cast<int>(vertices.size()), indices.data(), static_cast<int>(indices.size()));
        }
    }
    void Renderer::RenderCustomOutlineColor(const std::vector<Vector2C>& points) const
    {
        size_t size = points.size();
        if (size > 1)
        {
            for (size_t index = 0; index < size; index++)
            {
                SDL_SetRenderDrawColorFloat(m_renderer,
                    points[index].m_color.m_x, points[index].m_color.m_y, points[index].m_color.m_z, points[index].m_color.m_w
                );
                SDL_RenderLine(m_renderer,
                    points[index].m_x, points[index].m_y,
                    points[(index + 1) % size].m_x, points[(index + 1) % size].m_y
                );
            }
            SDL_SetRenderDrawColorFloat(m_renderer, m_lastSetColor->m_x, m_lastSetColor->m_y, m_lastSetColor->m_z, m_lastSetColor->m_w);
        }
    }

    void Renderer::Render3DOutlineTriangles(const Camera3D& cam, const std::vector<Triangle3D>& tris) const
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
            pointVector = Vector3(cam.m_transform.m_pos, tri[0]);
            x1 = pointVector.Dot(cam.m_transform.GetRotationMatrix().Right());
            y1 = pointVector.Dot(cam.m_transform.GetRotationMatrix().Up());
            z1 = pointVector.Dot(cam.m_transform.GetRotationMatrix().Forward());
            pointVector = Vector3(cam.m_transform.m_pos, tri[1]);
            x2 = pointVector.Dot(cam.m_transform.GetRotationMatrix().Right());
            y2 = pointVector.Dot(cam.m_transform.GetRotationMatrix().Up());
            z2 = pointVector.Dot(cam.m_transform.GetRotationMatrix().Forward());
            pointVector = Vector3(cam.m_transform.m_pos, tri[2]);
            x3 = pointVector.Dot(cam.m_transform.GetRotationMatrix().Right());
            y3 = pointVector.Dot(cam.m_transform.GetRotationMatrix().Up());
            z3 = pointVector.Dot(cam.m_transform.GetRotationMatrix().Forward());

            if ((z1 + z2 + z3) / 3.0f < 0.0f) { continue; }

            px1 = x1 / ((z1 < 0.001f) ? -0.01f : z1) * FOVScaling / cam.m_aspect;
            px2 = x2 / ((z2 < 0.001f) ? -0.01f : z2) * FOVScaling / cam.m_aspect;
            px3 = x3 / ((z3 < 0.001f) ? -0.01f : z3) * FOVScaling / cam.m_aspect;
            py1 = y1 / ((z1 < 0.001f) ? -0.01f : z1) * FOVScaling;
            py2 = y2 / ((z2 < 0.001f) ? -0.01f : z2) * FOVScaling;
            py3 = y3 / ((z3 < 0.001f) ? -0.01f : z3) * FOVScaling;

            screenPos1 = Vector2((px1 + 1) * 0.5f * cam.m_ScreenDim.m_x, (1 - py1) * 0.5f * cam.m_ScreenDim.m_y);
            screenPos2 = Vector2((px2 + 1) * 0.5f * cam.m_ScreenDim.m_x, (1 - py2) * 0.5f * cam.m_ScreenDim.m_y);
            screenPos3 = Vector2((px3 + 1) * 0.5f * cam.m_ScreenDim.m_x, (1 - py3) * 0.5f * cam.m_ScreenDim.m_y);

            drawTriangles.push_back(Triangle2D(screenPos1, screenPos2, screenPos3));
        }
        for (const Triangle2D& tri : drawTriangles)
        {
            RenderOutlineTriangle(tri);
        }
    }
}