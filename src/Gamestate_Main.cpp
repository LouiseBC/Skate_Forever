#include "GameState_Main.hpp"
#include "Obstacle.hpp"

bool MainGameState::init(Graphics* graph, Game* gam) {
    game = gam;
    graphics = graph;
    
    player.init(graphics);
    scenery.init(graphics);
    obstacles.init(graphics);
    hud.init(graphics);
    
    playerScore = player.score();
    getHighScore();
    
    pauseStart = graphics->loadSound("Assets/pause_in.wav");
    pauseStop  = graphics->loadSound("Assets/pause_out.wav");
    
    music = graphics->loadMusic("Assets/music.mp3");
    //Mix_VolumeMusic(20);
    //if (!Mix_PlayMusic(music, 0))
    //    Mix_GetError();
    
    return true;
}

MainGameState::~MainGameState() {
    Mix_FreeMusic(music);
    Mix_FreeChunk(pauseStart);
    Mix_FreeChunk(pauseStop);
    music = nullptr;
    
    player.destroy();
    scenery.destroy();
    obstacles.destroy();
    game     = nullptr;
    graphics = nullptr;
}

void MainGameState::restart() {
    SDL_SetRenderDrawBlendMode(graphics->renderer(), SDL_BLENDMODE_NONE);
    player.restart();
    scenery.restart();
    obstacles.restart();
    hud.restart();
    
    playerIsDead = false;
    isGameBeginning = true;
    countDownTimer = 0.0f;
    gameSpeed = defaultSpeed;
    playerScore = player.score();
}

void MainGameState::handleEvents(SDL_Event& event) {
    if (event.type == SDL_QUIT)
        game->setQuit();
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        game->setQuit();
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
        if (playerIsDead) {
            restart();
        }
        else if (isGameBeginning == false){
            paused = !paused;
            if (paused == true)
                Mix_PlayChannel(-1, pauseStart, 0);
            else if (paused == false) {
                Mix_PlayChannel(-1, pauseStop, 0);
                SDL_SetRenderDrawBlendMode(graphics->renderer(), SDL_BLENDMODE_NONE);
            }
        }
    }
    
    // Any other key event is player-related
    else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        player.handleEvent(event, obstacles.type());
}

void MainGameState::update(const float& deltaTime) {
    if (isGameBeginning)
        countDownTimer += deltaTime;
    
    else if (paused)
        Mix_PauseMusic();
    
    else if (playerIsDead) {
        Mix_PauseMusic(); Mix_RewindMusic();
        hud.fadeDeathScreenOverlay(deltaTime);
    }
    
    else {
        scenery.update(deltaTime, gameSpeed);
        obstacles.update(deltaTime, gameSpeed);
        player.update(deltaTime, obstacles.current(), gameSpeed);
        playerIsDead = player.getState();
        
        setGameDifficulty(player.score());
        if (playerScore > highScore)
            updateHighScore();
        
        if (Mix_PausedMusic())
            Mix_ResumeMusic();
    }
}

void MainGameState::setGameDifficulty(int playerscore) {
    // Check that the speed hasn't already been updated
    if (playerScore != playerscore) {
        playerScore = playerscore;
        
        // push long duck obstacle to prepare for speed increase
        if (playerscore > 0 && (playerscore + 1) % 5 == 0) {
            obstacles.pushObstacle(Obstacle::type::longduck);
        }
        else if (playerscore % 5 == 0) {
            gameSpeed += 0.1;
        }
    }
}

void MainGameState::getHighScore() {
    SDL_RWops* highscore = SDL_RWFromFile("Assets/highscore.txt", "r");
    if (highscore == nullptr)
        highScore = playerScore;
    else SDL_RWread(highscore, &highScore, sizeof(int), 1);
}

void MainGameState::updateHighScore() {
    highScore = playerScore;
    // Update highscores file
    SDL_RWops* highscores = SDL_RWFromFile("Assets/highscore.txt", "w");
    if (highscores == nullptr)
        std::cerr << "Unable to open highscores file " << SDL_GetError() << std::endl;
    SDL_RWwrite(highscores, &highScore, sizeof(int), 1);
    SDL_RWclose(highscores);
}

void MainGameState::render() {
    graphics->renderClear();
    
    scenery.render();
    player.render();
    obstacles.render();
    
    if (isGameBeginning == false) {
        hud.renderScore(playerScore);
        if (playerIsDead)
            hud.renderHighScore(highScore);
    }
    else
        isGameBeginning = hud.countDown(countDownTimer, "Ready..", "Set...", "Go!!");
    
    if (paused) {
        hud.setBlendedRender();
        hud.pauseScreenOverlay();
        hud.renderPauseMsg("Paused");
        hud.unSetBlendedRender();
    }
    
    if (playerIsDead) {
        hud.setBlendedRender();
        hud.deathScreenOverlay();
        hud.renderDeathMsg("Game Over..", "Press spacebar to restart");
        hud.unSetBlendedRender();
    }
    
    graphics->renderPresent();
}