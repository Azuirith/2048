#pragma once

class RenderWindow
{
public: 
    RenderWindow(const char* p_title, int p_width, int p_height);

    void Clear();
    void Update();

    const int width;
    const int height;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};