#ifndef SHOP_H
#define SHOP_H
#include "item.h"
#include <iostream>
#include <vector>
class Shop
{
private:
    int rows;
    int cols;
    Item*** items;
    int currentRow;
    int currentCol;
public:
    Shop();
    ~Shop();
    void clear();
    void display();
    bool addItem(Item* item);
    bool removeItem(int row, int col);
    bool moveTo(int oldRow, int oldCol, int newRow, int newCol);
    void sort();


    // getters & setters
    int getRows() const;
    void setRows(int newRows);
    int getCols() const;
    void setCols(int newCols);
    Item ***getItems() const;
    Item *getItemOnSelectedRC(int row, int col);
    void setItems(Item ***newItems);
    int getCurrentRow() const;
    void setCurrentRow(int newCurrentRow);
    int getCurrentCol() const;
    void setCurrentCol(int newCurrentCol);


};

#endif // INVENTORY_H
