#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Sprite.hpp"

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

void RenderWindow::SetColor(int p_r, int p_g, int p_b, int p_a)
{
    SDL_SetRenderDrawColor(this->renderer, p_r, p_g, p_b, p_a);
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

void RenderWindow::Draw(Sprite p_sprite)
{
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = 64;
    source.h = 64;

    SDL_Rect destination;
    destination.x = p_sprite.x;
    destination.y = p_sprite.y;
    destination.w = p_sprite.width;
    destination.h = p_sprite.height;

    SDL_RenderCopy(this->renderer, p_sprite.texture, &source, &destination);
}

void RenderWindow::Update()
{
    SDL_RenderPresent(this->renderer);
}