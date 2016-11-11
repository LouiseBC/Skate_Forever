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
    if (currentState != state::dead) {
        // Jump
        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
            if (currentState == state::onGround) {
                currentState = state::inAir;
                setJumpType(obstacletype);
            }
        }
        // Duck
        if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
            if (currentState == state::onGround) {
                currentState = state::ducking;
                playerPos.h = SPRITE_HEIGHT_DUCK;
                playerPos.y += SPRITE_HEIGHT - SPRITE_HEIGHT_DUCK;
                renderTexture = playerDuck;
            }
        }
        if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) ) {
            currentState = state::onGround;
            playerPos.h = SPRITE_HEIGHT;
            playerPos.y -= SPRITE_HEIGHT - SPRITE_HEIGHT_DUCK;
            renderTexture = playerStand;
        }
    }
}

void Player::setJumpType(const int& obstacletype) {
    obstacleType = obstacletype;
    
    switch(obstacletype) {
        case Obstacle::type::square: // High jump
            yVelocity        = -600.0f;
            gravity          = 1050.0f;
            break;
        default: // Low jump
            yVelocity        = -400.0f;
            gravity          = 1200.0f;
            break;
    }
}

void Player::update(const float& deltaTime, Obstacle* currentObstacle, const float& gameSpeed) {
    if (currentState == inAir) {
        handleJump(deltaTime, gameSpeed);
    }
    if (currentObstacle != nullptr) {
    checkCollision(currentObstacle);
    updateScore(currentObstacle);
    }
}

void Player::handleJump(const float& deltaTime, const float& gameSpeed) {
    if (obstacleType == Obstacle::type::square)
        toggleJumpAnimation();
    
    // Player is in air
    playerPos.y += (int)(yVelocity * deltaTime * gameSpeed);
    yVelocity += gravity * deltaTime * gameSpeed;
    
    // Player landed
    if (playerPos.y >= Y_POS_DEFAULT) {
        currentState = state::onGround;
        playerPos.y = Y_POS_DEFAULT;
        
        if (obstacleType == Obstacle::type::square)
            toggleJumpAnimation();
    }
}
void Player::toggleJumpAnimation() {
    // Reattach skateboard
    if (currentState == state::onGround) {
        playerClip = (SDL_Rect{0, 0, SPRITE_WIDTH, SPRITE_HEIGHT});
        playerPos.h = SPRITE_HEIGHT;
    }
    
    // Detatch skateboard
    else {
        playerClip.h = SPRITE_HEIGHT - SKATEBOARD_HEIGHT;
        playerPos.h = SPRITE_HEIGHT - SKATEBOARD_HEIGHT;
    }
}

void Player::checkCollision(Obstacle* currentObstacle) {
    std::vector<SDL_Rect> obstaclepositions = currentObstacle->positions();
    
    switch (currentObstacle->type()) {
        case Obstacle::type::low:
            isOnObstacle(obstaclepositions);
            checkSideCollision(obstaclepositions);
            break;
        case Obstacle::type::square:
            checkSideCollision(obstaclepositions);
            checkTopCollision(obstaclepositions);
            break;
        case Obstacle::type::longduck: case Obstacle::type::shortduck:
            checkBottomCollision(obstaclepositions);
            break;
    }
}

void Player::checkSideCollision(std::vector<SDL_Rect> obstacle) {
    // Check collision with side of obstacle
    if ( (playerPos.x + playerPos.w - FRONT_SKATEBOARD_OFFSET > obstacle[0].x &&
          playerPos.x < obstacle[0].x + obstacle[0].w/4) &&
        (playerPos.y + playerPos.h > obstacle[0].y) ) {
        //currentObstacle->move(playerPos.x + playerPos.w + 1);
        currentState = state::dead;
    }
}

void Player::checkTopCollision(std::vector<SDL_Rect> obstacle) {
    // Check collision with top of obstacle
    if ( (playerPos.x + playerPos.w > obstacle[obstacle.size()-1].x &&
          playerPos.x < obstacle[obstacle.size()-1].x + obstacle[obstacle.size()-1].w/4) &&
        (playerPos.y + playerPos.h > obstacle[obstacle.size()-1].y) ) {
        playerPos.y = obstacle[obstacle.size()-1].y - playerPos.h;
        currentState = state::dead;
    }
}

void Player::checkBottomCollision(std::vector<SDL_Rect> obstacle) {
    // Check collision with bottom of obstacle
    if ( ((playerPos.y < obstacle[obstacle.size()-1].y + obstacle[obstacle.size()-1].h) &&
          (playerPos.x + playerPos.w > obstacle[0].x)) &&
        (playerPos.x + BACK_HEAD_OFFSET < obstacle[obstacle.size()-1].x + obstacle[obstacle.size()-1].w))
        currentState = state::dead;
}

void Player::isOnObstacle(std::vector<SDL_Rect> obstacle) {
    // Player landed on obstacle
    if (currentState == state::inAir) {
        if ( (playerPos.x + playerPos.w - FRONT_SKATEBOARD_OFFSET > obstacle[0].x &&
              playerPos.x + BACK_SKATEBOARD_OFFSET < obstacle[0].x + obstacle[0].w) &&
             (playerPos.y + playerPos.h >= obstacle[0].y) ) {
            // 'pause' jump mechanics & correct player position
            currentState = onObstacle;
            playerPos.y = obstacle[obstacle.size()-1].y - playerPos.h - 1;
        }
    }
    // Player moves off obstacle, restart gravity mechanics
    else if (playerPos.y < Y_POS_DEFAULT &&
             playerPos.x + BACK_SKATEBOARD_OFFSET > obstacle[obstacle.size()-1].x + obstacle[obstacle.size()-1].w)
        currentState = state:: inAir;
}

void Player::updateScore(Obstacle* currentObstacle) {
    std::vector<SDL_Rect> temp = currentObstacle->positions();
    
    if (!scoreUpdated) {
        if (playerPos.x > temp[temp.size()-1].x + temp[temp.size()-1].w) {
            ++currentScore;
            scoreUpdated = true;
        }
    }
    // Reset boolean when new obstacle reaches player
    // Checking method is reliant on obstacle speed? - to do
    else if ((playerPos.x + playerPos.w > temp[0].x) &&
             playerPos.x + playerPos.w < temp[temp.size()-1].x)
        scoreUpdated = false;
}

void Player::render() {
    graphics->renderTexture(renderTexture, &playerPos, &playerClip);

    if (obstacleType == Obstacle::type::square) {// render skateboard separately
        graphics->renderTexture(playerStand, &skateBoardPos, &skateBoardClip);
    }
}

void Player::renderScore() {
    SDL_Colour fontColour  { 225, 225, 225, 1};
    std::string message = "Score: ";
    std::string scoreMSG = message + std::to_string(currentScore);
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
