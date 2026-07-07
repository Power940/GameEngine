#include "StarFallEngine.h"

using namespace STR_FALL;

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 1024;

int main()
{
    STR_FALL::Renderer r;
    if (!r.Initialize("testing", WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        return 1;
    }
    STR_FALL::Input input;

    SDL_Event event;
    bool quit = false;

    Vector2 delta = Vector2();
    Rect2D player = Rect2D(500,500,50,50, Color(0,0,255));
    Rect2D block = Rect2D(200,200,50,200, Color(255,0,0));

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
        }
        input.Update();

        delta.x = static_cast<float>(input.GetKeyDown(SDL_SCANCODE_D) - input.GetKeyDown(SDL_SCANCODE_A));
        delta.y = static_cast<float>(input.GetKeyDown(SDL_SCANCODE_S) - input.GetKeyDown(SDL_SCANCODE_W));
        delta *= ((input.GetKeyDown(SDL_SCANCODE_LSHIFT) ? 2 : 1) * 0.1f);

        if (!CheckCollision_NonRotated_RectToRect( Rect2D (player.m_p + delta, player.m_sx, player.m_sy), block))
        {
            player.m_p += delta;
            player.m_p.ClampX(player.m_sx / 2.0f, static_cast<float>(WINDOW_WIDTH) - player.m_sx / 2.0f);
            player.m_p.ClampY(player.m_sy / 2.0f, static_cast<float>(WINDOW_HEIGHT) - player.m_sy / 2.0f);
        }
        else if (!CheckCollision_NonRotated_RectToRect( Rect2D (player.m_p.x, player.m_p.y + delta.y, player.m_sx, player.m_sy), block))
        {
            player.m_p.y += delta.y;
            player.m_p.ClampY(player.m_sy / 2.0f, static_cast<float>(WINDOW_HEIGHT) - player.m_sy / 2.0f);
        }
        else if (!CheckCollision_NonRotated_RectToRect( Rect2D (player.m_p.x + delta.x, player.m_p.y, player.m_sx, player.m_sy), block))
        {
            player.m_p.x += delta.x;
            player.m_p.ClampX(player.m_sx / 2.0f, static_cast<float>(WINDOW_WIDTH) - player.m_sx / 2.0f);
        }

        r.Clear();

        r.RenderFillRectsAABBColor({ player, block });

        r.Present();
    }

    r.ShutDown();

    return 0;
}