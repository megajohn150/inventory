#include "menu.h"

int Menu::getRows() const
{
    return rows;
}

void Menu::setRows(int newRows)
{
    rows = newRows;
}

int Menu::getCols() const
{
    return cols;
}

void Menu::setCols(int newCols)
{
    cols = newCols;
}

Item ***Menu::getItems() const
{
    return items;
}

Item *Menu::getItemOnSelectedRC(int row, int col)
{
    return items[row][col];
}

void Menu::setItems(Item ***newItems)
{
    items = newItems;
}

int Menu::getCurrentRow() const
{
    return currentRow;
}

void Menu::setCurrentRow(int newCurrentRow)
{
    if (newCurrentRow >= 0 && newCurrentRow < rows){
        currentRow = newCurrentRow;
    } else if (newCurrentRow < 0) {
        currentRow = rows - 1;
    } else {
        currentRow = 0;
    }
}

int Menu::getCurrentCol() const
{
    return currentCol;
}

void Menu::setCurrentCol(int newCurrentCol)
{
    if (newCurrentCol >= 0 && newCurrentCol < cols){
        currentCol = newCurrentCol;
    } else if (newCurrentCol < 0) {
        currentCol = cols - 1;
    } else {
        currentCol = 0;
    }
}

Menu::Menu()
{
    rows = 4;
    cols = 1;
    currentRow = 0;
    currentCol = 0;

    items = new Item**[rows];
    for(int i = 0; i < rows; i++) {
        items[i] = new Item*[cols];
    }
}

Menu::~Menu()
{
    this->clear();
    for(int i = 0; i < rows; i++) {
        delete[] items[i];
    }
    delete[] items;
}

void Menu::clear()
{
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (items[i][j] != nullptr){
                delete items[i][j];
                items[i][j] = nullptr;
            }
        }
    }
}


void Menu::display()
{
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (i == currentRow && j == currentCol){
                std::cout << ">  ";
            }
            else{
                std::cout << "";
            }
            std::cout << items[i][j]->getName();
        }
        if(i == 2){
            std::cout << "\n~~~~~~~~~~~~~\n";
        }
        else{
            std::cout << "\n";
        }
    }
}

bool Menu::addItem(Item *item)
{
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (items[i][j] == nullptr){
                items[i][j] = item;
                return true;
            }
        }
    }
    return false;
}

bool Menu::removeItem(int row, int col)
{
    if (items[row][col] != nullptr){
        delete items[row][col];
        items[row][col] = nullptr;
        return true;
    }
    return false;
}

bool Menu::moveTo(int oldRow, int oldCol, int newRow, int newCol)
{
    if (oldRow < 0 || oldRow >= rows || oldCol < 0 || oldCol >= cols ||
        newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
        return false;
    }

    if (items[oldRow][oldCol] == nullptr) {
        return false;
    }

    if (items[newRow][newCol] != nullptr) {
        Item* temp = items[oldRow][oldCol];
        items[oldRow][oldCol] = items[newRow][newCol];
        items[newRow][newCol] = temp;
    } else {
        items[newRow][newCol] = items[oldRow][oldCol];
        items[oldRow][oldCol] = nullptr;
    }
    return true;
}

void Menu::sort()
{
    std::vector<Item*> allItems;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (items[i][j] != nullptr){
                allItems.push_back(items[i][j]);
                items[i][j] = nullptr;
            }
        }
    }

    for (Item* item : allItems) {
        addItem(item);
    }
}
