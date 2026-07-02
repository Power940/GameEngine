#include <iostream>
#include <SDL3/SDL.h>
#include <set>
#include <algorithm>

#include "Engine.h"
#include "Rect2D.h"

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 1024;

int main()
{
    nu::Renderer r;
    r.Initialize("testing", WINDOW_WIDTH, WINDOW_HEIGHT);


    SDL_Event e;
    bool quit = false;


    Rect2D player = Rect2D(0, 0, 50, 50);
    Rect2D block = Rect2D(400, 400, 450, 600);

    std::set<Uint32> heldKeys;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                quit = true;
            else if (e.type == SDL_EVENT_KEY_DOWN)
                heldKeys.insert(e.key.key);
            else if (e.type == SDL_EVENT_KEY_UP)
                heldKeys.erase(e.key.key);
        }

        int dX = heldKeys.contains(SDLK_D) - heldKeys.contains(SDLK_A);
        int dY = heldKeys.contains(SDLK_S) - heldKeys.contains(SDLK_W);
        float newX = std::clamp(player.X1() + dX * 0.1f * (heldKeys.contains(SDLK_LSHIFT) ? 2 : 1), 0.0f, static_cast<float>(WINDOW_WIDTH) - player.W());
        float newY = std::clamp(player.Y1() + dY * 0.1f * (heldKeys.contains(SDLK_LSHIFT) ? 2 : 1), 0.0f, static_cast<float>(WINDOW_HEIGHT) - player.H());

        if (!CheckCollision_NonRotated_RectToRect( Rect2D (newX, newY, newX + player.W(), newY + player.H()), block))
        {
            player.Update(newX, newY, newX + player.W(), newY + player.H());
        }
        else if (!CheckCollision_NonRotated_RectToRect( Rect2D (player.X1(), newY, player.X2(), newY + player.H()), block))
        {
            player.Y(newY);
        }
        else if (!CheckCollision_NonRotated_RectToRect( Rect2D (newX, player.Y1(), newX + player.W(), player.Y2()), block))
        {
            player.X(newX);
        }

        r.SetColor(0, 0, 0, 255);
        r.Clear();

        r.SetColor(0, 0, 255, 255);
        r.FillRect(player);

        r.SetColor(255, 0, 0, 255);
        r.FillRect(block);

        r.Present();
    }

    r.ShutDown();

    return 0;
}