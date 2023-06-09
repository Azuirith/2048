#pragma once

#include <map>

#include "RenderWindow.hpp"
#include "UIManager.hpp"
#include "Sprite.hpp"
#include "GridSpace.hpp"
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
    void SetTileDestinations(MoveDirection direction, bool& tilesMoving);
    bool PlayerHasAvailableMoves();

    void DrawGrid();

    void MoveTiles(float deltaTime, bool& tilesMoving);
    void DrawTiles();
    void ResetTiles(); 
public:
    Sprite gridBackground;
    
    GridSpace* gridSpaces[4][4] = {};
    Tile* tiles[4][4] = {};

    std::map<int, SDL_Texture*> tileSprites;
private:
    void SpawnRandomTile();
private:
    RenderWindow& windowReference;
    UIManager& UIManagerReference;

    const float TILE_SIZE = (BORDER_WIDTH / 4.f) - ((5.f / 4.f) * TILE_OFFSET);

    int tileCount = 0;
    
    int lastSpawnRow = 0;
    int lastSpawnColumn = 0;
};