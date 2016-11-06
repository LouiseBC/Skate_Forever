#include "Game.hpp"
#include "Gamestate_Main.hpp"

int main() {
    Game game;
    if (game.init(new MainGameState))
        game.loop();
}