#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "Tile.hpp"
#include "TileManager.hpp"
#include "UIManager.hpp"

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

#define FPS 1.f / 60.f

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "Error: SDL_Init has failed. Error message: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "Error: IMG_Init has failed. Error message: " << SDL_GetError() << std::endl;

    if (TTF_Init() < 0)
        std::cout << "Error: TTF_Init has failed. Error message: " << SDL_GetError() << std::endl; 

    RenderWindow window("2048", WINDOW_WIDTH, WINDOW_HEIGHT);
    UIManager UIManager(window);
    TileManager tileManager(window, UIManager);

    float lastFrameTime = 0.f, currentFrameTime;
    float accumulator = 0.f;

    bool gameRunning = true;
    bool tilesMoving = false;

    SDL_Event event;
    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) 
            {
                gameRunning = false;
                break;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (tilesMoving) continue;

                // Registers both WASD and arrow keys
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
                    tileManager.MoveTiles(TileManager::MoveDirection::UP, tilesMoving);
                else if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
                    tileManager.MoveTiles(TileManager::MoveDirection::LEFT, tilesMoving);
                else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
                    tileManager.MoveTiles(TileManager::MoveDirection::DOWN, tilesMoving);
                else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
                    tileManager.MoveTiles(TileManager::MoveDirection::RIGHT, tilesMoving);

                if (event.key.keysym.sym == SDLK_r) // Restart
                {
                    UIManager.ResetScore();
                    tileManager.ResetTiles();
                }
            }
        }

        currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000;
        accumulator += deltaTime;
        lastFrameTime = currentFrameTime;

        while (accumulator >= FPS)
        {   
            window.Clear();

            tileManager.DrawGrid();
            tileManager.DrawTiles();

            UIManager.DrawScore();
            UIManager.DrawHighScore();
            UIManager.DrawRestartText();

            window.Update();

            accumulator -= FPS;
        }
    }

    SDL_Quit();
    return 0;
}