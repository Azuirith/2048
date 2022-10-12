#include "Tile.hpp"
#include "Sprite.hpp"

Tile::Tile(float p_tileSize)
{
    sprite = new Sprite(0.f, 0.f, p_tileSize, p_tileSize);
}