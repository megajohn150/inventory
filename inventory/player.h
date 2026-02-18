#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "inventory.h"
#include "equipment.h"

class Player
{
private:
    std::string name;
    int money;
    Inventory* inv;
    Equipment* equip;

public:
    Player();
    Player(std::string name);
    ~Player();

    // equip item z gridu (row/col = pozycja kursora)
    // zwraca false jesli brak itemu lub nieznana kategoria
    bool equipFromInventory(int row, int col);

    // unequip wybranego slotu z sylwetki, wraca na grid
    // zwraca false jesli slot pusty lub inventory pelne
    bool unequipToInventory();

    // settery / gettery
    void       setName(const std::string& newName);
    std::string getName() const;
    int        getMoney() const;
    void       setMoney(int newMoney);
    void       setInv(Inventory* newInv);
    Inventory* getInv()   const;
    Equipment* getEquip() const;
};

#endif // PLAYER_H
