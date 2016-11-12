#include "GameState_Main.hpp"
#include "Obstacle.hpp"

bool MainGameState::init(Graphics* graph, Game* gam) {
    game = gam;
    graphics = graph;
    
    player.init(graphics);
    scenery.init(graphics);
    obstacles.init(graphics);
    
    playerScore = player.score();
    return true;
}
MainGameState::~MainGameState() {
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
        if (gamestart == false)
            gamestart = true;
        else
            pause = !pause;
    }
    
    // Any other key event is player-related
    else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        player.handleEvent(event, obstacles.type());
}
void MainGameState::update(const float& deltaTime) {
    if (gamestart == true && pause == false && player.status() != Player::state::dead) {
        scenery.update(deltaTime, gameSpeed);
        obstacles.update(deltaTime, gameSpeed);
        player.update(deltaTime, obstacles.current(), gameSpeed);
        
        setGameDifficulty(player.score());
        std::cerr<< gameSpeed << std::endl;
    }
}

void MainGameState::setGameDifficulty(int playerscore) {
    // Check that the speed hasn't already been updated
    if (playerScore != playerscore) {
        playerScore = playerscore;
    
    // push long duck obstacle to prepare for speed increase
    if (playerscore > 0 && (playerscore + 1) % 5 == 0)
        obstacles.pushObstacle(Obstacle::type::longduck);
    else if (playerscore % 5 == 0)
        gameSpeed += 0.1;
    }
    // Change background colour
    //if (playerscore == 15)
        //scenery.setBackGroundColour(Scenery::colour::yellow);
}

void MainGameState::render() {
    graphics->renderClear();
    
    scenery.render();
    player.render();
    obstacles.render();
    player.renderScore();
    
    graphics->renderPresent();
}