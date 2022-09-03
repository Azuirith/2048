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

SDL_Texture* RenderWindow::LoadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
    {
        std::cout << "Error: Texture has failed to load. Error message: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void RenderWindow::Clear()
{
    SDL_RenderClear(this->renderer);
}

void RenderWindow::Draw(SDL_Texture* p_texture)
{
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = 32;
    source.h = 32;

    SDL_Rect destination;
    destination.x = this->width / 2 - 16;
    destination.y = this->height / 2 - 16;
    destination.w = 32;
    destination.h = 32;

    SDL_RenderCopy(this->renderer, p_texture, &source, &destination);
}

void RenderWindow::Update()
{
    SDL_RenderPresent(this->renderer);
}