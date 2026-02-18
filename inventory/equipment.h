#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "item.h"
#include <string>

class Equipment
{
private:
    Item* armor;   // category: "armor"
    Item* melee;   // category: "close range weapons"
    Item* ranged;  // category: "long range weapons"

    // 0 = glowa (armor), 1 = lewa reka (ranged), 2 = prawa reka (melee)
    int cursorSlot;

public:
    Equipment();
    ~Equipment();

    // zwraca stary item (oddaj do inventory), nullptr jesli slot byl pusty
    Item* equipItem(Item* newItem);

    // unequip aktualnie wybranego slotu
    Item* unequipSelected();

    void moveCursor(int dir); // -1 lewo, +1 prawo

    int   getCursorSlot() const { return cursorSlot; }
    Item* getArmor()      const { return armor; }
    Item* getMelee()      const { return melee; }
    Item* getRanged()     const { return ranged; }

    // active = czy kursor jest aktywny (tryb equipment)
    void display(bool active) const;
};

#endif // EQUIPMENT_H
