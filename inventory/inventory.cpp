#include "inventory.h"
#include <cctype>

Inventory::Inventory() : GridBase(4, 4) {}

void Inventory::display(Equipment* eq, bool equipMode)
{
    // ---- GRID 4x4 ----
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool selected = !equipMode && (i == currentRow && j == currentCol);

            if (selected) std::cout << ">[";
            else          std::cout << " [";

            if (items[i][j] == nullptr)
                std::cout << " ";
            else
                std::cout << char(std::toupper(items[i][j]->getName()[0]));

            if (selected) std::cout << "]<";
            else          std::cout << "] ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    if (eq)
        eq->display(equipMode);
    else {
        std::cout << "         [ ]\n";
        std::cout << "     [ ][   ][ ]\n";
        std::cout << "     { }[   ]{ }\n";
        std::cout << "        [ | ]\n";
        std::cout << "        [ | ]\n";
    }
}

void Inventory::clearInv(Equipment* eq)
{
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            removeItem(i,j);
        }
    }
    if(eq){
        eq->clear();
    }
}
