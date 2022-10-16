#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Sprite.hpp"

Sprite::Sprite(float p_x, float p_y, float p_width, float p_height) 
               : x(p_x), y(p_y), width(p_width), height(p_height) {};