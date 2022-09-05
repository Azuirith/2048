#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Sprite.hpp"

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

    Sprite gridBackground(150.f, 200.f, 600.f, 600.f);
    gridBackground.texture = window.LoadTexture("assets/gfx/grid_background.png");

    window.SetColor(250, 248, 239, 255);

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
        window.Draw(gridBackground);
        window.Update();
    }

    SDL_Quit();
    return 0;
}