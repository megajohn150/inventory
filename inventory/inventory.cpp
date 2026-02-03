#include "inventory.h"
#include <cctype>

Inventory::Inventory() : GridBase(4, 4) {}

void Inventory::display()
{
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){

            if (i == currentRow && j == currentCol)
                std::cout << ">[";
            else
                std::cout << " [";

            if (items[i][j] == nullptr){
                std::cout << " ";
            } else {
                std::cout << char(std::toupper(items[i][j]->getName()[0]));
            }

            if (i == currentRow && j == currentCol)
                std::cout << "]<";
            else
                std::cout << "] ";
        }
        std::cout << "\n";
    }
}
