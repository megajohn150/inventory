#include "menu.h"

Menu::Menu() : GridBase(5, 1) {}

void Menu::display()
{
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (i == currentRow && j == currentCol)
                std::cout << ">  ";

            if (items[i][j] != nullptr)
                std::cout << items[i][j]->getName();
        }

        if(i == 2)
            std::cout << "\n~~~~~~~~~~~~~\n";
        else
            std::cout << "\n";
    }
}
