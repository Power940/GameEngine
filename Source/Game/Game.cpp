#include <iostream>
#include "../Engine/Engine.h"
#include "SDL3/SDL.h"

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

    // Define a rectangle
    SDL_FRect greenSquare{ 500, 200, 200, 200 };

    float step = 0;
    bool colorOther = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        step += 0.005f;
        greenSquare.x = sin(step) * 200 + 300;
        greenSquare.y = cos(step) * 200 + 300;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
        SDL_RenderClear(renderer); // Clear the renderer

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Set render draw color to green
        SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDebugText(renderer, 30,30,"test");

        SDL_RenderPresent(renderer); // Render the screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}