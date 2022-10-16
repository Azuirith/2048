#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>

#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "Tile.hpp"

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;

const float BORDER_HORIZONTAL = 150.f;
const float BORDER_VERTICAL = 200.f;
const float BORDER_WIDTH = 600.f;
const float BORDER_HEIGHT = 600.f;
const float TILE_OFFSET = 25.f;
const float TILE_SIZE = (BORDER_WIDTH / 4.f) - ((5.f / 4.f) * TILE_OFFSET);

std::map<int, SDL_Texture*> tileSprites;

void LoadTileSprites(RenderWindow& window)
{
    tileSprites[2] = window.LoadTexture("assets/gfx/square.png");
    tileSprites[4] = window.LoadTexture("assets/gfx/square2.png");
    tileSprites[8] = window.LoadTexture("assets/gfx/square3.png");
}

void CreateTile(RenderWindow* window, Tile* tiles[4][4], int column, int row)
{
    tiles[column][row] = new Tile(TILE_SIZE);
    Tile* newTile = tiles[column][row];
    newTile->sprite->texture = tileSprites[2];
    newTile->sprite->x = BORDER_HORIZONTAL + (TILE_OFFSET * (row + 1)) + (TILE_SIZE * row);
    newTile->sprite->y = BORDER_VERTICAL + (TILE_OFFSET * (column + 1)) + (TILE_SIZE * column);
}

enum MoveDirection
{
    RIGHT = 0, LEFT, UP, DOWN
};

void MoveTiles(Tile* tiles[4][4], MoveDirection direction)
{
    // The different i and j limits are just so that the tiles in certain corners don't move at all
    // when certain directions are pressed
    if (direction == MoveDirection::RIGHT)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 2; j >= 0; j--)
            {         
                if (!tiles[i][j]) continue;

                // Loops through all possible tiles to the right to find the rightmost space that the current
                // tile can move to or the rightmost tile that the current tile can combine wit. This chunk 
                // of code is a lot more compact than the original version but it also makes a lot less sense
                // when just looking at it. 
                int rightmostTile = 3;
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
                        int newTileValue = tiles[i][j]->value * 2;
                        tiles[i][j] = NULL; 
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
            for (int j = 1; j < 4; j++)
            {
                if (!tiles[i][j]) continue;

                int leftmostTile = 0;
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
                    else if (tiles[i][leftmostTile]->value == tiles[i][j]->value)
                    {
                        int newTileValue = tiles[i][j]->value * 2;
                        tiles[i][j] = NULL; 
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
        for (int i = 1; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (!tiles[i][j]) continue;

                int topmostTile = 0;
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
                        int newTileValue = tiles[i][j]->value * 2;
                        tiles[i][j] = NULL; 
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
        for (int i = 2; i >= 0; i--)
        {
            for (int j = 0; j < 4; j++)
            {
                if (!tiles[i][j]) continue;

                int bottommostTile = 3;
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
                        int newTileValue = tiles[i][j]->value * 2;
                        tiles[i][j] = NULL; 
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
}

void InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error: SDL_Init has failed. Error message: " << SDL_GetError() << std::endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "Error: IMG_Init has failed. Error message: " << SDL_GetError() << std::endl;
    }
}

int main(int argc, char* argv[])
{
    InitSDL();

    RenderWindow window("2048", WINDOW_WIDTH, WINDOW_HEIGHT);
    window.SetColor(250, 248, 239, 255);
    
    LoadTileSprites(window);

    Sprite gridBackground(BORDER_HORIZONTAL, BORDER_VERTICAL, BORDER_WIDTH, BORDER_HEIGHT);
    gridBackground.texture = window.LoadTexture("assets/gfx/grid_background.png");

    Tile* tiles[4][4] = {{NULL, NULL, NULL, NULL}, 
                         {NULL, NULL, NULL, NULL}, 
                         {NULL, NULL, NULL, NULL},
                         {NULL, NULL, NULL, NULL}};

    CreateTile(&window, tiles, 0, 0);
    CreateTile(&window, tiles, 1, 0);
    CreateTile(&window, tiles, 2, 0);
    CreateTile(&window, tiles, 2, 2);

    bool gameRunning = true;
    SDL_Event event;
    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) 
            {
                gameRunning = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                // Registers both WASD and arrow keys
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
                    MoveTiles(tiles, MoveDirection::UP);
                else if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
                    MoveTiles(tiles, MoveDirection::LEFT);
                else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
                    MoveTiles(tiles, MoveDirection::DOWN);
                else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
                    MoveTiles(tiles, MoveDirection::RIGHT);
            }
        }

        window.Clear();

        window.Draw(&gridBackground);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (tiles[i][j] == NULL) continue;
                window.Draw(tiles[i][j]->sprite);
            }
        }

        window.Update();
    }

    SDL_Quit();
    return 0;
}