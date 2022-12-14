#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "Tile.hpp"
#include "TileManager.hpp"
#include "ScoreManager.hpp"

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

void InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "Error: SDL_Init has failed. Error message: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "Error: IMG_Init has failed. Error message: " << SDL_GetError() << std::endl;

    if (TTF_Init() < 0)
      std::cout << "Error: TTF_Init has failed. Error message: " << SDL_GetError() << std::endl; 
}

int main(int argc, char* argv[])
{
    InitSDL();

    RenderWindow window("2048", WINDOW_WIDTH, WINDOW_HEIGHT);
    window.SetColor(250, 248, 239, 255);

    TileManager tileManager(window);
    ScoreManager scoreManager;

    bool gameRunning = true;
    SDL_Event event;
    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) 
            {
                std::cout << SDL_GetError() << std::endl;
                gameRunning = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                // Registers both WASD and arrow keys
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
                    tileManager.MoveTiles(TileManager::MoveDirection::UP, scoreManager);
                else if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
                    tileManager.MoveTiles(TileManager::MoveDirection::LEFT, scoreManager);
                else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
                    tileManager.MoveTiles(TileManager::MoveDirection::DOWN, scoreManager);
                else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
                    tileManager.MoveTiles(TileManager::MoveDirection::RIGHT, scoreManager);
            }
        }

        window.Clear();

        tileManager.DrawGrid(window);
        tileManager.DrawTiles(window);

        scoreManager.DrawScore(window);

        window.Update();
    }

    SDL_Quit();
    return 0;
}