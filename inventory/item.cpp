#include "item.h"
#include "random.h"

std::string Item::getName() const
{
    return name;
}

void Item::setName(const std::string &newName)
{
    name = newName;
}

Rarity Item::getRarity() const
{
    return rarity;
}

void Item::setRarity(Rarity newRarity)
{
    rarity = newRarity;
}

void Item::upgradeType()
{
    switch (this->type) {
    case wooden:
        this->type = stone;
        std::cout << "Successfully upgraded " << this->name << " from wooden to stone!";
        break;
    case stone:
        this->type = iron;
        std::cout << "Successfully upgraded " << this->name << " from stone to iron!";
        break;
    case iron:
        this->type = gold;
        std::cout << "Successfully upgraded " << this->name << " from iron to gold!";
        break;
    case gold:
        this->type = diamond;
        std::cout << "Successfully upgraded " << this->name << " from gold to diamond!";
        break;
    case diamond:
        std::cout << "Cannot upgrade item, its already diamond";
        break;
    default:
        std::cout << "Cannot upgrade item";
        break;
    }
}

int Item::getDurability() const
{
    return durability;
}

void Item::setDurability(int newDurability)
{
    durability = newDurability;
}



int Item::getPrice() const
{
    return price;
}

void Item::setPrice(int newPrice)
{
    price = newPrice;
}


void Item::use()
{
    int dmg = 0;

    switch (this->type)
    {
    case wooden:
        dmg = Random::range(1, 10);
        break;
    case stone:
        dmg = Random::range(1, 8);
        break;
    case iron:
        dmg = Random::range(1, 6);
        break;
    case gold:
        dmg = Random::range(1, 4);
        break;
    case diamond:
        dmg = Random::range(1, 2);
        break;
    default:
        return;
    }

    if (this->getDurability() > 0)
        this->setDurability(this->getDurability() - dmg);
}



void Item::showInfo()
{
    // dodac showInfo dla i
    std::cout << "Item - " << Item::getTypeString() << " " <<this->name << " (" << Item::getRarityString()<<")" << "\n";
    std::cout << "Price - " << this->price << "\n";
    std::cout << "Durability - " << this->durability << "/100 \n";
}

std::string Item::getRarityString()
{
    switch (this->rarity) {
    case common:
        return "common";
        break;
    case uncommon:
        return "uncommon";
        break;
    case rare:
        return "rare";
        break;
    case epic:
        return "epic";
        break;
    case legendary:
        return "legendary";
        break;
    case unknown:
        return "unknown";
        break;
    default:
        return "common";
        break;
    }
}

std::string Item::getTypeString()
{
    switch (this->type) {
    case wooden:
        return "Wooden";
        break;
    case stone:
        return "Stone";
        break;
    case iron:
        return "Iron";
        break;
    case gold:
        return "Gold";
        break;
    case diamond:
        return "Diamond";
        break;
    default:
        return "Wooden";
        break;
    }
}

std::string Item::getCategory() const
{
    return category;
}

void Item::setCategory(const std::string &newCategory)
{
    category = newCategory;
}

Item::Item() {
    name = "Stick";
    price = 1;
    durability = 100;
    rarity = common;

}

Item::Item(const std::string &name, int price, const std::string &category)
    : name(name),
    durability(100),
    price(price),
    category(category)
{
    int randNum = Random::range(1,100);
    if(randNum <= 50) {
        rarity = common;
    }
    else if(randNum > 50 && randNum <= 78) {
        rarity = uncommon;
    }
    else if(randNum > 78 && randNum <= 92) {
        rarity = rare;
    }
    else if(randNum > 92 && randNum <= 98) {
        rarity = epic;
    }
    else {
        rarity = legendary;
    }
    type = wooden;
}
