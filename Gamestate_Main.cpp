#include "GameState_Main.hpp"

bool MainGameState::init(Graphics* graph, Game* gam) {
    game = gam;
    graphics = graph;
    
    player.init(graphics);
    scenery.init(graphics);
    obstacle.init(graphics);
    
    return true;
}
MainGameState::~MainGameState() {
    player.destroy();
    scenery.destroy();
    obstacle.destroy();
    game     = nullptr;
    graphics = nullptr;
}

void MainGameState::handleEvents(SDL_Event& event) {
    if (event.type == SDL_QUIT)
        game->setQuit();
    if (event.type == SDL_MOUSEBUTTONDOWN)
        game->setQuit();
    if (event.type == SDL_KEYDOWN)
        player.handleEvent(event, obstacle.obstacleType());
}
void MainGameState::update(float deltaTime) {
    obstacle.update(deltaTime);
    player.update(deltaTime);
}

void MainGameState::render() {
    graphics->renderClear();
    
    scenery.render();
    player.render();
    obstacle.render();
    
    graphics->renderPresent();
}