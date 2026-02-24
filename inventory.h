#ifndef INVENTORY_H
#define INVENTORY_H
#include "gridbase.h"
#include "equipment.h"

class Inventory : public GridBase
{
private:
    bool hasSmallBackpack = false;
    bool hasLargeBackpack = false;

    void expandCols(int addCols);

public:
    Inventory();

    bool addSmallBackpack();  // false = juz ma
    bool addLargeBackpack();  // false = juz ma

    bool getHasSmallBackpack() const { return hasSmallBackpack; }
    bool getHasLargeBackpack() const { return hasLargeBackpack; }

    void display(Equipment* eq = nullptr, bool equipMode = false);
    void display() override { display(nullptr, false); }
    void clearInv(Equipment* eq);
};

#endif // INVENTORY_H
