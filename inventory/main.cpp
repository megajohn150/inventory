//#include <iostream>
#include "game.h"
#ifdef _WIN32
#include "windows.h"



int main() {
    // std::cout << "Detected OS: " << OS_NAME << std::endl;
    SetConsoleOutputCP(65001); //Sets console to UTF-8 mode to avoid issues with map

    Game game;
    game.setPlayerName();
    game.play();
    // game.getPlayer()->getInv()->getItemOnSelectedRC(game.getPlayer()->getInv()->getCurrentRow(), game.getPlayer()->getInv()->getCurrentCol()).

    return 0;
}
#elif _APPLE
int main() {
    Game game;
    game.setPlayerName();
    game.play();
    // game.getPlayer()->getInv()->getItemOnSelectedRC(game.getPlayer()->getInv()->getCurrentRow(), game.getPlayer()->getInv()->getCurrentCol()).

    return 0;
}
#endif
