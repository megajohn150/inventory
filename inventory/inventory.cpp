#include "inventory.h"

int Inventory::getRows() const
{
    return rows;
}

void Inventory::setRows(int newRows)
{
    rows = newRows;
}

int Inventory::getCols() const
{
    return cols;
}

void Inventory::setCols(int newCols)
{
    cols = newCols;
}

Item ***Inventory::getItems() const
{
    return items;
}

Item *Inventory::getItemOnSelectedRC(int row, int col)
{
    return items[row][col];
}

void Inventory::setItems(Item ***newItems)
{
    items = newItems;
}

int Inventory::getCurrentRow() const
{
    return currentRow;
}

void Inventory::setCurrentRow(int newCurrentRow)
{
    if (newCurrentRow >= 0 && newCurrentRow < rows){
        currentRow = newCurrentRow;
    } else if (newCurrentRow < 0) {
        currentRow = rows - 1;
    } else {
        currentRow = 0;
    }
}

int Inventory::getCurrentCol() const
{
    return currentCol;
}

void Inventory::setCurrentCol(int newCurrentCol)
{
    if (newCurrentCol >= 0 && newCurrentCol < cols){
        currentCol = newCurrentCol;
    } else if (newCurrentCol < 0) {
        currentCol = cols - 1;
    } else {
        currentCol = 0;
    }
}

Inventory::Inventory()
{
    rows = 4;
    cols = 4;
    currentRow = 0;
    currentCol = 0;

    items = new Item**[rows];
    for(int i = 0; i < rows; i++) {
        items[i] = new Item*[cols];
    }
}

Inventory::~Inventory()
{
    this->clear();
    for(int i = 0; i < rows; i++) {
        delete[] items[i];
    }
    delete[] items;
}

void Inventory::clear()
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


void Inventory::display()
{
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){

            // if (items[rows][cols]->getDurability() >= 0){
            //     delete items[rows][cols];
            //     items[rows][cols] = nullptr;
            // }

            if (i == currentRow && j == currentCol){
                std::cout << ">[";
            } else{
                std::cout << " [";
            }
            if (items[i][j] == nullptr){
                std::cout << " ";
            } else {
                std::cout << char(toupper(items[i][j]->getName()[0]));
            }

            if (i == currentRow && j == currentCol){
                std::cout << "]<";
            } else{
                std::cout << "] ";
            }
        }
        std::cout << "\n";
    }
}

bool Inventory::addItem(Item *item)
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

bool Inventory::removeItem(int row, int col)
{
    if (items[row][col] != nullptr){
        delete items[row][col];
        items[row][col] = nullptr;
        return true;
    }
    return false;
}

bool Inventory::moveTo(int oldRow, int oldCol, int newRow, int newCol)
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

void Inventory::sort()
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

