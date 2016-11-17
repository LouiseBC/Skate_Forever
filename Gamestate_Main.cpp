#include "GameState_Main.hpp"
#include "Obstacle.hpp"

bool MainGameState::init(Graphics* graph, Game* gam) {
    game = gam;
    graphics = graph;
    
    player.init(graphics);
    scenery.init(graphics);
    obstacles.init(graphics);
    
    playerScore = player.score();
    getHighScore();
    
    pauseStart = graphics->loadSound("Assets/pause_in.wav");
    pauseStop  = graphics->loadSound("Assets/pause_out.wav");
    
    //music = graphics->loadMusic("Assets/music.mp3");
    //Mix_VolumeMusic(20);
    //if (!Mix_PlayMusic(music, 0))
    //    Mix_GetError();
    
    return true;
}
MainGameState::~MainGameState() {
    //Mix_FreeMusic(music);
    Mix_FreeChunk(pauseStart);
    Mix_FreeChunk(pauseStop);
    music = nullptr;
    
    player.destroy();
    scenery.destroy();
    obstacles.destroy();
    game     = nullptr;
    graphics = nullptr;
}

void MainGameState::handleEvents(SDL_Event& event) {
    if (event.type == SDL_QUIT)
        game->setQuit();
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        game->setQuit();
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
            pause = !pause;
            if (pause == true)
                Mix_PlayChannel(-1, pauseStart, 0);
            else if (pause == false)
                Mix_PlayChannel(-1, pauseStop, 0);
    }
    
    // Any other key event is player-related
    else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        player.handleEvent(event, obstacles.type());
}
void MainGameState::update(const float& deltaTime) {
    if (gameBeginning == true) {
        countDownPacer += deltaTime;
    }
    
    else if (pause == false && player.status() != Player::state::dead) {
        scenery.update(deltaTime, gameSpeed);
        obstacles.update(deltaTime, gameSpeed);
        player.update(deltaTime, obstacles.current(), gameSpeed);
        
        setGameDifficulty(player.score());
        if (playerScore > highScore)
            updateHighScore();
        
        if (Mix_PausedMusic())
            Mix_ResumeMusic();
    }
    
    else if (pause == true) {
        Mix_PauseMusic();
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

void MainGameState::renderCountDown(const std::string message1, const std::string message2, const std::string message3) {
    // Set correct message
    if (countDownPacer > 4.0f)
        gameBeginning = false;
    
    std::string message = "";
    if (countDownPacer >= 1.0f && countDownPacer < 2.0f) {
        message = message1;
    }
    else if (countDownPacer >= 2.0f && countDownPacer < 3.0f)
        message = message2;
    else if (countDownPacer >= 3.0f)
        message = message3;
    
    std::cerr << message << std::endl;
    if (message != "") {
        // Render the texture
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
}

void MainGameState::renderScore() {
    SDL_Colour fontColour  { 225, 225, 225, 1};
    std::string message = "Score: ";
    std::string scoreMSG = message + std::to_string(playerScore);
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
        printf( "Warning: Unable to open file! SDL Error: %s\n", SDL_GetError() );
    SDL_RWwrite(highscores, &highScore, sizeof(int), 1);
    SDL_RWclose(highscores);
}

void MainGameState::renderHighScore() {
    SDL_Colour fontColour  { 120, 120, 120, 1};
    std::string message = "Highscore: ";
    std::string scoreMSG = message + std::to_string(highScore);
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

void MainGameState::renderPause(const std::string& message) {
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

void MainGameState::render() {
    graphics->renderClear();
    
    scenery.render();
    player.render();
    obstacles.render();
    
    if (gameBeginning == false) {
        renderScore();
        renderHighScore();
    }
    
    if (gameBeginning == true)
        renderCountDown("Ready?", "Set...", "Go!!");
    
    if (pause == true)
        renderPause("- Paused -");
    
    graphics->renderPresent();
}