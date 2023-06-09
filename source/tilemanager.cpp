#include <iostream> // DELETE
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
            gridSpaces[row][column]->row = row;
            gridSpaces[row][column]->column = column;
            gridSpaces[row][column]->sprite = new Sprite((BORDER_HORIZONTAL + (TILE_OFFSET * (column + 1)) + (TILE_SIZE * column)),
                                                 BORDER_VERTICAL + (TILE_OFFSET * (row + 1)) + (TILE_SIZE * row), 
                                                 TILE_SIZE,
                                                 TILE_SIZE);  
            gridSpaces[row][column]->sprite->texture = window.LoadTexture("assets/gfx/grid_space.png");
        }
    }

    LoadTileSprites();
    SpawnRandomTile();
    SpawnRandomTile();
}

void TileManager::LoadTileSprites()
{
    // I know I could use a loop for this
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
    tiles[row][column] = new Tile(TILE_SIZE);
    gridSpaces[row][column]->occupyingTile = tiles[row][column];
    Tile* newTile = tiles[row][column];
    newTile->sprite->texture = tileSprites[2];
    newTile->sprite->x = gridSpaces[row][column]->sprite->x;
    newTile->sprite->y = gridSpaces[row][column]->sprite->y;
}

void TileManager::SetTileDestinations(MoveDirection direction, bool& tilesMoving)
{   
    bool tilesWillMove = false; // Used for figuring out if a new tile should be spawned

    if (direction == MoveDirection::RIGHT)
    {
        for (int row = 0; row < 4; row++)
        {
            int rightmostTile = 3;
            for (int column = 2; column >= 0; column--)
            {         
                if (!tiles[row][column]) continue;

                // Loops through all possible tiles to the right to find the rightmost space that the current
                // tile can move to or the rightmost tile that the current tile can combine with 
                // This chunk of code is a lot more compact than the original version but it also makes a lot 
                // less sense when just looking at it
                while (rightmostTile > column)
                {
                    if (tiles[row][rightmostTile] == NULL)
                    {
                        tilesWillMove = true;
                        tiles[row][column]->targetGridSpace = gridSpaces[row][rightmostTile];
                        break;
                    }
                    else if (tiles[row][rightmostTile]->value == tiles[row][column]->value)
                    {
                        tilesWillMove = true;
                        tiles[row][column]->targetGridSpace = gridSpaces[row][rightmostTile];
                        if (rightmostTile == 3) rightmostTile--; // Done so that the rightmost tile can't change
                        // values twice in one move
                        break;
                    }
        
                    rightmostTile--;
                }
            }
        }
    }
    else if (direction == MoveDirection::LEFT)
    {
        for (int row = 0; row < 4; row++)
        {
            int leftmostTile = 0;
            for (int column = 1; column < 4; column++)
            {
                if (!tiles[row][column]) continue;

                while (leftmostTile < column)
                {
                    if (tiles[row][leftmostTile] == NULL)
                    {
                        tilesWillMove = true; 
                        tiles[row][column]->targetGridSpace = gridSpaces[row][leftmostTile];
                        break;
                    }
                    // Checks if leftmost tile or the tile directly to the left of the current tile
                    // has the same value
                    else if (tiles[row][leftmostTile]->value == tiles[row][column]->value)
                    {
                        tilesWillMove = true;
                        tiles[row][column]->targetGridSpace = gridSpaces[row][leftmostTile];
                        if (leftmostTile == 0) leftmostTile++;   
                        break;
                    }
                    
                    leftmostTile++;
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
            int topmostTile = 0;
            for (int row = 1; row < 4; row++)
            {
                if (!tiles[row][column]) continue;

                while (topmostTile < row)
                {
                    if (tiles[topmostTile][column] == NULL)
                    {
                        tilesWillMove = true;
                        tiles[row][column]->targetGridSpace = gridSpaces[topmostTile][column];
                        break;
                    }
                    else if (tiles[topmostTile][column]->value == tiles[row][column]->value)
                    {
                        tilesWillMove = true;
                        tiles[row][column]->targetGridSpace = gridSpaces[topmostTile][column];
                        if (topmostTile == 0) topmostTile++;         
                        break;
                    }
                    
                    topmostTile++;
                }
            }
        }
    }
    else if (direction == MoveDirection::DOWN)
    {
        for (int column = 0; column < 4; column++)
        {
            int bottommostTile = 3;
            for (int row = 2; row >= 0; row--)
            {
                if (!tiles[row][column]) continue;

                while (bottommostTile > row)
                {
                    if (tiles[bottommostTile][column] == NULL)
                    {
                        tilesWillMove = true;
                        tiles[row][column]->targetGridSpace = gridSpaces[bottommostTile][column];
                        break;
                    }
                    else if (tiles[bottommostTile][column]->value == tiles[row][column]->value)
                    {
                        tilesWillMove = true;
                        tiles[row][column]->targetGridSpace = gridSpaces[bottommostTile][column];
                        if (bottommostTile == 3) bottommostTile--; 
                        break;
                    }

                    bottommostTile--;
                }
            }
        }
    }

    tilesMoving = tilesWillMove;
}

void TileManager::SpawnRandomTile()
{
    int randomRow = rand() % 4;
    int randomColumn = rand() % 4;

    if (tiles[randomRow][randomColumn]) 
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

bool TileManager::PlayerHasAvailableMoves()
{
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            Tile* currentTile = tiles[row][column];
            Tile* rightTile = NULL; 
            Tile* downTile = NULL;

            if (column + 1 < 4) rightTile = tiles[row][column + 1];
            if (row + 1 < 4) downTile = tiles[row + 1][column];

            if (rightTile != NULL)
            {
                if (currentTile->value == rightTile->value) return true;
            }
            if (downTile != NULL)
            {
                if (currentTile->value == downTile->value) return true;
            }
        }
    }
    return false;
}

void TileManager::DrawGrid()
{
    windowReference.Draw(gridBackground, false);

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            windowReference.Draw(*gridSpaces[row][column]->sprite, false);
        }
    }
}

void TileManager::MoveTiles(float deltaTime, bool& tilesMoving)
{
    bool allTilesMoved = true;

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            Tile* tile = tiles[row][column];
            if (tile == NULL || tile->targetGridSpace == NULL) continue;

            bool reachedGoal;
            tile->Move(deltaTime, reachedGoal);

            if (!reachedGoal)
            {
                allTilesMoved = false;
                continue;
            }

            // I think that there is an incongruency between the actual tiles array and the grid spaces array
            // that is causing the issue
            // could be wrong though just try and work off of that
            // SO CLOSE
            if (tile->targetGridSpace->occupyingTile != NULL) 
            {
                tile->targetGridSpace->occupyingTile = NULL;
                tile->value *= 2;
                tile->sprite->texture = tileSprites[tile->value];
            }

            tile->targetGridSpace->occupyingTile = tile;
            int newRow = tile->targetGridSpace->row;
            int newColumn = tile->targetGridSpace->column;
            tiles[newRow][newColumn] = tile;
            tiles[row][column] = NULL;
            tile->targetGridSpace = NULL;

            std::cout << "Row " << row << " and column " << column << " of tiles: " << tiles[row][column] << std::endl;
            std::cout << "Row " << row << " and column " << column << " of gridSpaces: " << gridSpaces[row][column] << std::endl;
            std::cout << "New row " << newRow << " and new column " << newColumn << " of tiles: " << tiles[newRow][newColumn] << std::endl;
            std::cout << "New row " << newRow << " and new column " << newColumn << " of gridSpaces: " << gridSpaces[newRow][newColumn] << std::endl;
        }
    }

    tilesMoving = !allTilesMoved;
    if (tileCount < 16 && allTilesMoved)
    { 
        SpawnRandomTile();
    }
    else if (tileCount == 16 && !PlayerHasAvailableMoves())
    {
        UIManagerReference.UpdateHighScore();
    }
}

void TileManager::DrawTiles()
{
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            if (tiles[row][column] == NULL) continue;
            windowReference.Draw(*tiles[row][column]->sprite, false);
        }
    }
}

void TileManager::ResetTiles()
{
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            if (tiles[row][column] == NULL) continue;
            delete tiles[row][column];
            tiles[row][column] = NULL;
        }
    }

    tileCount = 0;
    SpawnRandomTile();
    SpawnRandomTile();
}