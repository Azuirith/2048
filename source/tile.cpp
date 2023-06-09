#include <iostream> // REMOVE

#include "Tile.hpp"
#include "Sprite.hpp"

Tile::Tile(int size)
{
    sprite = new Sprite(0.f, 0.f, size, size);
}

void Tile::Move(float deltaTime, bool& reachedGoal)
{
    if (targetGridSpace == NULL) return;

    float moveDistance = TILE_SPEED * deltaTime;
    float xDistance = std::abs(sprite->x - targetGridSpace->sprite->x);
    float yDistance = std::abs(sprite->y - targetGridSpace->sprite->y);

    if (xDistance > moveDistance)
    {
        if (sprite->x < targetGridSpace->sprite->x) sprite->x += moveDistance;
        else sprite->x -= moveDistance;
        return;
    }
    else if (yDistance > moveDistance)
    {
        if (sprite->y < targetGridSpace->sprite->y) sprite->y += moveDistance;
        else sprite->y -= moveDistance;
        return;
    }
    
    if (xDistance < moveDistance && xDistance != 0) sprite->x = targetGridSpace->sprite->x;
    else if (yDistance < moveDistance && yDistance != 0) sprite->y = targetGridSpace->sprite->y;

    reachedGoal = true;
}