#include <cstdlib>
#include <ctime>

#include "TileManager.hpp"
#include "RenderWindow.hpp"
#include "UIManager.hpp"
#include "Tile.hpp"

TileManager::TileManager(RenderWindow& window, UIManager& UIManager) 
    : windowReference(window), UIManagerReference(UIManager)
{
    srand(time(0)); // For the random tile spawning

    gridBackground = Sprite(BORDER_HORIZONTAL, BORDER_VERTICAL, BORDER_WIDTH, BORDER_HEIGHT);
    gridBackground.texture = window.LoadTexture("assets/gfx/grid_background.png");

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            gridSpaces[row][column] = new GridSpace();
            gridSpaces[row][column]->sprite = Sprite((BORDER_HORIZONTAL + (TILE_OFFSET * (column + 1)) + (TILE_SIZE * column)),
                                                 BORDER_VERTICAL + (TILE_OFFSET * (row + 1)) + (TILE_SIZE * row), 
                                                 TILE_SIZE,
                                                 TILE_SIZE);  
            gridSpaces[row][column]->sprite.texture = window.LoadTexture("assets/gfx/grid_space.png");
        }
    }

    LoadTileSprites();

    SpawnRandomTile();
    SpawnRandomTile();
}

void TileManager::LoadTileSprites()
{
    tileSprites[2] = windowReference.LoadTexture("assets/gfx/2_tile.png");
    tileSprites[4] = windowReference.LoadTexture("assets/gfx/4_tile.png");
    tileSprites[8] = windowReference.LoadTexture("assets/gfx/8_tile.png");
    tileSprites[16] = windowReference.LoadTexture("assets/gfx/16_tile.png");
    tileSprites[32] = windowReference.LoadTexture("assets/gfx/32_tile.png");
    tileSprites[64] = windowReference.LoadTexture("assets/gfx/64_tile.png"); 
    tileSprites[128] = windowReference.LoadTexture("assets/gfx/128_tile.png");   
    tileSprites[256] = windowReference.LoadTexture("assets/gfx/256_tile.png");
    tileSprites[512] = windowReference.LoadTexture("assets/gfx/512_tile.png");
    tileSprites[1024] = windowReference.LoadTexture("assets/gfx/1024_tile.png");
    tileSprites[2048] = windowReference.LoadTexture("assets/gfx/2048_tile.png");
}

void TileManager::CreateTile(int row, int column)
{ 
    gridSpaces[row][column]->occupyingTile = new Tile(TILE_SIZE);
    Tile* newTile = gridSpaces[row][column]->occupyingTile;
    newTile->sprite.texture = tileSprites[2];
    newTile->sprite.x = gridSpaces[row][column]->sprite.x;
    newTile->sprite.y = gridSpaces[row][column]->sprite.y;
}

void TileManager::SetTileDestinations(MoveDirection direction, bool& tilesMoving)
{  
    if (direction == MoveDirection::RIGHT)
    {
        for (int row = 0; row < 4; row++)
        {
            int rightmostColumn = 3;
            for (int column = 2; column >= 0; column--)
            {       
                GridSpace* currentSpace = gridSpaces[row][column];
                if (currentSpace->occupyingTile == nullptr) continue;   

                while (rightmostColumn > column)
                {
                    GridSpace* rightmostSpace = gridSpaces[row][rightmostColumn];
                    if (rightmostSpace->occupyingTile == nullptr)
                    {
                        tilesMoving = true;
                        rightmostSpace->occupyingTile = currentSpace->occupyingTile;
                        currentSpace->occupyingTile = nullptr;
                        break;
                    }
                    else if (rightmostSpace->occupyingTile->value == currentSpace->occupyingTile->value)
                    {
                        tilesMoving = true;
                        rightmostSpace->queuedTile = currentSpace->occupyingTile;
                        rightmostSpace->occupyingTile->value *= 2;
                        currentSpace->occupyingTile = nullptr;
                        rightmostColumn--; // Done so that the rightmost tile 
                                                                     // can't change values twice in one move
                        break;
                    }
        
                    rightmostColumn--;
                }
            }
        }
    }
    else if (direction == MoveDirection::LEFT)
    {
        for (int row = 0; row < 4; row++)
        {
            int leftmostColumn = 0;
            for (int column = 1; column < 4; column++)
            {
                GridSpace* currentSpace = gridSpaces[row][column];
                if (currentSpace->occupyingTile == nullptr) continue;

                while (leftmostColumn < column)
                {
                    GridSpace* leftmostSpace = gridSpaces[row][leftmostColumn]; 
                    if (leftmostSpace->occupyingTile == nullptr)
                    {
                        tilesMoving = true;
                        leftmostSpace->occupyingTile = currentSpace->occupyingTile;
                        currentSpace->occupyingTile = nullptr;
                        break;
                    }
                    // Checks if leftmost tile or the tile directly to the left of the current tile
                    // has the same value
                    else if (leftmostSpace->occupyingTile->value == currentSpace->occupyingTile->value)
                    {
                        tilesMoving = true;
                        leftmostSpace->queuedTile = currentSpace->occupyingTile;
                        leftmostSpace->occupyingTile->value *= 2;
                        currentSpace->occupyingTile = nullptr;
                        leftmostColumn++;   
                        break;
                    }
                    
                    leftmostColumn++;
                }
            }
        }
    }
    else if (direction == MoveDirection::UP)
    {
        // I reversed the order of the loop in the UP logic and the DOWN logic so that it loops over the tiles 
        // in the same way that it does with the RIGHT direction and the LEFT direction
        for (int column = 0; column < 4; column++)
        {
            int topmostRow = 0;
            for (int row = 1; row < 4; row++)
            {
                GridSpace* currentSpace = gridSpaces[row][column];
                if (currentSpace->occupyingTile == nullptr) continue;

                while (topmostRow < row)
                {
                    GridSpace* topmostSpace = gridSpaces[topmostRow][column];
                    if (topmostSpace->occupyingTile == nullptr)
                    {
                        tilesMoving = true;
                        topmostSpace->occupyingTile = currentSpace->occupyingTile;
                        currentSpace->occupyingTile = nullptr;
                        break;
                    }
                    else if (topmostSpace->occupyingTile->value == currentSpace->occupyingTile->value)
                    {
                        tilesMoving = true;
                        topmostSpace->queuedTile = currentSpace->occupyingTile;
                        topmostSpace->occupyingTile->value *= 2;
                        currentSpace->occupyingTile = nullptr;
                        topmostRow++;         
                        break;
                    }
                    
                    topmostRow++;
                }
            }
        }
    }
    else if (direction == MoveDirection::DOWN)
    {
        for (int column = 0; column < 4; column++)
        {
            int bottommostRow = 3;
            for (int row = 2; row >= 0; row--)
            {
                GridSpace* currentSpace = gridSpaces[row][column];
                if (currentSpace->occupyingTile == nullptr) continue;

                while (bottommostRow > row)
                {
                    GridSpace* bottommostSpace = gridSpaces[bottommostRow][column];
                    if (bottommostSpace->occupyingTile == nullptr)
                    {
                        tilesMoving = true;
                        bottommostSpace->occupyingTile = currentSpace->occupyingTile;
                        currentSpace->occupyingTile = nullptr;
                        break;
                    }
                    else if (bottommostSpace->occupyingTile->value == currentSpace->occupyingTile->value)
                    {
                        tilesMoving = true;
                        bottommostSpace->queuedTile = currentSpace->occupyingTile;
                        bottommostSpace->occupyingTile->value *= 2;
                        currentSpace->occupyingTile = nullptr;
                        bottommostRow--; 
                        break;
                    }

                    bottommostRow--;
                }
            }
        }
    }
}

void TileManager::SpawnRandomTile()
{
    int randomRow = rand() % 4;
    int randomColumn = rand() % 4;

    if (gridSpaces[randomRow][randomColumn]->occupyingTile != nullptr) 
    {
        SpawnRandomTile();
    }
    // Ensures that tiles won't spawn in the same place twice unless there's only one space left
    else if (randomRow == lastSpawnRow && randomColumn == lastSpawnColumn && tileCount < 15) 
    {
        SpawnRandomTile();
    }
    else
    { 
        CreateTile(randomRow, randomColumn);
        lastSpawnRow = randomRow;
        lastSpawnColumn = randomColumn;
        tileCount++;
    }
}

void TileManager::DrawGrid()
{
    windowReference.Draw(gridBackground, false);

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            windowReference.Draw(gridSpaces[row][column]->sprite, false);
        }
    }
}

void TileManager::MoveTiles(float deltaTime, bool& tilesMoving)
{ 
    // There's some issue with the tileCount variable I'm not sure what though
    bool allTilesMoved = true;

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            GridSpace* currentSpace = gridSpaces[row][column];
            if (currentSpace->occupyingTile == nullptr) continue;

            bool doneMoving = false;
            bool isTileInQueue = currentSpace->queuedTile != nullptr;

            currentSpace->MoveTile(deltaTime, currentSpace->occupyingTile, doneMoving);
            if (isTileInQueue) currentSpace->MoveTile(deltaTime, currentSpace->queuedTile, doneMoving);
            if (!doneMoving)
            {
                allTilesMoved = false;
                continue;
            }

            if (!isTileInQueue) continue;
            delete currentSpace->queuedTile;
            tileCount--;       
            currentSpace->queuedTile = nullptr;
            UIManagerReference.UpdateScore(currentSpace->occupyingTile->value);
            currentSpace->occupyingTile->sprite.texture = tileSprites[currentSpace->occupyingTile->value];
        }
    }

    tilesMoving = !allTilesMoved;
    if (tileCount < 16 && allTilesMoved)
    { 
        SpawnRandomTile();
    }
}

void TileManager::DrawTiles()
{
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            if (gridSpaces[row][column]->occupyingTile != nullptr)
                windowReference.Draw(gridSpaces[row][column]->occupyingTile->sprite, false);
            
            if (gridSpaces[row][column]->queuedTile != nullptr)
                windowReference.Draw(gridSpaces[row][column]->queuedTile->sprite, false);
        }
    }
}

void TileManager::ResetTiles()
{
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            if (gridSpaces[row][column]->occupyingTile != nullptr)
            {
                delete gridSpaces[row][column]->occupyingTile;
                gridSpaces[row][column]->occupyingTile = nullptr;
            }
            if (gridSpaces[row][column]->queuedTile == nullptr)
            {
                delete gridSpaces[row][column]->queuedTile;
                gridSpaces[row][column]->queuedTile = nullptr;
            }   
        }
    }

    tileCount = 0;
    SpawnRandomTile();
    SpawnRandomTile();
}