#ifndef INVENTORY_H
#define INVENTORY_H
#include "gridbase.h"
#include "equipment.h"

class Inventory : public GridBase
{
private:
    bool hasSmallBackpack = false;
    bool hasLargeBackpack = false;

    void expandCols(int addCols);

public:
    Inventory();
    int levenshteinDistance(std::string firstString, std::string secondString);
    std::pair<int, int> searchNames(std::string target);
    bool addSmallBackpack();
    bool addLargeBackpack();

    bool getHasSmallBackpack() const { return hasSmallBackpack; }
    bool getHasLargeBackpack() const { return hasLargeBackpack; }

    void display(Equipment* eq = nullptr, bool equipMode = false);
    void display() override { display(nullptr, false); }
    void clearInv(Equipment* eq);
    void cleanUp();
    bool invNotEmpCheckup();
};

#endif // INVENTORY_H
