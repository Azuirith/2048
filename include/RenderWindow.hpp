#pragma once

#include "Sprite.hpp"

class RenderWindow
{
public: 
    RenderWindow(const char* title, int width, int height);

    SDL_Texture* LoadTexture(const char* filePath);
    SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

    void Clear();
    void Draw(Sprite& sprite, bool isText);
    void Update();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};