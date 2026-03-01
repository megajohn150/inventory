#ifndef SHOP_H
#define SHOP_H

#include "gridbase.h"

class Shop : public GridBase
{
public:
    Shop();
    void display() override;
    void displayTemplate(std::string cat);
    std::vector<int> stock;
private:
    void decreaseStock(std::string );
};

#endif
