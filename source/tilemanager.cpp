#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TileManager.hpp"
#include "RenderWindow.hpp"
#include "Tile.hpp"

TileManager::TileManager(RenderWindow& window)
{
    srand(time(0)); // For the random tile spawning
    gridBackgroundSprite = new Sprite(BORDER_HORIZONTAL, BORDER_VERTICAL, BORDER_WIDTH, BORDER_HEIGHT);
    gridBackgroundSprite->texture = window.LoadTexture("assets/gfx/gridBackground.png");
    LoadTileSprites(window);
    SpawnRandomTile();
    SpawnRandomTile();
    currentTiles = 2;
}

void TileManager::LoadTileSprites(RenderWindow& window)
{
    tileSprites[2] = window.LoadTexture("assets/gfx/square.png");
    tileSprites[4] = window.LoadTexture("assets/gfx/square2.png");
    tileSprites[8] = window.LoadTexture("assets/gfx/square3.png");
    tileSprites[16] = window.LoadTexture("assets/gfx/square4.png");
    tileSprites[32] = window.LoadTexture("assets/gfx/square5.png");
    tileSprites[64] = window.LoadTexture("assets/gfx/square6.png"); 
    tileSprites[128] = window.LoadTexture("assets/gfx/square7.png");   
    tileSprites[256] = window.LoadTexture("assets/gfx/square8.png");
    tileSprites[512] = window.LoadTexture("assets/gfx/square9.png");
}

void TileManager::CreateTile(int column, int row)
{
    tiles[column][row] = new Tile(TILE_SIZE);
    Tile* newTile = tiles[column][row];
    newTile->sprite->texture = tileSprites[2];
    newTile->sprite->x = BORDER_HORIZONTAL + (TILE_OFFSET * (row + 1)) + (TILE_SIZE * row);
    newTile->sprite->y = BORDER_VERTICAL + (TILE_OFFSET * (column + 1)) + (TILE_SIZE * column);
}

void TileManager::MoveTiles(MoveDirection direction)
{   
    // The different i and j limits are just so that the tiles in certain corners don't move at all
    // when certain directions are pressed
    if (direction == MoveDirection::RIGHT)
    {
        for (int i = 0; i < 4; i++)
        {
            int rightmostTile = 3;
            bool rightmostTileHasChanged = false;
            for (int j = 2; j >= 0; j--)
            {         
                if (!tiles[i][j]) continue;
 
                // Loops through all possible tiles to the right to find the rightmost space that the current
                // tile can move to or the rightmost tile that the current tile can combine with 
                // This chunk of code is a lot more compact than the original version but it also makes a lot 
                // less sense when just looking at it
                while (rightmostTile > 0)
                {
                    if (tiles[i][rightmostTile] == NULL)
                    {
                        tiles[i][rightmostTile] = tiles[i][j];
                        tiles[i][j] = NULL;
                        tiles[i][rightmostTile]->sprite->x = BORDER_HORIZONTAL 
                                                           + (TILE_OFFSET * (rightmostTile + 1))
                                                           + (TILE_SIZE * rightmostTile);
                        break;
                    }
                    else if (tiles[i][rightmostTile]->value == tiles[i][j]->value)
                    {
                        if (rightmostTile == 0) 
                        {
                            if (rightmostTileHasChanged) continue;
                            else rightmostTileHasChanged = true;
                        } 
                     
                        int newTileValue = tiles[i][j]->value * 2;
                        tiles[i][j] = NULL; 
                        currentTiles--;
                        tiles[i][rightmostTile]->value = newTileValue;
                        tiles[i][rightmostTile]->sprite->texture = tileSprites[newTileValue];   
                        break;
                    }

                    rightmostTile--;
                    if (rightmostTile == j) break;
                }
            }
        }
    }
    else if (direction == MoveDirection::LEFT)
    {
        for (int i = 0; i < 4; i++)
        {
            int leftmostTile = 0;
            bool leftmostTileHasChanged = false; // This is to prevent an issue where a tile could increase
            // value twice in one move
            for (int j = 1; j < 4; j++)
            {
                if (!tiles[i][j]) continue;

                while (leftmostTile < 3)
                {
                    if (tiles[i][leftmostTile] == NULL)
                    {
                        tiles[i][leftmostTile] = tiles[i][j];
                        tiles[i][j] = NULL;
                        tiles[i][leftmostTile]->sprite->x = BORDER_HORIZONTAL 
                                                           + (TILE_OFFSET * (leftmostTile + 1))
                                                           + (TILE_SIZE * leftmostTile);
                        break;
                    }
                    // Checks if leftmost tile or the tile directly to the left of the current tile
                    // has the same value
                    else if (tiles[i][leftmostTile]->value == tiles[i][j]->value)
                    {
                        if (leftmostTile == 0) 
                        {
                            if (leftmostTileHasChanged) continue;
                            else leftmostTileHasChanged = true;
                        } 

                        int newTileValue = tiles[i][j]->value * 2;
                        tiles[i][j] = NULL; 
                        currentTiles--;
                        tiles[i][leftmostTile]->value = newTileValue;
                        tiles[i][leftmostTile]->sprite->texture = tileSprites[newTileValue];    
                        break;
                    }
                    
                    leftmostTile++;
                    if (leftmostTile == j) break;
                }
            }
        }
    }
    else if (direction == MoveDirection::UP)
    {
        // I reverse the order of the loop in the UP logic and the DOWN logic so that it loops over the tiles 
        // in the same way that it does with the RIGHT direction and the LEFT direction
        for (int j = 0; j < 4; j++)
        {
            int topmostTile = 0;
            bool topmostTileHasChanged = false;
            for (int i = 1; i < 4; i++)
            {
                if (!tiles[i][j]) continue;

                while (topmostTile < 3)
                {
                    if (tiles[topmostTile][j] == NULL)
                    {
                        tiles[topmostTile][j] = tiles[i][j];
                        tiles[i][j] = NULL;
                        tiles[topmostTile][j]->sprite->y = BORDER_VERTICAL 
                                                           + (TILE_OFFSET * (topmostTile + 1))
                                                           + (TILE_SIZE * topmostTile);
                        break;
                    }
                    else if (tiles[topmostTile][j]->value == tiles[i][j]->value)
                    {
                        if (topmostTile == 0) 
                        {
                            if (topmostTileHasChanged) continue;
                            else topmostTileHasChanged = true;
                        } 

                        int newTileValue = tiles[i][j]->value * 2;
                        tiles[i][j] = NULL; 
                        currentTiles--;
                        tiles[topmostTile][j]->value = newTileValue;
                        tiles[topmostTile][j]->sprite->texture = tileSprites[newTileValue];          
                        break;
                    }
                    
                    topmostTile++;
                    if (topmostTile == i) break;
                }
            }
        }
    }
    else if (direction == MoveDirection::DOWN)
    {
        for (int j = 0; j < 4; j++)
        {
            int bottommostTile = 3;
            bool bottommostTileHasChanged = false;
            for (int i = 2; i >= 0; i--)
            {
                if (!tiles[i][j]) continue;

                while (bottommostTile > 0)
                {
                    if (tiles[bottommostTile][j] == NULL)
                    {
                        tiles[bottommostTile][j] = tiles[i][j];
                        tiles[i][j] = NULL;
                        tiles[bottommostTile][j]->sprite->y = BORDER_VERTICAL 
                                                           + (TILE_OFFSET * (bottommostTile + 1))
                                                           + (TILE_SIZE * bottommostTile);
                        break;
                    }
                    else if (tiles[bottommostTile][j]->value == tiles[i][j]->value)
                    {
                        if (bottommostTile == 0) 
                        {
                            if (bottommostTileHasChanged) continue;
                            else bottommostTileHasChanged = true;
                        } 

                        int newTileValue = tiles[i][j]->value * 2;
                        tiles[i][j] = NULL; 
                        currentTiles--;
                        tiles[bottommostTile][j]->value = newTileValue;
                        tiles[bottommostTile][j]->sprite->texture = tileSprites[newTileValue];  
                        break;
                    }

                    bottommostTile--;
                    if (bottommostTile == i) break;
                }
            }
        }
    }

    if (currentTiles < 16) SpawnRandomTile();
    else std::cout << "Game over" << std::endl;
}

void TileManager::SpawnRandomTile()
{
    int randomColumn = rand() % 4;
    int randomRow = rand() % 4;
    std::cout << ++timesLooped << std::endl;

    if (tiles[randomColumn][randomRow]) 
    {
        SpawnRandomTile();
    }
    else
    { 
        CreateTile(randomColumn, randomRow);
        timesLooped = 0;
        currentTiles++;
    }
}