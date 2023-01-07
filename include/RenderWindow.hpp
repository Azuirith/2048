#pragma once

#include "Sprite.hpp"

class RenderWindow
{
public: 
    RenderWindow(const char* title, int p_width, int p_height);

    void SetColor(int r, int g, int b, int a);

    SDL_Texture* LoadTexture(const char* filePath);
    SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

    void Clear();
    void Draw(Sprite& sprite, bool isText);
    void Update();

    const int width;
    const int height;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};