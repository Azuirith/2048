#include <iostream>
#include <string>

#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "ScoreManager.hpp"
#include "Sprite.hpp"

ScoreManager::ScoreManager(RenderWindow& window) : windowReference(window)
{
    // These all are constant values, so they are not in the AlignScoreUI function
    scoreSprite.height = UI_HEIGHT;
    scoreSprite.y = UI_VERTICAL;
    scoreBorderSprite.height = UI_HEIGHT;
    scoreBorderSprite.y = UI_VERTICAL;

    highScoreSprite.height = UI_HEIGHT;
    highScoreSprite.y = UI_VERTICAL;
    highScoreBorderSprite.height = UI_HEIGHT;
    highScoreBorderSprite.y = UI_VERTICAL;

    AlignScoreUI();
    AlignHighScoreUI();

    scoreBorderSprite.texture = window.LoadTexture("assets/gfx/grid_background.png"); // Reusing this image
    // because there's absolutely no point in creating a whole new one for it
    highScoreBorderSprite.texture = window.LoadTexture("assets/gfx/grid_background.png");

    FONT = TTF_OpenFont("assets/fonts/JetBrainsMono-ExtraBold.ttf", FONT_SIZE);   
}

void ScoreManager::AlignScoreUI()
{
    scoreSprite.width = UI_WIDTH * scoreString.length();
    scoreSprite.x = SCORE_HORIZONTAL - (scoreSprite.width / 2); 
    scoreBorderSprite.width = scoreSprite.width + UI_WIDTH;
    scoreBorderSprite.x = scoreSprite.x - (UI_WIDTH / 2);
}

void ScoreManager::AlignHighScoreUI()
{
    highScoreSprite.width = UI_WIDTH * highScoreString.length();
    highScoreSprite.x = HIGH_SCORE_HORIZONTAL - (highScoreSprite.width / 2);
    highScoreBorderSprite.width = highScoreSprite.width + UI_WIDTH;
    highScoreBorderSprite.x = highScoreSprite.x - (UI_WIDTH / 2);
}

void ScoreManager::DrawScore()
{
    windowReference.Draw(scoreBorderSprite, false);
    SDL_Surface* textSurface = TTF_RenderText_Blended(FONT, scoreString.c_str(), SDL_Color{255, 255, 255, 255});
    scoreSprite.texture = windowReference.CreateTextureFromSurface(textSurface);
    windowReference.Draw(scoreSprite, true);
}

void ScoreManager::DrawHighScore()
{
    windowReference.Draw(highScoreBorderSprite, false);
    SDL_Surface* textSurface = TTF_RenderText_Blended(FONT, highScoreString.c_str(), SDL_Color{255, 255, 255, 255});
    highScoreSprite.texture = windowReference.CreateTextureFromSurface(textSurface);
    windowReference.Draw(highScoreSprite, true);
}

void ScoreManager::UpdateScore(int scoreIncrement)
{
    score += scoreIncrement;
    scoreString = "Score: " + std::to_string(score);
    AlignScoreUI();
}

void ScoreManager::UpdateHighScore()
{
    highScore = score;
    highScoreString = "Best: " + std::to_string(highScore);
    AlignHighScoreUI();
}