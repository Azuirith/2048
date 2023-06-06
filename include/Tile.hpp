#pragma once

#include "Sprite.hpp"

#define TILE_START_VALUE 2

struct Tile
{
    Tile(int size);

    Sprite* sprite;
    int value = TILE_START_VALUE;

    Sprite* targetGridSpace;
};