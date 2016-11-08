#include "Player.hpp"
#include "Obstacle.hpp"
#include <SDL2_image/SDL_image.h>
#include <vector>

void Player::init(Graphics* graph) {
    graphics = graph;
    
    playerStand = graphics->loadTexture("Assets/dino.png");
    playerDuck  = graphics->loadTexture("Assets/dinoduck.png");
    renderTexture = playerStand;
}

void Player::destroy() {
    graphics = nullptr;
}

void Player::handleEvent(SDL_Event& event, const int& obstacletype) {
    if (!isDead) {
        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
            if (isGrounded) {
                isGrounded = false;
                setJumpType(obstacletype);
            }
        }
        if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
            if (playerPos.y == Y_POS_DEFAULT) {
                isDucking = true;
                playerPos.h = SPRITE_HEIGHT_DUCK;
                playerPos.y += DUCK_OFFSET;
                renderTexture = playerDuck;
            }
        }
        if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) ) {
            isDucking = false;
            playerPos.h = SPRITE_HEIGHT;
            playerPos.y -= DUCK_OFFSET;
            renderTexture = playerStand;
        }
    }
}

void Player::setJumpType(const int& obstacletype) {
    switch(obstacletype) {
        case Obstacle::type::square: // High jump
            yVelocity        = -600.0f;
            gravity          = 1050.0f;
            break;
        default: // Low jump
            yVelocity        = -300.0f;
            gravity          = 650.0f;
            break;
    }
}

void Player::update(const float& deltaTime, Obstacle* currentObstacle) {
    if (!isGrounded) {
        handleJump(deltaTime);
    }
    checkCollision(currentObstacle);
    updateScore(currentObstacle);
}

void Player::updateScore(Obstacle* currentObstacle) {
    if (!isDead) {
        std::vector<SDL_Rect> temp = currentObstacle->positions();
        
        if (!scoreUpdated) {
            if (playerPos.x > temp[temp.size()-1].x + temp[temp.size()-1].w) {
                ++currentScore;
                scoreUpdated = true;
            }
        }
        // A new obstacle is encountered
        else if ((playerPos.x + playerPos.w > temp[0].x) &&
                  playerPos.x + playerPos.w < temp[temp.size()-1].x)
            scoreUpdated = false;
    }
}

void Player::handleJump(const float& deltaTime) {
    playerPos.y += (int)(yVelocity * deltaTime);
    yVelocity += gravity * deltaTime;
    
    if (playerPos.y >= Y_POS_DEFAULT) {
        isGrounded = true;
        playerPos.y = Y_POS_DEFAULT;
    }
}

void Player::checkCollision(Obstacle* currentObstacle) {
    std::vector<SDL_Rect> temp = currentObstacle->positions();
    
    if (currentObstacle->type() == Obstacle::type::low ||
        currentObstacle->type() == Obstacle::type::square){
        // Check if player moved on/off obstacle
        isOnObstacle(currentObstacle);
        
        // Check collision with side of obstacle
        if ( (playerPos.x + playerPos.w - SKATEBOARD_OFFSET > temp[0].x &&
              playerPos.x < temp[0].x + temp[0].w/4) &&
             (playerPos.y + playerPos.h > temp[0].y) ) {
            //currentObstacle->move(playerPos.x + playerPos.w + 1);
            isDead = true;
        }
    }
    else {
        // Check collision with bottom of obstacle
        if ( ((playerPos.y < temp[temp.size()-1].y + temp[temp.size()-1].h) &&
              (playerPos.x + playerPos.w > temp[0].x)) &&
              (playerPos.x + BACK_HEAD_OFFSET < temp[temp.size()-1].x + temp[temp.size()-1].w))
            isDead = true;
    }
}

void Player::isOnObstacle(Obstacle* currentObstacle) {
    std::vector<SDL_Rect> temp = currentObstacle->positions();
    
    // Player landed on obstacle
    if (!isGrounded) {
        if ( (playerPos.x + playerPos.w - SKATEBOARD_OFFSET > temp[0].x &&
              playerPos.x + BACK_SKATEBOARD_OFFSET < temp[0].x + temp[0].w) &&
             (playerPos.y + playerPos.h >= temp[0].y) ) {
            // 'pause' jump mechanics & correct player position
            isGrounded = true;
            playerPos.y = temp[temp.size()-1].y - playerPos.h - 1;
        }
    }
    
    // Player moves off obstacle, 'restart' jump mechanics
    else if (playerPos.y < Y_POS_DEFAULT &&
             playerPos.x + BACK_SKATEBOARD_OFFSET > temp[temp.size()-1].x + temp[temp.size()-1].w)
        isGrounded = false;
}

void Player::render() {
    graphics->renderTexture(renderTexture, playerPos);
}

void Player::renderScore() {
    std::string message = "Score: ";
    std::string scoreMSG = message + std::to_string(currentScore);
    score = graphics->renderText(scoreMSG, "Assets/GreenFlame.ttf", fontColour, 25);
    int w; int h;
    SDL_QueryTexture(score, NULL, NULL, &w, &h);
    SDL_Rect scorePosition;
    scorePosition.x = graphics->width()/2 - w/2;
    scorePosition.y = 80;
    scorePosition.w = w;
    scorePosition.h = h;
    graphics->renderTexture(score, scorePosition);
}
