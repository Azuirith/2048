#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

void InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error: SDL_Init has failed. Error message: " << SDL_GetError() << std::endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "Error: IMG_Init has failed. Error message: " << SDL_GetError() << std::endl;
    }
}

int main(int argc, char* argv[])
{
    InitSDL();

    RenderWindow window("2048", 900, 900);

    SDL_Texture* texture = window.LoadTexture("assets/gfx/goat.png");

    bool gameRunning = true;
    SDL_Event event;
    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
        }

        window.Clear();
        window.Draw(texture);
        window.Update();
    }

    SDL_Quit();
    return 0;
}