#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Sprite.hpp"

RenderWindow::RenderWindow(const char* title, int p_width, int p_height) : width(p_width), height(p_height)
{
    window = SDL_CreateWindow(title, 
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              this->width, this->height,
                              0);

    if (window == NULL)
        std::cout << "Error: Window has failed to init. Error message: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        std::cout << "Error: Renderer has failed to init. Error message: " << SDL_GetError() << std::endl;
}

void RenderWindow::SetColor(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

SDL_Texture* RenderWindow::LoadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
        std::cout << "Error: Texture has failed to load. Error message: " << SDL_GetError() << std::endl;

    return texture;
}

SDL_Texture* RenderWindow::CreateTextureFromSurface(SDL_Surface* p_surface)
{
    SDL_Texture* texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer, p_surface);

    if (texture == NULL)
        std::cout << "Error: SDL_CreateTextureFromSurface has failed. Error message: " << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::Clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::Draw(Sprite& sprite, bool isText)
{
    SDL_Rect destination;
    destination.x = sprite.x;
    destination.y = sprite.y;
    destination.w = sprite.width;
    destination.h = sprite.height; 

    if (isText)
    {
        SDL_RenderCopy(renderer, sprite.texture, NULL, &destination);
        return;
    }
    
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = 128;
    source.h = 128;

    SDL_RenderCopy(renderer, sprite.texture, &source, &destination);
}

void RenderWindow::Update()
{
    SDL_RenderPresent(renderer);
}