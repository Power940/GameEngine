#include <SDL3/SDL.h>
#include <random>
#include <vector>

#include "Engine.h"

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 1024;


// run these to test to make sure basic rendering works as expected
void hardcodedNonColorTests(STR_FALL::Renderer& r)
{
    r.SetColor(0, 255, 255);
    r.RenderPoint({ 100,100 });
    r.RenderPoints({ {150,150},{200,200},{250,250},{300,300} });
    r.RenderLine({ { 100, 200 }, { 300,400 } });
    r.RenderLines({ {{100,300}, {300,500}}, {{100,400}, {300,600}}, {{100,500}, {300,700}} });
    r.RenderRectAABB(Rect2D(800, 800, 50, 50));
    r.RenderRectsAABB({ Rect2D(900, 800, 50, 50), Rect2D(900, 900, 50, 50), Rect2D(800, 900, 50, 50) });
    r.RenderFillRectAABB(Rect2D(800, 200, 50, 50));
    r.RenderFillRectsAABB({ Rect2D(900, 200, 50, 50), Rect2D(900, 300, 50, 50), Rect2D(800, 300, 50, 50) });
}
void hardcodedColorTests(STR_FALL::Renderer& r)
{
    r.SetColor(0, 255, 255);

    r.RenderPointColor({ 100,100,Color(255,0,0) });
    r.RenderPointsColor({ {150,150,Color(255,50,0)},{200,200,Color(255,100,0)},{250,250,Color(255,150,0)},{300,300,Color(255,200,0)} });
    r.RenderLineColor({ { 100, 200 }, { 300,400 }, Color(255,0,0) });
    r.RenderLinesColor({ {{100,300}, {300,500},Color(255,50,0)}, {{100,400}, {300,600},Color(255,100,0)}, {{100,500}, {300,700},Color(255,150,0)} });
    r.RenderRectAABBColor(Rect2D(800, 800, 50, 50, Color(255, 0, 0)));
    r.RenderRectsAABBColor({ Rect2D(900, 800, 50, 50, Color(255, 50, 0)), Rect2D(900, 900, 50, 50, Color(255, 150, 0)), Rect2D(800, 900, 50, 50, Color(255, 100, 0)) });
    r.RenderFillRectAABBColor(Rect2D(800, 200, 50, 50, Color(255, 0, 0)));
    r.RenderFillRectsAABBColor({ Rect2D(900, 200, 50, 50, Color(255, 50, 0)), Rect2D(900, 300, 50, 50, Color(255, 150, 0)), Rect2D(800, 300, 50, 50, Color(255, 100, 0)) });

    r.RenderFillRectAABB(Rect2D(500, 500, 50, 50));
}


int main()
{
    STR_FALL::Renderer r;
    if (!r.Initialize("testing", WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        return 1;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    SDL_Event e;
    bool quit = false;

    std::vector<PointC> points;
    std::vector<LineC> lines;
    std::vector<Rect2D> rects;


    for (int i = 0; i < 20; i++)
    {
        points.push_back(PointC{
            std::rand() % WINDOW_WIDTH + 1.0f, std::rand() % WINDOW_HEIGHT + 1.0f,
            Color(
                static_cast<uint8_t>(std::rand() % 256),
                static_cast<uint8_t>(std::rand() % 256),
                static_cast<uint8_t>(std::rand() % 256)
            )
            });
    }
    for (int i = 0; i < 10; i++)
    {
        lines.push_back(LineC{
            {std::rand() % WINDOW_WIDTH + 1.0f, std::rand() % WINDOW_HEIGHT + 1.0f},
            {std::rand() % WINDOW_WIDTH + 1.0f, std::rand() % WINDOW_HEIGHT + 1.0f},
            Color(
                static_cast<uint8_t>(std::rand() % 256),
                static_cast<uint8_t>(std::rand() % 256),
                static_cast<uint8_t>(std::rand() % 256)
            )
            });
    }
    for (int i = 0; i < 10; i++)
    {
        rects.push_back(Rect2D(
            std::rand() % WINDOW_WIDTH + 1.0f, std::rand() % WINDOW_HEIGHT + 1.0f,
            std::rand() % 100 + 1.0f, std::rand() % 100 + 1.0f,
            Color(
                static_cast<uint8_t>(std::rand() % 256),
                static_cast<uint8_t>(std::rand() % 256),
                static_cast<uint8_t>(std::rand() % 256)
            )
        ));
    }


    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
        }

        r.Clear();

        r.RenderPointsColor(points);
        r.RenderLinesColor(lines);
        r.RenderFillRectsAABBColor(rects);

        r.Present();
    }

    r.ShutDown();

    return 0;
}