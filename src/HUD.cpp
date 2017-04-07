#include "HUD.hpp"
#include "Graphics.hpp"

void HUD::init(Graphics *graphs) {
    graphics = graphs;
    countDownSound = graphics->loadSound("Assets/count1.wav");
    goSound = graphics->loadSound("Assets/count2.wav");
}

void HUD::destroy() {
    graphics = nullptr;
}

void HUD::restart() {
    counter = 0.5f;
    r = 225;
    g = 225;
    b = 225;
}

bool HUD::countDown(const float& countdowntimer, const std::string& message1,
                    const std::string& message2, const std::string& message3) {
    // Countdown ended
    if (countdowntimer > 2.5f) {
        return false;
    }
    // Select correct message
    std::string message;
    if (countdowntimer < 1.0f) {
        message = message1;
        if (soundsPlayed == 0) {
            Mix_PlayChannel(-1, countDownSound, 0);
            ++soundsPlayed;
        }
    }
    else if (countdowntimer >= 1.0f && countdowntimer < 2.0f) {
        message = message2;
        if (soundsPlayed == 1) {
            Mix_PlayChannel(-1, countDownSound, 0);
            ++soundsPlayed;
        }
    }
    else if (countdowntimer >= 2.0f) {
        message = message3;
        if (soundsPlayed == 2) {
            Mix_PlayChannel(-1, goSound, 0);
            soundsPlayed = 0; // reset
        }
    }
    // Render the texture
    renderCountDown(message);
    return true;
}

void HUD::renderCountDown(const std::string& message) {
    SDL_Colour fontColour  { 225, 225, 225, 1};
    countDownTexture = graphics->renderText(message, "Assets/GreenFlame.ttf", fontColour, 25);
    int W; int H;
    SDL_QueryTexture(countDownTexture, NULL, NULL, &W, &H);
    SDL_Rect countDownPosition;
    countDownPosition.x = graphics->width()/2 - W/2;
    countDownPosition.y = WINDOW_HEIGHT/2 - H/3;
    countDownPosition.w = W;
    countDownPosition.h = H;
    graphics->renderTexture(countDownTexture, &countDownPosition);
}

void HUD::renderScore(const int &score) {
    SDL_Colour fontColour  { 225, 225, 225, 1};
    std::string message = "Score: ";
    std::string scoreMSG = message + std::to_string(score);
    scoreTexture = graphics->renderText(scoreMSG, "Assets/GreenFlame.ttf", fontColour, 25);
    int w; int h;
    SDL_QueryTexture(scoreTexture, NULL, NULL, &w, &h);
    SDL_Rect scorePosition;
    scorePosition.x = graphics->width()/2 - w/2;
    scorePosition.y = 80;
    scorePosition.w = w;
    scorePosition.h = h;
    graphics->renderTexture(scoreTexture, &scorePosition);
}

void HUD::renderHighScore(const int &highscore) {
    SDL_Colour fontColour  { 120, 120, 120, 1};
    std::string message = "Highscore: ";
    std::string scoreMSG = message + std::to_string(highscore);
    highScoreTexture = graphics->renderText(scoreMSG, "Assets/GreenFlame.ttf", fontColour, 15);
    int W; int H;
    SDL_QueryTexture(highScoreTexture, NULL, NULL, &W, &H);
    SDL_Rect scorePosition;
    scorePosition.x = graphics->width() - W*1.25;
    scorePosition.y = 1.5*H;
    scorePosition.w = W;
    scorePosition.h = H;
    graphics->renderTexture(highScoreTexture, &scorePosition);
}

void HUD::setBlendedRender() {
    SDL_SetRenderDrawBlendMode(graphics->renderer(), SDL_BLENDMODE_MOD);
}

void HUD::unSetBlendedRender() {
    SDL_SetRenderDrawBlendMode(graphics->renderer(), SDL_BLENDMODE_NONE);
}

void HUD::pauseScreenOverlay() {
    SDL_SetRenderDrawColor(graphics->renderer(), 112, 112, 112, 1);
    SDL_RenderFillRect(graphics->renderer(), &overlay);
}

void HUD::renderPauseMsg(const std::string& message) {
    SDL_Colour fontColour  { 225, 225, 225, 1};
    pauseTexture = graphics->renderText(message, "Assets/GreenFlame.ttf", fontColour, 20);
    int W; int H;
    SDL_QueryTexture(highScoreTexture, NULL, NULL, &W, &H);
    SDL_Rect pausePosition;
    pausePosition.x = WINDOW_WIDTH/2 - W/2;
    pausePosition.y = WINDOW_HEIGHT/2 - H/2;
    pausePosition.w = W;
    pausePosition.h = H;
    graphics->renderTexture(pauseTexture, &pausePosition);
}

void HUD::fadeDeathScreenOverlay(const float& deltaTime) {
    //Delay a little
    if (counter >= 0.5) {
        if (r > 100) { // r g and b have the same values
            r -= 1;
            g -= 1;
            b -= 1;
        }
    }
    else counter += deltaTime;
}

void HUD::deathScreenOverlay() {
    if (counter >= 0.5) {
        SDL_SetRenderDrawColor(graphics->renderer(), r, g, b, 1);
        SDL_RenderFillRect(graphics->renderer(), &overlay);
    }
}

void HUD::renderDeathMsg(const std::string& message, const std::string& message2) {
    SDL_Colour fontColour  { 225, 225, 225, 1};
    deathTexture = graphics->renderText(message, "Assets/GreenFlame.ttf", fontColour, 50);
    int W; int H;
    SDL_QueryTexture(deathTexture, NULL, NULL, &W, &H);
    SDL_Rect textPosition;
    textPosition.x = WINDOW_WIDTH/2 - W/2;
    textPosition.y = WINDOW_HEIGHT/2 - H/2;
    textPosition.w = W;
    textPosition.h = H;
    graphics->renderTexture(deathTexture, &textPosition);
    
    restartInstruction = graphics->renderText(message2, "Assets/GreenFlame.ttf", fontColour, 15);
    SDL_QueryTexture(restartInstruction, NULL, NULL, &W, &H);
    SDL_Rect restartPosition;
    restartPosition.x = WINDOW_WIDTH/2 - W/2;
    restartPosition.y = textPosition.x + textPosition.h + H;
    restartPosition.w = W;
    restartPosition.h = H;
    graphics->renderTexture(restartInstruction, &restartPosition);
}