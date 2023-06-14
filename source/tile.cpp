#include <iostream> // REMOVE

#include "Tile.hpp"
#include "Sprite.hpp"

Tile::Tile(int size) : sprite(Sprite(0.f, 0.f, size, size)) {}