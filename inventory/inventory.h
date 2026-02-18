#ifndef INVENTORY_H
#define INVENTORY_H
#include "gridbase.h"
#include "equipment.h"

class Inventory : public GridBase
{
public:
    Inventory();
    // eq = nullptr wyswietla sam grid bez ludzika
    // equipMode = czy kursor jest aktywny na sylwetce
    void display(Equipment* eq = nullptr, bool equipMode = false);

    // stara sygnaatura override — wywola display(nullptr, false)
    void display() override { display(nullptr, false); }
};

#endif // INVENTORY_H
