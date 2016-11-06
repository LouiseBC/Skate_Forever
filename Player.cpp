#include "Player.hpp"
#include <SDL2_image/SDL_image.h>

void Player::init(Graphics* graph) {
    graphics = graph;
    
    playerStand = IMG_LoadTexture(graphics->renderer(), "Assets/dino.png");
    if (playerStand == nullptr)
        std::cerr << "Error: Load dino texture";
}

void Player::destroy() {
    graphics = nullptr;
    playerStand = nullptr;
}

void Player::render() {
    graphics->renderTexture(playerStand, playerPos);
}

void Player::handleEvent(SDL_Event &event, int obstacletype) {
    if (event.key.keysym.sym == SDLK_SPACE) {
        if (!isjumping) {
            isjumping = true;
            obstacle = obstacletype;
        }
    }
}

void Player::jump(float deltaTime) {
    playerPos.y += (int)(yVelocity * deltaTime);
    yVelocity += gravity * deltaTime;
    
    if (playerPos.y >= Y_POS_DEFAULT) {
        isjumping = false;
        yVelocity = Y_VEL_DEFAULT;
        playerPos.y = Y_POS_DEFAULT;
    }
}

void Player::update(float deltaTime) {
    if (isjumping) {
        jump(deltaTime);
    }
}
/*
 int  yvel                   { 10 }; 320 default
 const int  maxheight        { Y_POS_DEFAULT - 120}; =200
 bool isjumping              { false };
 int obstacle                { -1 };
 };*/