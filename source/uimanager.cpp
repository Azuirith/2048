#include <iostream>
#include <string>

#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "UIManager.hpp"
#include "Sprite.hpp"

UIManager::UIManager(RenderWindow& window) : windowReference(window)
{
    // These all are constant values, so they are not in the AlignScoreUI function
    scoreSprite.height = UI_TEXT_HEIGHT;
    scoreSprite.y = SCORE_TEXT_VERTICAL;
    scoreBorderSprite.height = UI_TEXT_HEIGHT;
    scoreBorderSprite.y = SCORE_TEXT_VERTICAL;

    highScoreSprite.height = UI_TEXT_HEIGHT;
    highScoreSprite.y = SCORE_TEXT_VERTICAL;
    highScoreBorderSprite.height = UI_TEXT_HEIGHT;
    highScoreBorderSprite.y = SCORE_TEXT_VERTICAL;

    restartSprite.width = UI_TEXT_WIDTH * restartString.length();
    restartSprite.height = UI_TEXT_HEIGHT;
    restartSprite.x = RESTART_TEXT_HORIZONTAL;
    restartSprite.y = RESTART_TEXT_VERTICAL;

    AlignScoreUI();
    AlignHighScoreUI();

    SDL_Texture* borderTexture = window.LoadTexture("assets/gfx/grid_background.png"); // Reusing this image
    // because there's absolutely no point in creating a whole new one for it
    scoreBorderSprite.texture = borderTexture; 
    highScoreBorderSprite.texture = borderTexture;

    FONT = TTF_OpenFont("assets/fonts/JetBrainsMono-ExtraBold.ttf", FONT_SIZE);   
}

void UIManager::UpdateScore(int scoreIncrement)
{
    score += scoreIncrement;
    scoreString = "Score: " + std::to_string(score);
    AlignScoreUI();
}

void UIManager::DrawScore()
{
    // TODO: Fix that this is called every frame
    // too lazy to do it right now
    windowReference.Draw(scoreBorderSprite, false);
    SDL_Surface* textSurface = TTF_RenderText_Blended(FONT, scoreString.c_str(), SDL_Color{255, 255, 255, 255});
    scoreSprite.texture = windowReference.CreateTextureFromSurface(textSurface);
    windowReference.Draw(scoreSprite, true);
}

void UIManager::ResetScore()
{
    if (score > highScore) UpdateHighScore();
    UpdateScore(-score); // Sets score to 0
}

void UIManager::UpdateHighScore()
{
    highScore = score;
    highScoreString = "Best: " + std::to_string(highScore);
    AlignHighScoreUI();
}

void UIManager::DrawHighScore()
{
    windowReference.Draw(highScoreBorderSprite, false);
    SDL_Surface* textSurface = TTF_RenderText_Blended(FONT, highScoreString.c_str(), SDL_Color{255, 255, 255, 255});
    highScoreSprite.texture = windowReference.CreateTextureFromSurface(textSurface);
    windowReference.Draw(highScoreSprite, true);
}

void UIManager::DrawRestartText()
{
    SDL_Surface* textSurface = TTF_RenderText_Blended(FONT, restartString.c_str(), SDL_Color{187, 173, 160, 255});
    restartSprite.texture = windowReference.CreateTextureFromSurface(textSurface);
    windowReference.Draw(restartSprite, true);
}

void UIManager::AlignScoreUI()
{
    scoreSprite.width = UI_TEXT_WIDTH * scoreString.length();
    scoreSprite.x = SCORE_TEXT_HORIZONTAL - (scoreSprite.width / 2); 
    scoreBorderSprite.width = scoreSprite.width + UI_TEXT_WIDTH;
    scoreBorderSprite.x = scoreSprite.x - (UI_TEXT_WIDTH / 2);
}

void UIManager::AlignHighScoreUI()
{
    highScoreSprite.width = UI_TEXT_WIDTH * highScoreString.length();
    highScoreSprite.x = HIGH_SCORE_TEXT_HORIZONTAL - (highScoreSprite.width / 2);
    highScoreBorderSprite.width = highScoreSprite.width + UI_TEXT_WIDTH;
    highScoreBorderSprite.x = highScoreSprite.x - (UI_TEXT_WIDTH / 2);
}