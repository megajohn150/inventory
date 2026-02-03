#ifndef MENU_H
#define MENU_H

#include "gridbase.h"

class Menu : public GridBase
{
public:
    Menu();
    void display() override;
};

#endif
