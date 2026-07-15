#include "StarFallEngine.h"
#include "Ship.h"

using namespace STR_FALL;

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 1024;
Camera3D cam = Camera3D(Transform3D(), 90, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
Ship player = Ship(Transform2D(Vector2(100, 100), Vector2(75, 75)), Color(), 500.0f, 1000.0f);

int main()
{
    g_engine.Initialize("Testing", WINDOW_WIDTH, WINDOW_HEIGHT);
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
        g_engine.Update();

        player.Update(g_engine.m_time.GetDeltaTime());

        g_engine.m_renderer.Clear();
        player.Draw(g_engine.m_renderer, cam);
        g_engine.m_renderer.Present();
    }

    return 0;
}