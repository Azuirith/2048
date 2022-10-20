#pragma once

#include <map>

#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "Tile.hpp"

class TileManager
{
public:
    enum MoveDirection
    {
        RIGHT = 0, LEFT, UP, DOWN
    };
public:
    TileManager(RenderWindow& window);

    void LoadTileSprites(RenderWindow& window);
    void CreateTile(int column, int row);
    void MoveTiles(MoveDirection direction);
public:
    Sprite* gridBackgroundSprite;
    
    Tile* tiles[4][4] = {};
private:
    void SpawnRandomTile();
private:
    const float BORDER_HORIZONTAL = 150.f;
    const float BORDER_VERTICAL = 200.f;
    const float BORDER_WIDTH = 600.f;
    const float BORDER_HEIGHT = 600.f;
    const float TILE_OFFSET = 25.f;
    const float TILE_SIZE = (BORDER_WIDTH / 4.f) - ((5.f / 4.f) * TILE_OFFSET);

    std::map<int, SDL_Texture*> tileSprites;

    int currentTiles = 0;
};