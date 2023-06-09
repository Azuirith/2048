#pragma once

#include "Sprite.hpp"
#include "Tile.hpp"

struct Tile; // Prevents errors because I'm including GridSpace and Tile into each other
             // and the compiler doesn't like that

struct GridSpace
{
    int row;
    int column;

    Sprite* sprite;
    Tile* occupyingTile = NULL;

    ~GridSpace();
};