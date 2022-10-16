#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "Tile.hpp"
#include "TileManager.hpp"

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;

void InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "Error: SDL_Init has failed. Error message: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "Error: IMG_Init has failed. Error message: " << SDL_GetError() << std::endl;
}

int main(int argc, char* argv[])
{
    InitSDL();

    RenderWindow window("2048", WINDOW_WIDTH, WINDOW_HEIGHT);
    window.SetColor(250, 248, 239, 255);

    TileManager tileManager(window);
    tileManager.CreateTile(0, 0);
    tileManager.CreateTile(0, 2);
    tileManager.CreateTile(1, 0);
    tileManager.CreateTile(1, 3);
    tileManager.CreateTile(2, 0);
    tileManager.CreateTile(2, 2);
    tileManager.CreateTile(3, 2);
    tileManager.CreateTile(3, 3);

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
                    tileManager.MoveTiles(TileManager::MoveDirection::UP);
                else if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
                    tileManager.MoveTiles(TileManager::MoveDirection::LEFT);
                else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
                    tileManager.MoveTiles(TileManager::MoveDirection::DOWN);
                else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
                    tileManager.MoveTiles(TileManager::MoveDirection::RIGHT);
            }
        }

        window.Clear();

        window.Draw(tileManager.gridBackgroundSprite);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (tileManager.tiles[i][j] == NULL) continue;
                window.Draw(tileManager.tiles[i][j]->sprite);
            }
        }

        window.Update();
    }

    SDL_Quit();
    return 0;
}