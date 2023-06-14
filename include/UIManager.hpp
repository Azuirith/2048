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
    void DrawScore();
    void ResetScore();

    void UpdateHighScore();
    void DrawHighScore();

    void UpdateRestartText();
    void DrawRestartText();
private:
    void AdjustScoreUI();
    void AdjustHighScoreUI();
private:
    RenderWindow& windowReference;

    const float UI_TEXT_WIDTH = 24.f;
    const float UI_TEXT_HEIGHT = 50.f;

    const float SCORE_TEXT_HORIZONTAL = 615.f;
    const float SCORE_TEXT_VERTICAL = 125.f;

    const float RESTART_TEXT_HORIZONTAL = 230.f;
    const float RESTART_TEXT_VERTICAL = 810.f;
    
    const float HIGH_SCORE_TEXT_HORIZONTAL = 270.f;

    Sprite scoreSprite;
    Sprite scoreBorderSprite; 
    std::string scoreString = "Score: 0";

    Sprite highScoreSprite;
    Sprite highScoreBorderSprite;
    std::string highScoreString = "Best: 0";

    Sprite restartSprite;
    std::string restartString = "Press R to restart";

    const int FONT_SIZE = 48;
    TTF_Font* FONT;

    int score = 0;
    int highScore = 0;
};