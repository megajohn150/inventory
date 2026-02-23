#include "inventory.h"
#include <cctype>

Inventory::Inventory() : GridBase(4, 4) {}

void Inventory::expandCols(int addCols)
{
    int newCols = cols + addCols;

    Item*** newItems = new Item**[rows];
    for (int i = 0; i < rows; i++) {
        newItems[i] = new Item*[newCols];
        for (int j = 0; j < newCols; j++) {
            if (j < cols)
                newItems[i][j] = items[i][j];
            else
                newItems[i][j] = nullptr;
        }
        delete[] items[i];
    }
    delete[] items;

    items = newItems;
    cols  = newCols;
}

bool Inventory::addSmallBackpack()
{
    if (hasSmallBackpack) return false;
    hasSmallBackpack = true;
    expandCols(1);
    return true;
}

bool Inventory::addLargeBackpack()
{
    if (hasLargeBackpack) return false;
    hasLargeBackpack = true;
    expandCols(2);
    return true;
}

void Inventory::display(Equipment* eq, bool equipMode)
{

    int baseEnd  = 4;
    int smallEnd = hasSmallBackpack ? baseEnd + 1 : baseEnd;
    // int largeEnd = hasLargeBackpack ? smallEnd + 2 : smallEnd;
    if (hasSmallBackpack || hasLargeBackpack) {

        std::cout << "                    ";
        if (hasSmallBackpack) {
            std::cout << "    SBP ";
        }
        if (hasLargeBackpack) {
            std::cout << "       BBP    ";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == baseEnd && hasSmallBackpack)
                std::cout << "   ";
            if (j == smallEnd && hasLargeBackpack)
                std::cout << "   ";

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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            removeItem(i, j);
        }
    }
    if (eq) {
        eq->clear();
    }
}
