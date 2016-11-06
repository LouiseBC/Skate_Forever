#include "GameState_Main.hpp"

bool MainGameState::init(Graphics* graph, Game* gam) {
    game = gam;
    graphics = graph;
    
    player.init(graphics);
    scenery.init(graphics);
    obstacles.init(graphics);
    
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
    if (event.type == SDL_MOUSEBUTTONDOWN)
        game->setQuit();
    if (event.type == SDL_KEYDOWN)
        player.handleEvent(event, obstacles.type());
}
void MainGameState::update(float deltaTime) {
    obstacles.update(deltaTime);
    player.update(deltaTime);
}

void MainGameState::render() {
    graphics->renderClear();
    
    scenery.render();
    player.render();
    obstacles.render();
    
    graphics->renderPresent();
}