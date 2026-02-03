#ifndef INVENTORY_H
#define INVENTORY_H

#include "gridbase.h"

class Inventory : public GridBase
{
public:
    Inventory();
    void display() override;
};

#endif
