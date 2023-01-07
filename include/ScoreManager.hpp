#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Sprite.hpp"

class ScoreManager
{
public:
    ScoreManager();
    void DrawScore(RenderWindow& window);
    void UpdateScore(int scoreIncrement);
private:
    const float SCORE_HORIZONTAL = 600.f;
    const float SCORE_VERTICAL = 150.f;
    const float SCORE_WIDTH = 24.f;
    const float SCORE_HEIGHT = 50.f;
    Sprite scoreSprite;
    std::string scoreString = "Score: 0";

    const int FONT_SIZE = 48;
    TTF_Font* FONT;

    int score = 0;
};