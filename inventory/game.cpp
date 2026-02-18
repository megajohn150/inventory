#include "game.h"
#include "charCheck.h"
#include "item.h"
#include "store.h"
#include <limits>
#include "random.h"
#include <vector>
void Game::setPlayer(Player *newPlayer) { player = newPlayer; }
Player *Game::getPlayer() const { return player; }
Menu *Game::getMenu() const { return menu; }
void Game::setMenu(Menu *newMenu) { menu = newMenu; }
Shop *Game::getShop() const { return shop; }
void Game::setShop(Shop *newShop) { shop = newShop; }
Store *Game::getStore() const { return store; }
void Game::setStore(Store *newStore) { store = newStore; }

Game::Game() {
    this->player = new Player();
    this->menu   = new Menu();
    this->shop   = new Shop();
    this->store  = new Store();

    menu->addItem(new Item("Play",      1, "game"));
    menu->addItem(new Item("Inventory", 1, "game"));
    menu->addItem(new Item("Store",     1, "game"));
    menu->addItem(new Item("Map",       1, "game"));
    menu->addItem(new Item("Guide",     1, "game"));

    store->addItem(new Item("Buy",  1, "game"));
    store->addItem(new Item("Sell", 1, "game"));

    // close range weapons
    shop->addItem(new Item("Sword",   15, "close range weapons"));
    shop->addItem(new Item("Katana",  35, "close range weapons"));
    shop->addItem(new Item("Hammer",  30, "close range weapons"));
    shop->addItem(new Item("Spear",   25, "close range weapons"));
    shop->addItem(new Item("Axe",     30, "close range weapons"));

    // long range weapons
    shop->addItem(new Item("Bow",      30, "long range weapons"));
    shop->addItem(new Item("Crossbow", 45, "long range weapons"));
    shop->addItem(new Item("Sling",    12, "long range weapons"));

    // armor
    shop->addItem(new Item("Used armor", 20,  "armor"));
    shop->addItem(new Item("Armor",  50,  "armor"));
}

Game::~Game() {
    delete this->player;
    delete this->menu;
    delete this->shop;
    delete this->store;
}

void Game::setPlayerName() {
    std::string name;
    system(CLEAR);
    std::cout << "Welcome, to start the game, please input your nickname: ";
    std::cin >> name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->player->setName(name);
}

// chooses the strongest weapon (close/long ranged)
// earnign more coins when better weapon + boost based on rarity
static Item* pickActiveWeapon(Item* melee, Item* ranged) {
    if (melee && ranged) {
        int meleeScore  = melee->getType()  * 10 + melee->getRarity();
        int rangedScore = ranged->getType() * 10 + ranged->getRarity();
        return (meleeScore >= rangedScore) ? melee : ranged;
    }
    return melee ? melee : ranged;
}

static int baseEarnByName(const std::string& name) {
    // close range
    if (name == "Sword")    return 2;
    if (name == "Spear")    return 2;
    if (name == "Hammer")   return 3;
    if (name == "Axe")      return 3;
    if (name == "Katana")   return 4;
    // long range
    if (name == "Sling")    return 1;
    if (name == "Bow")      return 3;
    if (name == "Crossbow") return 4;
    return 2;
}

static float rarityMultiplier(Rarity r) {
    switch (r) {
    case common:    return 1.0f;
    case uncommon:  return 1.5f;
    case rare:      return 2.5f;
    case epic:      return 4.0f;
    case legendary: return 7.0f;
    case unknown:   return 12.0f;
    default:        return 1.0f;
    }
}

// better armor + better weapon = less coins stolen
static int zombieSteal(Item* weapon, Item* armor) {

    int base = 10;
    if (weapon) {
        switch (weapon->getType()) {
        case wooden:  base = 8;  break;
        case stone:   base = 6;  break;
        case iron:    base = 4;  break;
        case gold:    base = 2;  break;
        case diamond: base = 1;  break;
        case unseen:  base = 0;  break;
        default:      base = 8;  break;
        }
        float wMult = 1.0f;
        switch (weapon->getRarity()) {
        case common:    wMult = 1.0f;  break;
        case uncommon:  wMult = 0.8f;  break;
        case rare:      wMult = 0.6f;  break;
        case epic:      wMult = 0.35f; break;
        case legendary: wMult = 0.15f; break;
        case unknown:   wMult = 0.0f;  break;
        default:        wMult = 1.0f;  break;
        }
        base = int(base * wMult);
    }

    if (base == 0) return 0;

    if (armor) {
        float armorBase = 0.0f;
        if      (armor->getName() == "Used armor") armorBase = 0.20f;
        else if (armor->getName() == "Armor")  armorBase = 0.40f;
        else                                   armorBase = 0.15f;

        float rarityBonus = 0.0f;
        switch (armor->getRarity()) {
        case common:    rarityBonus = 0.0f;  break;
        case uncommon:  rarityBonus = 0.05f; break;
        case rare:      rarityBonus = 0.10f; break;
        case epic:      rarityBonus = 0.18f; break;
        case legendary: rarityBonus = 0.28f; break;
        case unknown:   rarityBonus = 0.40f; break;
        default:        rarityBonus = 0.0f;  break;
        }

        float totalReduction = std::min(armorBase + rarityBonus, 0.90f);
        base = int(base * (1.0f - totalReduction));
    }

    return std::max(base, 0);
}

static int calculateSellPrice(Item* item) {
    if (!item) return 0;

    float base = item->getPrice() * 0.65f;

    float typeMult = 1.0f;
    switch (item->getType()) {
    case wooden:  typeMult = 1.0f;  break;
    case stone:   typeMult = 1.6f;  break;
    case iron:    typeMult = 2.4f;  break;
    case gold:    typeMult = 3.8f;  break;
    case diamond: typeMult = 6.0f;  break;
    case unseen:  typeMult = 11.0f; break;
    default:      typeMult = 1.0f;  break;
    }

    float rarityMult = 1.0f;
    switch (item->getRarity()) {
    case common:    rarityMult = 1.0f;  break;
    case uncommon:  rarityMult = 1.5f;  break;
    case rare:      rarityMult = 2.2f;  break;
    case epic:      rarityMult = 3.2f;  break;
    case legendary: rarityMult = 5.5f;  break;
    case unknown:   rarityMult = 9.0f;  break;
    default:        rarityMult = 1.0f;  break;
    }

    float durMult = item->getDurability() / 100.0f;
    durMult = std::max(durMult, 0.1f);

    return std::max(1, int(base * typeMult * rarityMult * durMult));
}
void Game::play() {
#ifdef __APPLE__
#define KEY_BACK 127
#else
#define KEY_BACK 8
#endif

    int  userInput    = 0;
    state             = STATE_MENU;
    bool showPrice    = false;
    bool showInfo     = false;
    bool equipMode    = false;
    bool used         = false;
    bool used2        = false;
    bool used3        = false;
    bool repairPending = false;
    int  repairCost    = 0;
    int  repairTarget  = 0;
    std::string secretCode = "";
    std::string lastEvent  = "";
    bool upgradePending = false;
    int  upgradeCost    = 0;
    std::string upgradeFrom = "";
    std::string upgradeTo   = "";
    bool sellPending = false;
    int  sellPrice   = 0;
    int  sellCursor = 0;

    while (true) {
        system(CLEAR);

        // ===================== MENU =====================
        if (state == STATE_MENU) {
            std::cout << "<===== Welcome to the game, " << player->getName() << "! =====>\n\n~~~~~~~~~~~~~\n";
            menu->display();
            std::cout << "\n\n\n";

            userInput = int(getSingleChar());
            switch (userInput) {
            case 'w': menu->setCurrentRow(menu->getCurrentRow() - 1); break;
            case 's': menu->setCurrentRow(menu->getCurrentRow() + 1); break;
            case 10: case 13: {
                auto item = menu->getItemOnSelectedRC(menu->getCurrentRow(), menu->getCurrentCol());
                if (!item) break;
                std::string sel = item->getName();
                if      (sel == "Inventory") state = STATE_INVENTORY;
                else if (sel == "Store")     state = STATE_STORE;
                else if (sel == "Play")      state = STATE_PLAY;
                else if (sel == "Map")       state = STATE_MAP;
                else                         state = STATE_NAVIGATION;
                break;
            }
            case KEY_BACK: {

                system(CLEAR);
                std::cout << "Are you sure you want to quit? Your progress will be lost (press ";
                if(KEY_BACK == 127){std::cout<<"delete";}
                else{std::cout<<"esc";};
                std::cout<<" to confirm)";
                int confirm = int(getSingleChar());
                if (confirm == KEY_BACK)
                    return;
                break;
            }
            }
        }

        // ===================== PLAY =====================
        else if (state == STATE_PLAY) {
            system(CLEAR);
            std::cout << "<===== Play =====>\n\n";

            Item* activeWeapon = pickActiveWeapon(
                player->getEquip()->getMelee(),
                player->getEquip()->getRanged()
                );

            if (activeWeapon) {
                std::string slot = (activeWeapon == player->getEquip()->getMelee()) ? "melee" : "ranged";
                std::cout << "Active weapon [" << slot << "]: "
                          << activeWeapon->getTypeString() << " " << activeWeapon->getName()
                          << " (" << activeWeapon->getRarityString() << ")"
                          << "  -  Durability: " << activeWeapon->getDurability() << "/100\n";
            } else {
                std::cout << "Active weapon: none\n";
            }

            std::cout << "Balance: " << player->getMoney() << "\n\n";
            std::cout << "Click to fight!!\n";

            if (!lastEvent.empty())
                std::cout << "\n" << lastEvent << "\n";

            userInput = int(getSingleChar());

            if (userInput == KEY_BACK) {
                state       = STATE_MENU;
                // earnedMoney = 0;
                lastEvent   = "";
                continue;
            }

            Item* checkWeapon = pickActiveWeapon(
                player->getEquip()->getMelee(),
                player->getEquip()->getRanged()
                );
            if (!checkWeapon) {
                lastEvent = "No weapon equipped, equip some to play";
                continue;
            }

            activeWeapon->use();

            if (activeWeapon->getDurability() <= 0) {
                std::string brokenName = activeWeapon->getName();

                int prevCursor = player->getEquip()->getCursorSlot();
                int targetSlot = (activeWeapon == player->getEquip()->getMelee()) ? 2 : 1;
                while (player->getEquip()->getCursorSlot() != targetSlot)
                    player->getEquip()->moveCursor(1);

                Item* broken = player->getEquip()->unequipSelected();
                delete broken;

                while (player->getEquip()->getCursorSlot() != prevCursor)
                    player->getEquip()->moveCursor(1);

                activeWeapon = nullptr;
                lastEvent = "!! " + brokenName + " has broke.";
                continue;
            }

            int earned = std::max(1, int(
                                         baseEarnByName(activeWeapon->getName()) * rarityMultiplier(activeWeapon->getRarity())
                                         ));

            int roll = Random::range(1, 100);
            if (roll <= 25) {
                Item* weaponNow = pickActiveWeapon(
                    player->getEquip()->getMelee(),
                    player->getEquip()->getRanged()
                    );
                int stolen = zombieSteal(weaponNow, player->getEquip()->getArmor());
                stolen = std::min(stolen, player->getMoney());
                player->setMoney(player->getMoney() - stolen);

                // armor zawsze sie zuzywa przy ataku zombie (niezaleznie od stolen)
                Item* armorItem = player->getEquip()->getArmor();
                bool armorBroke = false;
                if (armorItem) {
                    armorItem->use();

                    if (armorItem->getDurability() <= 0) {
                        int prevCursor = player->getEquip()->getCursorSlot();
                        while (player->getEquip()->getCursorSlot() != 0)
                            player->getEquip()->moveCursor(1);
                        Item* broken = player->getEquip()->unequipSelected();
                        delete broken;
                        while (player->getEquip()->getCursorSlot() != prevCursor)
                            player->getEquip()->moveCursor(1);
                        armorBroke = true;
                        armorItem  = nullptr;
                    }
                }

                if (stolen == 0) {
                    player->setMoney(player->getMoney() + earned);
                    lastEvent = ">> Zombie attacked! Your equipment scared him off. You earned: "
                                + std::to_string(earned) + "!"
                                + (armorBroke ? " Your armor broke!" : "");
                } else {
                    if (armorBroke) {
                        lastEvent = ">> Zombie attacked! You lost " + std::to_string(stolen)
                        + " coins and your armor broke!";
                    } else if (armorItem) {
                        lastEvent = ">> Zombie attacked! You lost " + std::to_string(stolen)
                        + " coins. Armor: " + std::to_string(armorItem->getDurability()) + "/100";
                    } else {
                        lastEvent = ">> Zombie attacked! You lost " + std::to_string(stolen) + " coins.";
                    }
                }
            } else {
                lastEvent = ">> You earned +" + std::to_string(earned) + " coins!";
                player->setMoney(player->getMoney() + earned);
            }
        }

        // ===================== INVENTORY =====================
        else if (state == STATE_INVENTORY) {
            std::cout << "<===== " << player->getName() << "'s inventory =====>\n\n";
            std::cout << "Balance: " << player->getMoney() << "                 ";


            if (equipMode)
                std::cout << " [Inventory]  >[EQUIPMENT]<\n\n";
            else
                std::cout << ">[INVENTORY]<  [Equipment]\n\n";


            player->getInv()->display(player->getEquip(), equipMode);


            if (showInfo) {
                std::cout << "~~~~~~~~~~~~~~~~~~~\n";
                if (!equipMode) {

                    if (auto item = player->getInv()->getItemOnSelectedRC(
                            player->getInv()->getCurrentRow(),
                            player->getInv()->getCurrentCol())) {
                        item->showInfo();
                    } else {
                        std::cout << "Empty slot\n";
                    }
                } else {

                    int s = player->getEquip()->getCursorSlot();
                    Item* sel = nullptr;
                    if      (s == 0) sel = player->getEquip()->getArmor();
                    else if (s == 1) sel = player->getEquip()->getRanged();
                    else             sel = player->getEquip()->getMelee();

                    if (sel) {
                        sel->showInfo();
                    } else {
                        std::string slotName = (s == 0) ? "Head (armor)"
                                               : (s == 1) ? "Left arm (ranged)"
                                                          :             "Right arm (melee)";
                        std::cout << slotName << ": Empty slot.\n";
                    }
                }
            }


            if (repairPending) {
                if (auto item = player->getInv()->getItemOnSelectedRC(
                        player->getInv()->getCurrentRow(),
                        player->getInv()->getCurrentCol())) {
                    std::cout << "~~~~~~~~~~~~~~~~~~~\n";
                    std::cout << "Repair: " << item->getName()
                              << "  " << item->getDurability() << " -> " << repairTarget << "/100"
                              << "\nPrice: " << repairCost << " coins\n";
                    std::cout << "[R] confrim\n";
                } else {

                    repairPending = false;
                }
            }

            if (upgradePending) {
                if (auto item = player->getInv()->getItemOnSelectedRC(
                        player->getInv()->getCurrentRow(),
                        player->getInv()->getCurrentCol())) {
                    std::cout << "~~~~~~~~~~~~~~~~~~~\n";
                    std::cout << "UPGRADE: " << item->getName()
                              << "  " << upgradeFrom << " -> " << upgradeTo
                              << "\nPrice: " << upgradeCost << " coins\n";
                    std::cout << "[P] confirm\n";
                } else {
                    upgradePending = false;
                }
            }

            std::cout << "\n";
            if (equipMode)
                std::cout << "[TAB] inventory  [A/D or arrow keys] move  [E] unequip  [I] toggle info\n";
            else
                std::cout << "[TAB] equipment  [WASD or arrow keys] move  [E] equip  [I] toggle info  [P] upgrade  [R] repair\n";

            userInput = int(getSingleChar());


            if (!equipMode) {
                secretCode += char(userInput);
                if (secretCode.length() > 20)
                    secretCode = secretCode.substr(1);


                if (secretCode.find("111") != std::string::npos && !used) {
                    if (auto item = player->getInv()->getItemOnSelectedRC(
                            player->getInv()->getCurrentRow(),
                            player->getInv()->getCurrentCol())) {
                        if (item->getTypeString() == "Diamond" && player->getMoney() >= 1000) {
                            item->setType(unseen);
                            player->setMoney(player->getMoney() - 1000);
                            secretCode = "";
                            used = true;
                            system(CLEAR);
                            std::cout << "SECRET KEY (cannot be used more than once): upgraded item type to unseen (cost - 1000 coins)\n";
                            getSingleChar();
                        } else { secretCode = ""; }
                    } else { secretCode = ""; }
                } else if (secretCode.find("111") != std::string::npos && used) {
                    secretCode = "";
                }


                if (secretCode.find("222") != std::string::npos && !used2) {
                    if (auto item = player->getInv()->getItemOnSelectedRC(
                            player->getInv()->getCurrentRow(),
                            player->getInv()->getCurrentCol())) {
                        if(item->getRarity() == common || item->getRarity() == uncommon || item->getRarity() == rare) {
                            secretCode = "";
                        }
                        else{
                            item->setRarity(unknown);
                            secretCode = "";
                            used2 = true;
                            system(CLEAR);
                            std::cout << "SECRET KEY (cannot be used more than once): upgraded item rarity to unknown\n";
                            getSingleChar();
                        }
                    } else { secretCode = ""; }
                } else if (secretCode.find("222") != std::string::npos && used2) {
                    secretCode = "";
                }


                if (secretCode.find("999") != std::string::npos && !used3) {
                    player->setMoney(player->getMoney() + 500);
                    secretCode = "";
                    used3 = true;
                    system(CLEAR);
                    std::cout << "SECRET KEY (cannot be used more than once): added 500 coins\n";
                    getSingleChar();
                } else if (secretCode.find("999") != std::string::npos && used3) {
                    secretCode = "";
                }
            }

            switch (userInput) {


            case '\t':
                repairPending = false;
                equipMode = !equipMode;
                break;


            case 'a':
                repairPending = false;
                if (equipMode) player->getEquip()->moveCursor(-1);
                else           player->getInv()->setCurrentCol(player->getInv()->getCurrentCol() - 1);
                break;
            case 'd':
                repairPending = false;
                if (equipMode) player->getEquip()->moveCursor(+1);
                else           player->getInv()->setCurrentCol(player->getInv()->getCurrentCol() + 1);
                break;
            case 'w':
                repairPending = false;
                if (!equipMode) player->getInv()->setCurrentRow(player->getInv()->getCurrentRow() - 1);
                break;
            case 's':
                repairPending = false;
                if (!equipMode) player->getInv()->setCurrentRow(player->getInv()->getCurrentRow() + 1);
                break;


            case 'e': case 'E':
                repairPending = false;
                if (equipMode) {
                    int s = player->getEquip()->getCursorSlot();
                    Item* slotItem = nullptr;
                    if      (s == 0) slotItem = player->getEquip()->getArmor();
                    else if (s == 1) slotItem = player->getEquip()->getRanged();
                    else             slotItem = player->getEquip()->getMelee();

                    if (!slotItem) {
                        continue;
                    } else if (!player->unequipToInventory()) {
                        system(CLEAR);
                        std::cout << "Inventory full!";
                        getSingleChar();
                    }
                } else {
                    player->equipFromInventory(
                        player->getInv()->getCurrentRow(),
                        player->getInv()->getCurrentCol()
                        );
                }
                break;


            case 'i':
                repairPending = false;
                showInfo = !showInfo;
                break;


            case 'p':
                repairPending = false;
                if (!equipMode) {
                    if (upgradePending) {
                        if (auto item = player->getInv()->getItemOnSelectedRC(
                                player->getInv()->getCurrentRow(),
                                player->getInv()->getCurrentCol())) {
                            if (player->getMoney() >= upgradeCost) {
                                player->setMoney(player->getMoney() - upgradeCost);
                                item->upgradeType();
                            }
                        }
                        upgradePending = false;
                    } else {
                        if (auto item = player->getInv()->getItemOnSelectedRC(
                                player->getInv()->getCurrentRow(),
                                player->getInv()->getCurrentCol())) {
                            std::string type = item->getTypeString();
                            int price = 0;
                            std::string to = "";
                            if      (type == "Wooden") { price = 20;  to = "Stone";   }
                            else if (type == "Stone")  { price = 50;  to = "Iron";    }
                            else if (type == "Iron")   { price = 120; to = "Gold";    }
                            else if (type == "Gold")   { price = 280; to = "Diamond"; }

                            if (price == 0) {
                            } else if (player->getMoney() < price) {
                            } else {
                                upgradeCost    = price;
                                upgradeFrom    = type;
                                upgradeTo      = to;
                                upgradePending = true;
                            }
                        }
                    }
                } else {
                    upgradePending = false;
                }
                break;


            case 'r':
                if (!equipMode) {
                    if (repairPending) {

                        if (auto item = player->getInv()->getItemOnSelectedRC(
                                player->getInv()->getCurrentRow(),
                                player->getInv()->getCurrentCol())) {
                            if (player->getMoney() >= repairCost) {
                                player->setMoney(player->getMoney() - repairCost);
                                item->setDurability(repairTarget);
                            }
                        }
                        repairPending = false;
                    } else {

                        if (auto item = player->getInv()->getItemOnSelectedRC(
                                player->getInv()->getCurrentRow(),
                                player->getInv()->getCurrentCol())) {

                            if (item->getDurability() < 100) {

                                int repairBase = 0;
                                switch (item->getType()) {
                                case wooden:  repairBase = 10;   break;
                                case stone:   repairBase = 25;   break;
                                case iron:    repairBase = 60;   break;
                                case gold:    repairBase = 150;  break;
                                case diamond: repairBase = 300;  break;
                                case unseen:  repairBase = 600; break;
                                default:      repairBase = 10;   break;
                                }

                                int missing   = 100 - item->getDurability();
                                int fullCost  = std::max(1, int(repairBase * missing / 100.0f));

                                if (player->getMoney() <= 0) {

                                    break;
                                } else if (player->getMoney() >= fullCost) {

                                    repairCost   = fullCost;
                                    repairTarget = 100;
                                } else {

                                    float ratio  = float(player->getMoney()) / float(fullCost);
                                    int canFix   = std::max(1, int(missing * ratio));
                                    repairTarget = item->getDurability() + canFix;
                                    repairCost   = player->getMoney();
                                }
                                repairPending = true;
                            }
                        }
                    }
                } else {

                    repairPending = false;
                }
                break;


            case KEY_BACK:
                state          = STATE_MENU;
                showInfo       = false;
                equipMode      = false;
                repairPending  = false;
                upgradePending = false;
                secretCode     = "";
                break;


            default:
                repairPending = false;
                break;
            }
        }

        // ===================== STORE =====================
        else if (state == STATE_STORE) {
            std::cout << "<===== Store =====>\n\n";
            store->display();
            std::cout << "\n\n\n";

            userInput = int(getSingleChar());
            switch (userInput) {
            case 'w': store->setCurrentRow(store->getCurrentRow() - 1); break;
            case 's': store->setCurrentRow(store->getCurrentRow() + 1); break;
            case 10: case 13: {
                auto item = store->getItemOnSelectedRC(store->getCurrentRow(), store->getCurrentCol());
                if (!item) break;
                if (item->getName() == "Buy") state = STATE_STORE_SHOP;
                else {
                    state      = STATE_STORE_SELL;
                    sellCursor = 0;
                }
                break;
            }
            case KEY_BACK: state = STATE_MENU; break;
            }
        }

        // ===================== SHOP (buy) =====================
        else if (state == STATE_STORE_SHOP) {
            std::cout << "<===== Shop =====>\n\n";
            std::cout << "Your current balance: " << player->getMoney() << "\n";
            shop->display();

            if (showPrice) {
                if (auto item = shop->getItemOnSelectedRC(shop->getCurrentRow(), shop->getCurrentCol())) {
                    std::cout << "~~~~~~~~~~~~~\n" << item->getName() << " price - " << item->getPrice() << "\n";
                }
            }

            userInput = int(getSingleChar());
            switch (userInput) {
            case 'w': shop->setCurrentRow(shop->getCurrentRow() - 1); break;
            case 's': shop->setCurrentRow(shop->getCurrentRow() + 1); break;
            case 'p': showPrice = !showPrice; break;
            case 'b': {
                auto src = shop->getItemOnSelectedRC(shop->getCurrentRow(), shop->getCurrentCol());
                if (!src) break;
                int price = src->getPrice();
                Item* newItem = new Item(src->getName(), src->getPrice(), src->getCategory());

                if (player->getMoney() >= price) {
                    if (player->getInv()->addItem(newItem)) {
                        player->setMoney(player->getMoney() - price);
                        system(CLEAR);
                        std::cout << "Successfully bought " << src->getName();
                    } else {
                        delete newItem;
                        system(CLEAR);
                        std::cout << "Cannot buy any more items, inventory is full";
                    }
                } else {
                    system(CLEAR);
                    std::cout << "Not enough funds to buy " << src->getName() << " (" << price << ")";
                    delete newItem;
                }
                getSingleChar();
                break;
            }
            case KEY_BACK:
                state     = STATE_STORE;
                showPrice = false;
                break;
            }
        }

        // ===================== SELL =====================
        else if (state == STATE_STORE_SELL) {
            system(CLEAR);
            std::cout << "<===== Sell =====>\n\n";
            std::cout << "Balance: " << player->getMoney() << "\n\n";

            // --- zbierz wszystkie itemy (inventory + equipment) do listy ---
            // kazdy wpis: wskaznik na item + czy jest wyposazone
            struct SellEntry {
                Item* item;
                bool  equipped;
                // skad pochodzi (zeby wiedziec jak usunac)
                // 0=inventory row/col, 1=armor, 2=ranged, 3=melee
                int   source;
                int   invRow;
                int   invCol;
            };

            std::vector<SellEntry> sellList;

            // inventory
            for (int i = 0; i < player->getInv()->getRows(); i++) {
                for (int j = 0; j < player->getInv()->getCols(); j++) {
                    Item* it = player->getInv()->getItems()[i][j];
                    if (it) {
                        sellList.push_back({it, false, 0, i, j});
                    }
                }
            }
            // equipment — armor
            if (player->getEquip()->getArmor())
                sellList.push_back({player->getEquip()->getArmor(),  true, 1, -1, -1});
            // equipment — ranged
            if (player->getEquip()->getRanged())
                sellList.push_back({player->getEquip()->getRanged(), true, 2, -1, -1});
            // equipment — melee
            if (player->getEquip()->getMelee())
                sellList.push_back({player->getEquip()->getMelee(),  true, 3, -1, -1});

            if (sellList.empty()) {
                std::cout << "No items to sell.\n\n";
                std::cout << "[BACKSPACE] back\n";
                userInput = int(getSingleChar());
                if (userInput == KEY_BACK) {
                    sellPending = false;
                    state = STATE_STORE;
                }
                continue;
            }

            // ogranicz kursor do rozmiaru listy
            if (sellCursor >= int(sellList.size())) sellCursor = int(sellList.size()) - 1;
            if (sellCursor < 0) sellCursor = 0;

            // --- wyswietl grid: max 4 kolumny, tyle wierszy ile trzeba ---
            const int SELL_COLS = 4;
            int totalItems = int(sellList.size());
            int rows = (totalItems + SELL_COLS - 1) / SELL_COLS;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < SELL_COLS; j++) {
                    int idx = i * SELL_COLS + j;
                    if (idx >= totalItems) {
                        std::cout << "     "; // puste miejsce dla wyrownania
                        continue;
                    }

                    bool selected = (idx == sellCursor);
                    Item* it = sellList[idx].item;
                    char  ch = char(std::toupper(it->getName()[0]));

                    if (selected) std::cout << ">[" << ch << "]<";
                    else          std::cout << " [" << ch << "] ";
                }
                std::cout << "\n";
            }

            // --- info o wybranym itemie ---
            std::cout << "~~~~~~~~~~~~~~~~~~~\n";
            Item* sel = sellList[sellCursor].item;
            sel->showInfo();
            std::cout << "Sell price: " << calculateSellPrice(sel) << " coins\n\n";

            if (sellPending) {
                std::cout << "[S] confirm\n";
            }

            userInput = int(getSingleChar());
            switch (userInput) {
            case 'a':
                sellPending = false;
                sellCursor--;
                if (sellCursor < 0) sellCursor = int(sellList.size()) - 1;
                break;
            case 'd':
                sellPending = false;
                sellCursor++;
                if (sellCursor >= int(sellList.size())) sellCursor = 0;
                break;
            case 's':
                if (sellPending) {
                    // drugie S — zatwierdz sprzedaz
                    SellEntry& entry = sellList[sellCursor];

                    // jesli wyposazone — najpierw odposaź (bez zwracania do inventory)
                    if (entry.equipped) {
                        int prevCursor = player->getEquip()->getCursorSlot();
                        int targetSlot = entry.source; // 1=armor->0, 2=ranged->1, 3=melee->2
                        int equipSlot  = targetSlot - 1; // przelicz: source 1->slot 0, 2->1, 3->2
                        while (player->getEquip()->getCursorSlot() != equipSlot)
                            player->getEquip()->moveCursor(1);
                        Item* unequipped = player->getEquip()->unequipSelected();
                        // nie oddawaj do inventory — zaraz usuwamy
                        while (player->getEquip()->getCursorSlot() != prevCursor)
                            player->getEquip()->moveCursor(1);
                        // unequipped == entry.item, usuwamy przez delete ponizej
                        player->setMoney(player->getMoney() + sellPrice);
                        delete unequipped;
                    } else {
                        // z inventory — removeItem robi delete
                        player->setMoney(player->getMoney() + sellPrice);
                        player->getInv()->removeItem(entry.invRow, entry.invCol);
                    }

                    sellPending = false;
                    sellCursor  = 0; // resetuj kursor po sprzedazy
                } else {
                    // pierwsze S — oblicz cene
                    sellPrice   = calculateSellPrice(sellList[sellCursor].item);
                    sellPending = true;
                }
                break;
            case KEY_BACK:
                sellPending = false;
                sellCursor  = 0;
                state = STATE_STORE;
                break;
            default:
                sellPending = false;
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
            std::cout << "For better user experience, please run this game in bigger screen view (so that everything fits in one screen, no scrolling needed)\n\n";
            std::cout << "\n<===== Navigation guide =====>\n\n";
            std::cout << "Movement:\n W, S, A, D or arrow keys\n\n";
            std::cout << "Inventory functions:\ntab- change select \n i - toggle info\n p - weapon upgrade\n r - repair item\n e - equip/unequip item";
            std::cout << "\n\nStore functions:\n p - toggle price\n b - buy\n s - sell\n\n\n";
            std::cout << "<===== Upgrade prices =====>\n\n";
            std::cout << " Wooden -> stone - 20\n";
            std::cout << " Stone -> iron - 50\n";
            std::cout << " Iron -> gold - 120\n";
            std::cout << " Gold -> Diamond - 280\n\n";
            std::cout << "\n<===== Repair prices =====>\n\n";
            std::cout << "Price for full repair (1-100)\n Wooden - 10\n Stone - 25\n Iron - 60\n Gold - 150\n Diamond - 300\n Unseen - 600\n";
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

