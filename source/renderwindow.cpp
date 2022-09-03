#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_width, int p_height) : width(p_width), height(p_height)
{
    window = SDL_CreateWindow(p_title, 
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              this->width, this->height,
                              0);

    if (window == NULL)
    {
        std::cout << "Error: Window has failed to init. Error message: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        std::cout << "Error: Renderer has failed to init. Error message: " << SDL_GetError() << std::endl;
    }
}

void RenderWindow::Clear()
{
    SDL_RenderClear(this->renderer);
}

void RenderWindow::Update()
{
    SDL_RenderPresent(this->renderer);
}