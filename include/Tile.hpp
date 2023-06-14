#pragma once

#include "Sprite.hpp"
#include "GridSpace.hpp"

#define TILE_SPEED 4000

#define TILE_START_VALUE 2

struct GridSpace; // For reasoning behind this see GridSpace.hpp

struct Tile
{
    Tile(int size);

    Sprite sprite;
    int value = TILE_START_VALUE;
};