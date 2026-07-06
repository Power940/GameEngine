/*
#include <set>
#include <algorithm>

#include "Engine.h"
#include "Rect2D.h"
#include <Renderer.h>

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 1024;

int main()
{
    STR_FALL::Renderer r;
    if (!r.Initialize("testing", WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        return 1;
    }

    SDL_Event event;
    bool quit = false;

    Rect2D player = Rect2D(500, 500, 50, 50, Color(0,0,255));
    Rect2D block = Rect2D(200, 200, 50, 200, Color(255,0,0));

    std::set<Uint32> heldKeys;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                heldKeys.insert(event.key.key);
            }
            else if (event.type == SDL_EVENT_KEY_UP)
            {
                heldKeys.erase(event.key.key);
            }
        }

        float dX = (heldKeys.contains(SDLK_D) - heldKeys.contains(SDLK_A)) * (heldKeys.contains(SDLK_LSHIFT) ? 2 : 1) * 0.1f;
        float dY = (heldKeys.contains(SDLK_S) - heldKeys.contains(SDLK_W)) * (heldKeys.contains(SDLK_LSHIFT) ? 2 : 1) * 0.1f;
        float newX = std::clamp(player.m_px + dX, player.m_sx / 2.0f, static_cast<float>(WINDOW_WIDTH) - player.m_sx / 2.0f);
        float newY = std::clamp(player.m_py + dY, player.m_sy / 2.0f, static_cast<float>(WINDOW_HEIGHT) - player.m_sy / 2.0f);

        if (!CheckCollision_NonRotated_RectToRect( Rect2D (newX, newY, player.m_sx, player.m_sy), block))
        {
            player.m_px = newX;
            player.m_py = newY;
        }
        else if (!CheckCollision_NonRotated_RectToRect( Rect2D (player.m_px, newY, player.m_sx, player.m_sy), block))
        {
            player.m_py = newY;
        }
        else if (!CheckCollision_NonRotated_RectToRect( Rect2D (newX, player.m_py, player.m_sx, player.m_sy), block))
        {
            player.m_px = newX;
        }

        r.Clear();

        r.RenderFillRectsAABBColor({ player, block });

        r.Present();
    }

    r.ShutDown();

    return 0;
}
*/