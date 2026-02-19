#include "shop.h"

Shop::Shop() : GridBase(10, 1) {}

void Shop::display()
{
    std::cout << "~~~~~~~~~~~~~\nClose range weapons:\n";
    for (int i = 0; i < rows; i++){
        if (items[i][0] && items[i][0]->getCategory() == "close range weapons"){
            if (i == currentRow) std::cout << " > ";
            std::cout << items[i][0]->getName() << "\n";
        }
    }

    std::cout << "~~~~~~~~~~~~~\nLong range weapons:\n";
    for (int i = 0; i < rows; i++){
        if (items[i][0] && items[i][0]->getCategory() == "long range weapons"){
            if (i == currentRow) std::cout << " > ";
            std::cout << items[i][0]->getName() << "\n";
        }
    }

    std::cout << "~~~~~~~~~~~~~\nDefensive equipment:\n";
    for (int i = 0; i < rows; i++){
        if (items[i][0] && items[i][0]->getCategory() == "armor"){
            if (i == currentRow) std::cout << " > ";
            std::cout << items[i][0]->getName() << "\n";
        }
    }
}
