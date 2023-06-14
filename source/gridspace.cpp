#include <cstdlib>

#include "GridSpace.hpp"

void GridSpace::MoveTile(float deltaTime, Tile* tile, bool& doneMoving)
{
    float moveDistance = TILE_SPEED * deltaTime;

    float xDistance = std::abs(tile->sprite.x - sprite.x);
    float yDistance = std::abs(tile->sprite.y - sprite.y);
    if (xDistance > moveDistance)
    {
        if (tile->sprite.x < sprite.x) tile->sprite.x += moveDistance;
        else tile->sprite.x -= moveDistance;
        doneMoving = false;
        return;
    }
    else if (yDistance > moveDistance)
    {
        if (tile->sprite.y < sprite.y) tile->sprite.y += moveDistance;
        else tile->sprite.y -= moveDistance;
        doneMoving = false;
        return;
    }

    if (xDistance < moveDistance && xDistance != 0.f) tile->sprite.x = sprite.x;
    if (yDistance < moveDistance && yDistance != 0.f) tile->sprite.y = sprite.y;
    doneMoving = true;
}