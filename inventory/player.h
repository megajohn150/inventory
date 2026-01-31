#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "inventory.h"

class Player
{
private:
    std::string name;
    Inventory* inv;
public:
    Player();
    Player(std::string name);
    ~Player();
    void setName(const std::string &newName);
    void setInv(Inventory *newInv);
    Inventory *getInv() const;
    std::string getName() const;
};

#endif // PLAYER_H
