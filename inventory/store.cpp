#include "store.h"

int Store::getRows() const
{
    return rows;
}

void Store::setRows(int newRows)
{
    rows = newRows;
}

int Store::getCols() const
{
    return cols;
}

void Store::setCols(int newCols)
{
    cols = newCols;
}

Item ***Store::getItems() const
{
    return items;
}

Item *Store::getItemOnSelectedRC(int row, int col)
{
    return items[row][col];
}

void Store::setItems(Item ***newItems)
{
    items = newItems;
}

int Store::getCurrentRow() const
{
    return currentRow;
}

void Store::setCurrentRow(int newCurrentRow)
{
    if (newCurrentRow >= 0 && newCurrentRow < rows){
        currentRow = newCurrentRow;
    } else if (newCurrentRow < 0) {
        currentRow = rows - 1;
    } else {
        currentRow = 0;
    }
}

int Store::getCurrentCol() const
{
    return currentCol;
}

void Store::setCurrentCol(int newCurrentCol)
{
    if (newCurrentCol >= 0 && newCurrentCol < cols){
        currentCol = newCurrentCol;
    } else if (newCurrentCol < 0) {
        currentCol = cols - 1;
    } else {
        currentCol = 0;
    }
}

Store::Store()
{
    rows = 2;
    cols = 1;
    currentRow = 0;
    currentCol = 0;

    items = new Item**[rows];
    for(int i = 0; i < rows; i++) {
        items[i] = new Item*[cols];
    }
}

Store::~Store()
{
    this->clear();
    for(int i = 0; i < rows; i++) {
        delete[] items[i];
    }
    delete[] items;
}

void Store::clear()
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

void Store::display()
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
        std::cout << "\n";
    }
}

bool Store::addItem(Item *item)
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

bool Store::removeItem(int row, int col)
{
    if (items[row][col] != nullptr){
        delete items[row][col];
        items[row][col] = nullptr;
        return true;
    }
    return false;
}

bool Store::moveTo(int oldRow, int oldCol, int newRow, int newCol)
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

void Store::sort()
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
