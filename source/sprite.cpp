#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Sprite.hpp"

Sprite::Sprite() : x(0), y(0), width(128), height(128) {};

Sprite::Sprite(float p_x, float p_y, float p_width, float p_height) 
               : x(p_x), y(p_y), width(p_width), height(p_height) {};