#pragma once 

#include <SDL2/SDL.h>

struct Sprite
{
    Sprite();
    Sprite(float x, float y, int width, int height);

    SDL_Texture* texture;

    float x; 
    float y;
    int width;
    int height;
};