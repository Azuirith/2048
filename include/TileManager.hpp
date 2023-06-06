#pragma once

#include <map>

#include "RenderWindow.hpp"
#include "UIManager.hpp"
#include "Sprite.hpp"
#include "Tile.hpp"

#define BORDER_HORIZONTAL 150.f
#define BORDER_VERTICAL 200.f
#define BORDER_WIDTH 600.f
#define BORDER_HEIGHT 600.f
#define TILE_OFFSET 25.f

class TileManager
{
public:
    enum MoveDirection
    {
        RIGHT = 0, LEFT, UP, DOWN
    };
public:
    TileManager(RenderWindow& window, UIManager& UIManager);

    void LoadTileSprites();
    void CreateTile(int column, int row);
    void MoveTiles(MoveDirection direction, bool& tilesMoving);
    bool PlayerHasAvailableMoves();

    void DrawGrid();
    void DrawTiles();

    void ResetTiles(); 
public:
    Sprite gridBackground;
    
    Sprite* gridSpaces[4][4] = {};
    Tile* tiles[4][4] = {};
private:
    void SpawnRandomTile();
private:
    RenderWindow& windowReference;
    UIManager& UIManagerReference;

    const float TILE_SIZE = (BORDER_WIDTH / 4.f) - ((5.f / 4.f) * TILE_OFFSET);

    std::map<int, SDL_Texture*> tileSprites;

    int tileCount = 0;
    
    int lastSpawnRow = 0;
    int lastSpawnColumn = 0;
};