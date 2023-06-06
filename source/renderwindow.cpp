#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Sprite.hpp"

#define WINDOW_COLOR_R 250
#define WINDOW_COLOR_G 248
#define WINDOW_COLOR_B 239
#define WINDOW_COLOR_A 255

#define TEXTURE_RESOLUTION 128

RenderWindow::RenderWindow(const char* title, int width, int height)
{
    window = SDL_CreateWindow(title, 
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              width, height,
                              0);

    if (window == NULL)
        std::cout << "Error: Window has failed to init. Error message: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        std::cout << "Error: Renderer has failed to init. Error message: " << SDL_GetError() << std::endl;

    SDL_SetRenderDrawColor(renderer, WINDOW_COLOR_R, WINDOW_COLOR_G, WINDOW_COLOR_B, WINDOW_COLOR_A);
}

SDL_Texture* RenderWindow::LoadTexture(const char* filePath)
{
    SDL_Texture* texture;
    texture = IMG_LoadTexture(renderer, filePath);

    if (texture == NULL)
        std::cout << "Error: LoadTexture has failed. Error message: " << SDL_GetError() << std::endl;

    return texture;
}

SDL_Texture* RenderWindow::CreateTextureFromSurface(SDL_Surface* surface)
{
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL)
        std::cout << "Error: CreateTextureFromSurface has failed. Error message: " << SDL_GetError() << std::endl;

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

    // Done because text does not have the same resoultion as other sprites
    if (isText)
    {
        SDL_RenderCopy(renderer, sprite.texture, NULL, &destination);
        return;
    }
    
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = TEXTURE_RESOLUTION;
    source.h = TEXTURE_RESOLUTION;

    SDL_RenderCopy(renderer, sprite.texture, &source, &destination);
}

void RenderWindow::Update()
{
    SDL_RenderPresent(renderer);
}