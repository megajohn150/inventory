#include "game.h"
#include "charCheck.h"
#include "item.h"
#include "store.h"
#include <limits>

void Game::setPlayer(Player *newPlayer)
{
    player = newPlayer;
}

Player *Game::getPlayer() const
{
    return player;
}


Menu *Game::getMenu() const
{
    return menu;
}

void Game::setMenu(Menu *newMenu)
{
    menu = newMenu;
}

Shop *Game::getShop() const
{
    return shop;
}

void Game::setShop(Shop *newShop)
{
    shop = newShop;
}

Store *Game::getStore() const
{
    return store;
}

void Game::setStore(Store *newStore)
{
    store = newStore;
}

Game::Game() {
    this->player = new Player();
    this->menu = new Menu();
    this->shop = new Shop();
    this->store = new Store();
    menu->addItem(new Item("Inventory", 1, "game"));
    menu->addItem(new Item("Store", 1, "game"));
    menu->addItem(new Item("Map", 1, "game"));
    menu->addItem(new Item("Navigation guide", 1, "game"));
    store->addItem(new Item("Shop", 1, "game"));
    store->addItem(new Item("Sell", 1, "game"));

    // close range weapons
    // long range weapons
    // defensive equipment
    shop->addItem(new Item("Sword",50, "close range weapons"));
    shop->addItem(new Item("Katana",80, "close range weapons"));
    shop->addItem(new Item("Hammer",60, "close range weapons"));
    shop->addItem(new Item("Spear",55, "close range weapons"));
    shop->addItem(new Item("Axe",65, "close range weapons"));

    shop->addItem(new Item("Bow",70, "long range weapons"));
    shop->addItem(new Item("Crossbow",90, "long range weapons"));
    shop->addItem(new Item("Sling",30, "long range weapons"));

    shop->addItem(new Item("Shield",40, "defensive equipment"));
    shop->addItem(new Item("Armor",100, "defensive equipment"));

}

Game::~Game()
{
    delete this->player;
    delete this->menu;
}



void Game::setPlayerName()
{

    std::string name;
    system(CLEAR);
    std::cout << "Welcome, to start the game, please input your nickname: ";
    std::cin >> name;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // chatgpt

    this->player->setName(name);
}


void Game::play()
{
#ifdef __APPLE__
#define KEY_BACK 127
#else
#define KEY_BACK 8
#endif

    int userInput = 0;
    state = STATE_MENU;
    bool showPrice = false;
    bool showInfo = false;

    while (true) {
        system(CLEAR);

        if (state == STATE_MENU) {
            std::cout << "<===== Welcome to the game, " << player->getName() << "! =====>\n\n~~~~~~~~~~~~~\n";
            menu->display();
            std::cout << "\n\n\n";

            userInput = int(getSingleChar());
            switch (userInput) {
            case 119: // w
                menu->setCurrentRow(menu->getCurrentRow() - 1);
                break;
            case 115: // s
                menu->setCurrentRow(menu->getCurrentRow() + 1);
                break;
            case 10: // enter linux
            case 13: // enter windows
            {
                std::string selected = menu->getItemOnSelectedRC(menu->getCurrentRow(), menu->getCurrentCol())->getName();

                if (selected == "Inventory") {
                    state = STATE_INVENTORY;
                }
                else if (selected == "Store") {
                    state = STATE_STORE;
                }
                else if (selected == "Map") {
                    state = STATE_MAP;
                }
                else {
                    state = STATE_NAVIGATION;
                }
                break;
            }
            case KEY_BACK:
                return;
            }
        }
        else if (state == STATE_INVENTORY) {
            std::cout << "<===== " << player->getName() << "'s inventory =====>\n\n";
            player->getInv()->display();
            if(showInfo){
                if (auto item = player->getInv()->getItemOnSelectedRC(player->getInv()->getCurrentRow(), player->getInv()->getCurrentCol())) {
                    std::cout << "~~~~~~~~~~~~~~~~~~~\n";
                    item->showInfo();
                }
            }
            std::cout << "\n\n\n";
            userInput = int(getSingleChar());

            switch (userInput) {
            case 97: player->getInv()->setCurrentCol(player->getInv()->getCurrentCol() - 1); break;
            case 100: player->getInv()->setCurrentCol(player->getInv()->getCurrentCol() + 1); break;
            case 119: player->getInv()->setCurrentRow(player->getInv()->getCurrentRow() - 1); break;
            case 115: player->getInv()->setCurrentRow(player->getInv()->getCurrentRow() + 1); break;
            case 105: // info
                showInfo = !showInfo;
                break;
                break;
            case 117: // use
                if (auto item = player->getInv()->getItemOnSelectedRC(player->getInv()->getCurrentRow(), player->getInv()->getCurrentCol())) {
                    system(CLEAR);
                    item->use();
                    if (item->getDurability() <= 0) {
                        player->getInv()->removeItem(player->getInv()->getCurrentRow(), player->getInv()->getCurrentCol());
                        std::cout << "Oops! No durability left - item broke...";
                    } else {
                        std::cout << "You used " << item->getName() << "\nDurability remaining: " << item->getDurability();
                    }
                    std::cout << "\nPress any key...";
                    getSingleChar();
                }
                break;
            case 'p': // upgrade
                if (auto item = player->getInv()->getItemOnSelectedRC(player->getInv()->getCurrentRow(), player->getInv()->getCurrentCol())) {
                    system(CLEAR);
                    item->upgradeType();
                    std::cout << "\nPress any key...";
                    getSingleChar();
                }
                break;
            case KEY_BACK: state = STATE_MENU; break;
            }
        }
        else if (state == STATE_STORE) {
            std::cout << "<===== Shop =====>\n\n";
            shop->display();

            if (showPrice) {
                if (auto item = shop->getItemOnSelectedRC(shop->getCurrentRow(), shop->getCurrentCol())) {
                    std::cout << "~~~~~~~~~~~~~\n" << item->getName() << " price - " << item->getPrice() << "\n";
                }
            }

            userInput = int(getSingleChar());
            switch (userInput) {
            case 119: shop->setCurrentRow(shop->getCurrentRow() - 1); break;
            case 115: shop->setCurrentRow(shop->getCurrentRow() + 1); break;
            case 'p': // toggle price
                showPrice = !showPrice;
                break;
            case 'b':{
                auto item = this->shop->getItemOnSelectedRC(shop->getCurrentRow(), shop->getCurrentCol());
                if(player->getInv()->addItem(new Item(item->getName(), item->getPrice(), item->getCategory()))){
                    system(CLEAR);
                    std::cout << "Successfully bought " << item->getName();
                    getSingleChar();
                }
                else{
                    system(CLEAR);
                    std::cout << "Cannot buy any more items, inventory is full";
                    getSingleChar();
                }
                break;
            }
            case KEY_BACK:
                state = STATE_MENU;
                showPrice = false;
                break;
            }
        }
        else if( state == STATE_MAP){
            std::cout << "<================ Map ================>\n\n";
            std::cout << " _______________________________________\n";
            std::cout << "|     ''                                |\n";
            std::cout << "|           ''             ''           |\n";
            std::cout << "|                                       |\n";
            std::cout << "|                                   M   |\n";
            std::cout << "|     ''                          M M   |\n";
            std::cout << "|               @@                M M   |\n";
            std::cout << "| @       ''    @&@        M    M M M   |\n";
            std::cout << "|@@@            @&@      M  M  M    M⠀⠀⠀|\n";
            std::cout << "|@&@@⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀&⠀⠀⠀⠀⠀M⠀⠀⠀⠀⠀M⠀    ⠀⠀M⠀⠀|\n";
            std::cout << "|@&@@⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀M ⠀⠀M⠀⠀⠀⠀⠀⠀⠀⠀⠀    ⠀ M⠀⠀|\n";
            std::cout << "|⠀&⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀M⠀M⠀⠀M⠀⠀⠀⠀⠀⠀⠀⠀    ⠀⠀ MM⠀|\n";
            std::cout << "|⠀&⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀M⠀⠀ M⠀M⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀     M⠀|\n";
            std::cout << "|##⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⠀M⠀⠀⠀MM⠀⠀⠀⠀⠀⠀ ⠀⠀    ⠀⠀⠀ M⠀|\n";
            std::cout << "|###~~~~~~~~~~M                       M⠀|\n";
            std::cout << "|####~~~~~~~~~M                       MM|\n";
            std::cout << "|#####~~~~~~~M                          |\n";
            std::cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n";

            userInput = int(getSingleChar());
            switch(userInput){
            case KEY_BACK:
                state = STATE_MENU;
                break;
            }
        }
        else if(state == STATE_NAVIGATION) {
            std::cout << "<===== Navigation guide =====>\n\n";
            std::cout << "For better user experience, please run this game in your system terminal, not in the code editor one\n~~~~~~~~~~~~~\n";
            std::cout << "Movement:\n W, S, A, D or arrow keys\n~~~~~~~~~~~~~\n";
            std::cout << "Inventory functions:\n i - toggle info\n u - use\n p - weapon upgrade\n~~~~~~~~~~~~~\n";
            std::cout << "Shop functions:\n p - toggle price\n b - buy\n\n\n";

            userInput = int(getSingleChar());
            switch(userInput){
                case KEY_BACK: state = STATE_MENU; break;
            }
        }
    }
}




    // enter : 10
    // backspace : 8
    // del : 127 (macos's backspace)
    // w : 119
    // a : 97
    // s : 115
    // d : 100
    // i : 105
    // u : 117

