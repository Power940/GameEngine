#include <SDL3/SDL.h>

#include "Engine.h"

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 1024;

int main()
{
    STR_FALL::Renderer r;
    if (!r.Initialize("testing", WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
        }

        r.Clear();

        r.SetColor(0,255,255);

        r.RenderPoint({ 100,100 });
        r.RenderPoints({ {150,150},{200,200},{250,250},{300,300} });
        r.RenderLine({ 100, 200 }, { 300,400 });
        r.RenderLines({ {100,300},{100,400},{100,500} }, { {300,500},{300,600},{300,700} });
        r.RenderRectAABB( Rect2D(800, 800, 50, 50) );
        r.RenderRectsAABB( { Rect2D(900, 800, 50, 50), Rect2D(900, 900, 50, 50), Rect2D(800, 900, 50, 50) });
        r.RenderFillRectAABB(Rect2D(800, 200, 50, 50));
        r.RenderFillRectsAABB({ Rect2D(900, 200, 50, 50), Rect2D(900, 300, 50, 50), Rect2D(800, 300, 50, 50) });

        r.Present();
    }

    r.ShutDown();

    return 0;
}