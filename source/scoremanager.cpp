#include <iostream>
#include <string>

#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "ScoreManager.hpp"
#include "Sprite.hpp"

ScoreManager::ScoreManager() : FONT(TTF_OpenFont("assets/fonts/JetBrainsMono-ExtraBold.ttf", FONT_SIZE)) 
{
    scoreSprite.width = SCORE_WIDTH * scoreString.length();
    scoreSprite.height = SCORE_HEIGHT;
    scoreSprite.x = SCORE_HORIZONTAL - (scoreSprite.width / 2);
    scoreSprite.y = SCORE_VERTICAL;
}

void ScoreManager::DrawScore(RenderWindow& window)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended(FONT, scoreString.c_str(), SDL_Color{255, 255, 255, 255});
    scoreSprite.texture = window.CreateTextureFromSurface(textSurface);
    window.Draw(scoreSprite, true);
}

void ScoreManager::UpdateScore(int scoreIncrement)
{
    score += scoreIncrement;
    scoreString = "Score: " + std::to_string(score);
    scoreSprite.width = SCORE_WIDTH * scoreString.length();
    scoreSprite.x = SCORE_HORIZONTAL - (scoreSprite.width / 2); 
}