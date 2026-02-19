#ifndef INVENTORY_H
#define INVENTORY_H
#include "gridbase.h"
#include "equipment.h"

class Inventory : public GridBase
{
public:
    Inventory();

    void display(Equipment* eq = nullptr, bool equipMode = false);

    void display() override { display(nullptr, false); }
};

#endif // INVENTORY_H
