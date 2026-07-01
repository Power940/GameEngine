#include <iostream>
#include "../Engine/Engine.h"
#include "SDL3/SDL.h"

#include <set>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", 1280, 1024, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;
    uint64_t now = SDL_GetPerformanceCounter();


    // Define a rectangle
    SDL_FRect player{ 500, 200, 50, 50 };
    SDL_FRect block{ 400, 400, 50, 200 };

    float step = 0;
    bool colorOther = false;
    std::set<Uint32> heldKeys;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
            else if (e.type == SDL_EVENT_KEY_DOWN)
            {
                heldKeys.insert(e.key.key);
            }
            else if (e.type == SDL_EVENT_KEY_UP)
            {
                heldKeys.erase(e.key.key);
            }
        }

        int dX = heldKeys.contains(SDLK_D) - heldKeys.contains(SDLK_A);
        int dY = heldKeys.contains(SDLK_S) - heldKeys.contains(SDLK_W);

        float nexX = player.x + dX * 0.1 * (heldKeys.contains(SDLK_LSHIFT) ? 2 : 1);
        float nexY = player.y + dY * 0.1 * (heldKeys.contains(SDLK_LSHIFT) ? 2 : 1);

        if (!CheckCollision_NonRotated_RectToRect(nexX, nexY, nexX + player.w, nexY + player.h, block.x, block.y, block.x + block.w, block.y + block.h))
        {
            player.x = nexX;
            player.y = nexY;
        }
        else if (!CheckCollision_NonRotated_RectToRect(player.x, nexY, player.x + player.w, nexY + player.h, block.x, block.y, block.x + block.w, block.y + block.h))
        {
            player.y = nexY;
        }
        else if (!CheckCollision_NonRotated_RectToRect(nexX, player.y, nexX + player.w, player.y + player.h, block.x, block.y, block.x + block.w, block.y + block.h))
        {
            player.x = nexX;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &player);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &block);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}