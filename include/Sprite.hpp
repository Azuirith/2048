#pragma once 

#include <SDL2/SDL.h>

class Sprite
{
public:
    Sprite(float p_x, float p_y, float p_width, float p_height);

    SDL_Texture* texture;

    float x; 
    float y;
    float width;
    float height;
};