#include "store.h"

Store::Store() : GridBase(2, 1) {}

void Store::display()
{
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (i == currentRow && j == currentCol)
                std::cout << ">  ";

            if (items[i][j] != nullptr)
                std::cout << items[i][j]->getName();
        }
        std::cout << "\n";
    }
}
