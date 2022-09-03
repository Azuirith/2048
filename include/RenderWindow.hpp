#pragma once

class RenderWindow
{
public: 
    RenderWindow(const char* p_title, int p_width, int p_height);

    SDL_Texture* LoadTexture(const char* p_filePath);

    void Clear();
    void Draw(SDL_Texture* p_texture);
    void Update();

    const int width;
    const int height;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};