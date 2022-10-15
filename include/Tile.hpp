#pragma once

#include "Sprite.hpp"

class Tile
{
public:
    Tile(float p_tileSize);

    Sprite* sprite;

    int value = 2;
};