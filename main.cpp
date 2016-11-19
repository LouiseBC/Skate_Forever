#include "Game.hpp"
#include "GameState_Menu.hpp"
#include "GameState_Main.hpp"

int main() {
    Game game;
    if (game.init(new MainGameState))
        game.loop();
}