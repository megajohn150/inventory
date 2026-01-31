// #include <iostream>
#include "game.h"


int main() {
    //std::cout << "Detected OS: " << OS_NAME << std::endl;

    Game game;
    game.setPlayerName();
    game.play();
    // game.getPlayer()->getInv()->getItemOnSelectedRC(game.getPlayer()->getInv()->getCurrentRow(), game.getPlayer()->getInv()->getCurrentCol()).

    return 0;
}
