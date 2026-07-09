/*
#include "StarFallEngine.h"

using namespace STR_FALL;

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 1024;

// run these to test to make sure basic rendering works as expected
static void hardcodedNonColorTests(STR_FALL::Renderer& r)
{
    r.SetColor(Color (0,1.0f,1.0f));

    r.RenderPoint(Vector2 (100,100));
    r.RenderPoints({
        Vector2 (150,150),
        Vector2 (200,200),
        Vector2 (250,250),
        Vector2 (300,300)
        });
    r.RenderLine(Line (Vector2 (100,200), Vector2(300,400)));
    r.RenderLines({
        Line (Vector2 (100,300), Vector2 (300,500)),
        Line (Vector2 (100,400), Vector2 (300,600)),
        Line (Vector2 (100,500), Vector2 (300,700))
        });
    r.RenderRectAABB(Rect2D (800,800,50,50));
    r.RenderRectsAABB({
        Rect2D (900,800,50,50),
        Rect2D (900,900,50,50),
        Rect2D (800,900,50,50)
        });
    r.RenderFillRectAABB(Rect2D (800,200,50,50));
    r.RenderFillRectsAABB({
        Rect2D (900,200,50,50),
        Rect2D (900,300,50,50),
        Rect2D (800,300,50,50)
        });
}
static void hardcodedColorTests(STR_FALL::Renderer& r)
{
    r.SetColor(Color (0,1.0f,1.0f));

    r.RenderPointColor(Vector2C (100,100, Color (1.0f, 0.0f, 0.0f)));
    r.RenderPointsColor({
        Vector2C (150,150,Color (1.0f,0.25f,0.0f)),
        Vector2C (200,200,Color (1.0f,0.5f,0.0f)),
        Vector2C (250,250,Color (1.0f,0.75f,0.0f)),
        Vector2C (300,300,Color (1.0f,1.0f,0.0f))
        });
    r.RenderLineColor(LineC (Vector2 (100,200), Vector2 (300,400), Color (1.0f, 0.0f, 0.0f)));
    r.RenderLinesColor({
        LineC (Vector2 (100,300), Vector2 (300,500), Color (1.0f,0.25f,0.0f)),
        LineC (Vector2 (100,400), Vector2 (300,600), Color (1.0f,0.5f,0.0f)),
        LineC (Vector2 (100,500), Vector2 (300,700), Color (1.0f,0.75f,0.0f))
        });
    r.RenderRectAABBColor(Rect2D (800, 800, 50, 50, Color (1.0f, 0.0f, 0.0f)));
    r.RenderRectsAABBColor({
        Rect2D (900,800,50,50, Color (1.0f,0.25f,0.0f)),
        Rect2D (900,900,50,50, Color (1.0f,0.5f,0.0f)),
        Rect2D (800,900,50,50, Color (1.0f,0.75f,0.0f))
        });
    r.RenderFillRectAABBColor(Rect2D (800, 200, 50, 50, Color (1.0f, 0.0f, 0.0f)));
    r.RenderFillRectsAABBColor({
        Rect2D (900,200,50,50, Color (1.0f,0.25f,0.0f)),
        Rect2D (900,300,50,50, Color (1.0f,0.5f,0.0f)),
        Rect2D (800,300,50,50, Color (1.0f,0.75f,0.0f))
        });

    r.RenderFillRectAABB(Rect2D (500,500,50,50));
}

int main()
{
    STR_FALL::Renderer r;
    if (!r.Initialize("testing", WINDOW_WIDTH, WINDOW_HEIGHT)) { return 1; }

    SeedRandom();
    SDL_Event e;
    bool quit = false;

    std::vector<Vector2C> points;
    std::vector<LineC> lines;
    std::vector<Rect2D> rects;

    for (int i = 0; i < 20; i++)
    {
        points.push_back({
            RandomFloat(WINDOW_WIDTH), RandomFloat(WINDOW_HEIGHT),
            Color (RandomFloat(),RandomFloat(),RandomFloat())
            });
    }
    for (int i = 0; i < 10; i++)
    {
        lines.push_back(LineC{
            Vector2 (RandomFloat(WINDOW_WIDTH), RandomFloat(WINDOW_HEIGHT)),
            Vector2 (RandomFloat(WINDOW_WIDTH), RandomFloat(WINDOW_HEIGHT)),
            Color (RandomFloat(),RandomFloat(),RandomFloat())
            });
    }
    for (int i = 0; i < 10; i++)
    {
        rects.push_back(Rect2D(
            Vector2 (RandomFloat(WINDOW_WIDTH), RandomFloat(WINDOW_HEIGHT)),
            Vector2 (RandomFloat(100.0f, 1.0f), RandomFloat(100.0f, 1.0f)),
            Color(RandomFloat(), RandomFloat(), RandomFloat())
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
*/