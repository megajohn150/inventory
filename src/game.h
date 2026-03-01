#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "menu.h"
#include "shop.h"
enum GameState {
    STATE_MENU,
    STATE_INVENTORY,
    STATE_MAP,
    STATE_NAVIGATION,
    STATE_STORE_SHOP,
    STATE_STORE_SELL,
    STATE_PLAY_MEDKIT,
    STATE_PLAY,
    STATE_BOSS,
    STATE_BOSS_COOLDOWN
};

class Game
{
private:
    Player* player;
    Menu* menu;
    Shop* shop;
    GameState state;

public:
    Game();
    ~Game();
    void setPlayerName();
    void play();
    void setPlayer(Player *newPlayer);
    Player *getPlayer() const;
    Menu *getMenu() const;
    void setMenu(Menu *newMenu);
    Shop *getShop() const;
    void setShop(Shop *newShop);

};

#endif // GAME_H
