#include "Player.hpp"
#include "Obstacle.hpp"
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <vector>

void Player::init(Graphics* graph) {
    graphics = graph;
    
    playerStand = graphics->loadTexture("Assets/dino.png");
    playerDuck  = graphics->loadTexture("Assets/dinoduck.png");
    renderTexture = playerStand;
    SDL_SetTextureBlendMode( renderTexture, SDL_BLENDMODE_BLEND );
    
    kickoff      = graphics->loadSound("Assets/kickoff.wav");
    playerLand1  = graphics->loadSound("Assets/landsound1.wav");
    playerLand2  = graphics->loadSound("Assets/landsound2.wav");
    highJump     = graphics->loadSound("Assets/jump.wav");
    highJumpLand = graphics->loadSound("Assets/highjumpland.wav");
    duckSound    = graphics->loadSound("Assets/duck.wav");
    deathSound   = graphics->loadSound("Assets/deathsound.wav");
    levelUp      = graphics->loadSound("Assets/levelup.wav");
    
    Mix_VolumeChunk(highJump, 30);
    Mix_VolumeChunk(duckSound, 30);
    //Mix_VolumeChunk(levelUp, 30);
}

void Player::destroy() {
    graphics = nullptr;
}

void Player::restart() {
    playerPos.y = Y_POS_DEFAULT;
    renderTexture = playerStand;
    textureRotation = 0;
    
    playerShadowPos = playerPos;
    skateBoardShadowPos = skateBoardPos;
    playerShadow2Pos = playerPos ;
    skateBoardShadow2Pos = skateBoardPos;
    shadowRotation = 0;
    shadow2Rotation = 0;
    
    currentState = Player::state::onGround;
    currentScore = 0;
}

bool Player::getState() const {
    if (currentState == Player::state::dead)
        return true;
    return false;
}

void Player::handleEvent(SDL_Event& event, const int& obstacletype) {
    if (currentState != state::dead) {
        // Jump
        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
            if (currentState == state::onGround) {
                currentState = state::inAir;
                setJumpHeight(obstacletype);
            }
        }
        if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
            if (currentState == state::onGround)
                duck();
        }
        if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) )
            stopDucking();
    }
}

void Player::duck() {
    currentState = state::ducking;
    playerPos.h = SPRITE_HEIGHT_DUCK - SKATEBOARD_HEIGHT;
    playerPos.y += SPRITE_HEIGHT - SPRITE_HEIGHT_DUCK;
    playerClip.h = SPRITE_HEIGHT_DUCK - SKATEBOARD_HEIGHT;
    renderTexture = playerDuck;
    Mix_PlayChannel(-1, duckSound, 0);
}

void Player::stopDucking() {
    currentState = state::onGround;
    playerPos.h = SPRITE_HEIGHT - SKATEBOARD_HEIGHT;
    playerPos.y -= SPRITE_HEIGHT - SPRITE_HEIGHT_DUCK;
    playerClip.h = SPRITE_HEIGHT - SKATEBOARD_HEIGHT;
    renderTexture = playerStand;
}

void Player::setJumpHeight(const int& obstacletype) {
    obstacleType = obstacletype;
    switch(obstacletype) {
        case Obstacle::type::square: // High jump
            yVelocity        = -600.0f;
            gravity          = 1050.0f;
            break;
        default:                    // Low jump
            yVelocity        = -400.0f;
            gravity          = 1200.0f;
            break;
    }
}

void Player::update(const float& deltaTime, Obstacle* currentObstacle, const float& gameSpeed) {
    // Assign previous position of player to shadows
    updateShadows(deltaTime);
    
    if (currentState == inAir)
        handleJump(deltaTime, gameSpeed);
    
    checkCollision(currentObstacle);
    updateScore(currentObstacle);
    jiggleSkateboard();
}

void Player::handleJump(const float& deltaTime, const float& gameSpeed) {
    // Low obstacle: player first kicks off ground.
    if (obstacleType == Obstacle::type::low && playerPos.y == Y_POS_DEFAULT)
        handleLowJump();
    
    // Square obstacle: Apply rotation
    if (obstacleType == Obstacle::type::square)
        handleHighJump(deltaTime, gameSpeed);
    
    // Apply gravity / jump velocity
    playerPos.y += (int)(yVelocity * deltaTime * gameSpeed);
    yVelocity += gravity * deltaTime * gameSpeed;
    
    // Player landed
    if (playerPos.y >= Y_POS_DEFAULT)
        handleLanding();
}

void Player::handleLowJump() {
    Mix_PlayChannel(-1, kickoff, 0);
    // render whole player
    playerPos.h = SPRITE_HEIGHT;
    playerClip.h = SPRITE_HEIGHT;
    renderSeparateSkateboard = false;
}

void Player::handleHighJump(const float& deltaTime, const float& gameSpeed) {
    // Play sound at kickoff
    if (playerPos.y == Y_POS_DEFAULT)
        Mix_PlayChannel(-1, highJump, 0);
    textureRotation += (int)(320 * deltaTime * gameSpeed);
}

void Player::handleLanding() {
    currentState = state::onGround;
    // reset player position
    playerPos.y = Y_POS_DEFAULT;
    playerPos.h = SPRITE_HEIGHT - SKATEBOARD_HEIGHT;
    playerClip.h = SPRITE_HEIGHT - SKATEBOARD_HEIGHT;
    // Obstacle-specific sounds / data reset
    if (obstacleType == Obstacle::type::low) {
        Mix_PlayChannel(-1, playerLand2, 0);
        renderSeparateSkateboard = true;
    }
    if (obstacleType == Obstacle::type::square) {
        Mix_PlayChannel(-1, highJumpLand, 0);
        textureRotation = 0;
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

void Player::isOnObstacle(std::vector<SDL_Rect> obstacle) {
    // Player landed on obstacle
    if (currentState == state::inAir) {
        if ( (playerPos.x + playerPos.w - FRONT_SKATEBOARD_OFFSET > obstacle[0].x &&
              playerPos.x + BACK_SKATEBOARD_OFFSET < obstacle[obstacle.size()-1].x + obstacle[obstacle.size()-1].w) &&
            (playerPos.y + playerPos.h >= obstacle[0].y) ) {
            // 'pause' jump mechanics & correct player position
            currentState = state::onObstacle;
            playerPos.y = obstacle[obstacle.size()-1].y - playerPos.h - 1;
            Mix_PlayChannel(-1, playerLand1, 0);
        }
    }
    // Player moves off obstacle, restart gravity mechanics
    else if (playerPos.y < Y_POS_DEFAULT &&
             playerPos.x + BACK_SKATEBOARD_OFFSET > obstacle[obstacle.size()-1].x + obstacle[obstacle.size()-1].w)
        currentState = state:: inAir;
}

void Player::checkSideCollision(std::vector<SDL_Rect> obstacle) {
    // Check collision with side of obstacle
    if ( (playerPos.x + playerPos.w - FRONT_SKATEBOARD_OFFSET > obstacle[0].x &&
          playerPos.x < obstacle[0].x + obstacle[0].w/4) &&
        (playerPos.y + playerPos.h > obstacle[0].y) ) {
        //currentObstacle->move(playerPos.x + playerPos.w + 1);
        currentState = state::dead;
        Mix_PlayChannel(-1, deathSound, 0);
    }
}

void Player::checkTopCollision(std::vector<SDL_Rect> obstacle) {
    // Check collision with top of obstacle
    if ( (playerPos.x + playerPos.w > obstacle[obstacle.size()-1].x &&
          playerPos.x < obstacle[obstacle.size()-1].x + obstacle[obstacle.size()-1].w/4) &&
        (playerPos.y + playerPos.h > obstacle[obstacle.size()-1].y) ) {
        playerPos.y = obstacle[obstacle.size()-1].y - playerPos.h;
        currentState = state::dead;
        Mix_PlayChannel(-1, deathSound, 0);
    }
}

void Player::checkBottomCollision(std::vector<SDL_Rect> obstacle) {
    // Check collision with bottom of obstacle
    if ( ((playerPos.y < obstacle[obstacle.size()-1].y + obstacle[obstacle.size()-1].h) &&
          (playerPos.x + playerPos.w > obstacle[0].x)) &&
        (playerPos.x + BACK_HEAD_OFFSET < obstacle[obstacle.size()-1].x + obstacle[obstacle.size()-1].w)) {
        currentState = state::dead;
        Mix_PlayChannel(-1, deathSound, 0);
    }
}

void Player::updateShadows(const float& deltaTime) {
    if (shadowUpdateCounter == 5) {
        // Second shadow data
        playerShadow2Pos = playerShadowPos;
        playerShadow2Pos.x -= SHADOW_OFFSET;
        playerShadow2Clip.h = playerShadowClip.h;
        
        skateBoardShadow2Pos = skateBoardShadowPos;
        skateBoardShadow2Pos.x -= SHADOW_OFFSET;
        shadow2Rotation = shadowRotation;
        
        // First shadow data
        playerShadowPos = playerPos;
        playerShadowPos.x -= SHADOW_OFFSET;
        playerShadowClip.h = playerClip.h;
        
        skateBoardShadowPos = skateBoardPos;
        skateBoardShadowPos.x -= SHADOW_OFFSET;
        shadowRotation = textureRotation;
        
        shadowUpdateCounter = 0;
    }
    else ++shadowUpdateCounter;
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

void Player::jiggleSkateboard() {
    // Not implemented deltaTime - To Do.
    if (frameCount == 3) {
       if (movedAmount == 2)
           direction = -1;
        else if (movedAmount == 0)
            direction = 1;
        
        skateBoardPos.x += direction;
        movedAmount     += direction;
        frameCount = 0;
    }
    else
        ++frameCount;
}

void Player::render() {
    SDL_SetTextureAlphaMod( renderTexture, 70 );
    graphics->renderRotatedTexture(renderTexture, &playerShadow2Pos, shadow2Rotation,
                                   NULL, SDL_FLIP_NONE, &playerShadow2Clip);
    SDL_SetTextureAlphaMod( renderTexture, 100 );
    graphics->renderRotatedTexture(renderTexture, &playerShadowPos, shadowRotation,
                                   NULL, SDL_FLIP_NONE, &playerShadowClip);
    SDL_SetTextureAlphaMod( renderTexture, 255 );
    graphics->renderRotatedTexture(renderTexture, &playerPos, textureRotation,
                                   NULL, SDL_FLIP_NONE, &playerClip);
    
    if (renderSeparateSkateboard) {
        SDL_SetTextureAlphaMod( playerStand, 70 );
        graphics->renderTexture(playerStand, &skateBoardShadow2Pos, &skateBoardClip);
        SDL_SetTextureAlphaMod( playerStand, 100 );
        graphics->renderTexture(playerStand, &skateBoardShadowPos, &skateBoardClip);
        SDL_SetTextureAlphaMod( playerStand, 255 );
        graphics->renderTexture(playerStand, &skateBoardPos, &skateBoardClip);
    }
}
