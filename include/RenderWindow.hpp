#pragma once

#include "Sprite.hpp"

class RenderWindow
{
public: 
    RenderWindow(const char* p_title, int p_width, int p_height);

    void SetColor(int r, int g, int b, int a);

    SDL_Texture* LoadTexture(const char* p_filePath);

    void Clear();
    void Draw(Sprite* p_sprite);
    void Update();

    const int width;
    const int height;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};