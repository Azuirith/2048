#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Sprite.hpp"

class UIManager
{
public:
    UIManager(RenderWindow& window);
    
    void UpdateScore(int scoreIncrement);
    void UpdateHighScore();
    void DrawScore();
    void DrawHighScore();
private:
    void AlignScoreUI();
    void AlignHighScoreUI();
private:
    RenderWindow& windowReference;

    const float UI_VERTICAL = 125.f;
    const float UI_HEIGHT = 50.f;
    const float UI_WIDTH = 24.f;
    
    const float SCORE_HORIZONTAL = 615.f;
    const float HIGH_SCORE_HORIZONTAL = 270.f;

    Sprite scoreSprite;
    Sprite scoreBorderSprite; 
    std::string scoreString = "Score: 0";

    Sprite highScoreSprite;
    Sprite highScoreBorderSprite;
    std::string highScoreString = "Best: 0";

    const int FONT_SIZE = 48;
    TTF_Font* FONT;

    int score = 0;
    int highScore = 0;
};