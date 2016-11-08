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
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        game->setQuit();
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
        pause = !pause;
    
    // Any other key event is player-related
    else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        player.handleEvent(event, obstacles.type());
}
void MainGameState::update(const float& deltaTime) {
    if (pause == false && !player.hasDied()) {
        obstacles.update(deltaTime);
        player.update(deltaTime, obstacles.current());
    }
}

void MainGameState::render() {
    graphics->renderClear();
    
    scenery.render();
    player.render();
    obstacles.render();
    player.renderScore();
    
    graphics->renderPresent();
}