#include "shop.h"

int Shop::getRows() const
{
    return rows;
}

void Shop::setRows(int newRows)
{
    rows = newRows;
}

int Shop::getCols() const
{
    return cols;
}

void Shop::setCols(int newCols)
{
    cols = newCols;
}

Item ***Shop::getItems() const
{
    return items;
}

Item *Shop::getItemOnSelectedRC(int row, int col)
{
    return items[row][col];
}

void Shop::setItems(Item ***newItems)
{
    items = newItems;
}

int Shop::getCurrentRow() const
{
    return currentRow;
}

void Shop::setCurrentRow(int newCurrentRow)
{
    if (newCurrentRow >= 0 && newCurrentRow < rows){
        currentRow = newCurrentRow;
    } else if (newCurrentRow < 0) {
        currentRow = rows - 1;
    } else {
        currentRow = 0;
    }
}

int Shop::getCurrentCol() const
{
    return currentCol;
}

void Shop::setCurrentCol(int newCurrentCol)
{
    if (newCurrentCol >= 0 && newCurrentCol < cols){
        currentCol = newCurrentCol;
    } else if (newCurrentCol < 0) {
        currentCol = cols - 1;
    } else {
        currentCol = 0;
    }
}

Shop::Shop()
{
    rows = 10;
    cols = 1;
    currentRow = 0;
    currentCol = 0;

    items = new Item**[rows];
    for(int i = 0; i < rows; i++) {
        items[i] = new Item*[cols];
    }
}

Shop::~Shop()
{
    this->clear();
    for(int i = 0; i < rows; i++) {
        delete[] items[i];
    }
    delete[] items;
}

void Shop::clear()
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


void Shop::display()
{
    // close range weapons
    // long range weapons
    // defensive equipment
    std::cout << "~~~~~~~~~~~~~\nClose range weapons: \n";
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(items[i][j]->getCategory() == "close range weapons"){
                if (i == currentRow && j == currentCol){
                    std::cout << " >  ";
                }
                else{
                    std::cout << " ";
                }
                std::cout << items[i][j]->getName();
                std::cout << "\n";
            }
        }

    }
    std::cout << "~~~~~~~~~~~~~\nLong range weapons: \n";
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(items[i][j]->getCategory() == "long range weapons"){
                if (i == currentRow && j == currentCol){
                    std::cout << " >  ";
                }
                else{
                    std::cout << " ";
                }
                std::cout << items[i][j]->getName();
                std::cout << "\n";
            }
        }
    }
    std::cout << "~~~~~~~~~~~~~\nDefensive equipment: \n";
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(items[i][j]->getCategory() == "defensive equipment"){
                if (i == currentRow && j == currentCol){
                    std::cout << " >  ";
                }
                else{
                    std::cout << " ";
                }
                std::cout << items[i][j]->getName();
                std::cout << "\n";
            }

        }
    }
}

bool Shop::addItem(Item *item)
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

bool Shop::removeItem(int row, int col)
{
    if (items[row][col] != nullptr){
        delete items[row][col];
        items[row][col] = nullptr;
        return true;
    }
    return false;
}

bool Shop::moveTo(int oldRow, int oldCol, int newRow, int newCol)
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

void Shop::sort()
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
