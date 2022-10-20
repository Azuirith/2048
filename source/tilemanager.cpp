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

void TileManager::CreateTile(int row, int column)
{
    tiles[row][column] = new Tile(TILE_SIZE);
    Tile* newTile = tiles[row][column];
    newTile->sprite->texture = tileSprites[2];
    newTile->sprite->x = BORDER_HORIZONTAL + (TILE_OFFSET * (column + 1)) + (TILE_SIZE * column);
    newTile->sprite->y = BORDER_VERTICAL + (TILE_OFFSET * (row + 1)) + (TILE_SIZE * row);
}

void TileManager::MoveTiles(MoveDirection direction)
{   
    // The different i and j limits are just so that the tiles in certain corners don't move at all
    // when certain directions are pressed
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
                        tiles[row][rightmostTile] = tiles[row][column];
                        tiles[row][column] = NULL;
                        tiles[row][rightmostTile]->sprite->x = BORDER_HORIZONTAL 
                                                                + (TILE_OFFSET * (rightmostTile + 1))
                                                                + (TILE_SIZE * rightmostTile);
                        break;
                    }
                    else if (tiles[row][rightmostTile]->value == tiles[row][column]->value)
                    {
                        int newTileValue = tiles[row][column]->value * 2;
                        delete tiles[row][column];
                        tiles[row][column] = NULL; 
                        currentTiles--;
                        tiles[row][rightmostTile]->value = newTileValue;
                        tiles[row][rightmostTile]->sprite->texture = tileSprites[newTileValue]; 

                        if (rightmostTile == 3) rightmostTile--;
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
                        tiles[row][leftmostTile] = tiles[row][column];
                        tiles[row][column] = NULL;
                        tiles[row][leftmostTile]->sprite->x = BORDER_HORIZONTAL 
                                                           + (TILE_OFFSET * (leftmostTile + 1))
                                                           + (TILE_SIZE * leftmostTile);
                        break;
                    }
                    // Checks if leftmost tile or the tile directly to the left of the current tile
                    // has the same value
                    else if (tiles[row][leftmostTile]->value == tiles[row][column]->value)
                    {
                        int newTileValue = tiles[row][column]->value * 2;
                        delete tiles[row][column];
                        tiles[row][column] = NULL; 
                        currentTiles--;
                        tiles[row][leftmostTile]->value = newTileValue;
                        tiles[row][leftmostTile]->sprite->texture = tileSprites[newTileValue]; 

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
                        tiles[topmostTile][column] = tiles[row][column];
                        tiles[row][column] = NULL;
                        tiles[topmostTile][column]->sprite->y = BORDER_VERTICAL 
                                                           + (TILE_OFFSET * (topmostTile + 1))
                                                           + (TILE_SIZE * topmostTile);
                        break;
                    }
                    else if (tiles[topmostTile][column]->value == tiles[row][column]->value)
                    {
                        int newTileValue = tiles[row][column]->value * 2;
                        delete tiles[row][column];
                        tiles[row][column] = NULL; 
                        currentTiles--;
                        tiles[topmostTile][column]->value = newTileValue;
                        tiles[topmostTile][column]->sprite->texture = tileSprites[newTileValue]; 

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
                        tiles[bottommostTile][column] = tiles[row][column];
                        tiles[row][column] = NULL;
                        tiles[bottommostTile][column]->sprite->y = BORDER_VERTICAL 
                                                           + (TILE_OFFSET * (bottommostTile + 1))
                                                           + (TILE_SIZE * bottommostTile);
                        break;
                    }
                    else if (tiles[bottommostTile][column]->value == tiles[row][column]->value)
                    {
                        int newTileValue = tiles[row][column]->value * 2;
                        delete tiles[row][column];
                        tiles[row][column] = NULL; 
                        currentTiles--;
                        tiles[bottommostTile][column]->value = newTileValue;
                        tiles[bottommostTile][column]->sprite->texture = tileSprites[newTileValue];  

                        if (bottommostTile == 3) bottommostTile--;
                        break;
                    }

                    bottommostTile--;
                }
            }
        }
    }

    if (currentTiles < 16) 
    {
        SpawnRandomTile();
    }
    else
    {

    }
}

void TileManager::SpawnRandomTile()
{
    int randomColumn = rand() % 4;
    int randomRow = rand() % 4;

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