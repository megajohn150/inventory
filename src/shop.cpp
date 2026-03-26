#include "shop.h"
#include <iomanip>

namespace Color {
const std::string RED     = "\033[91m";
const std::string GREEN   = "\033[92m";
const std::string YELLOW  = "\033[93m";
const std::string BLUE    = "\033[38;5;75m";
const std::string MAGENTA = "\033[95m";
const std::string CYAN    = "\033[96m";
const std::string WHITE   = "\033[97m";
const std::string BOLD    = "\033[1m";
const std::string GRAY = "\033[38;5;245m";
const std::string DARKGRAY = "\033[90m";
const std::string MIDGRAY = "\033[38;5;242m";
const std::string RESET   = "\033[0m";
}

Shop::Shop() : GridBase(15, 1) {}

void Shop::displayTemplate(std::string cat)
{
    for (int i = 0; i < rows; i++){
        if (items[i][0] && items[i][0]->getCategory() == cat){
            if (i == currentRow) std::cout << Color::BOLD << Color::WHITE << " > " << Color::RESET;
            else                 std::cout << "   ";

            if(i == currentRow){
                std::cout << Color::WHITE << Color::BOLD << std::left << std::setw(25) << items[i][0]->getName() << Color::RESET;
            }
            else{
                std::cout << std::left << std::setw(25) << items[i][0]->getName();
            }

            if (i == currentRow){
                std::cout<< Color::GRAY << "Price: " <<  Color::BOLD<< std::setw(8) << items[i][0]->getPrice() << Color::RESET << Color::GRAY;
                if (items[i][0]->getStock() == 0)
                    std::cout << Color::BOLD<< "OUT OF STOCK" << Color::RESET;
                else
                    std::cout << "Stock: " << Color::BOLD << items[i][0]->getStock() << Color::RESET;
            }

            std::cout << "\n";
        }
    }
}

void Shop::displayShop(int playerBalance)
{
    auto repeat = [](const std::string& s, int n) {
        std::string result;
        for (int i = 0; i < n; i++) result += s;
        return result;
    };
    std::string balance = "Balance: " +std::to_string(playerBalance);
    int total = 27;
    int totalleft = total - balance.length();
    int left = totalleft / 2;
    int right = totalleft - left;

    std::cout << Color::CYAN <<Color::BOLD<< "╔═══════════════════════════╗\n";
    std::cout << "║       " << Color::RESET << Color::BOLD
              << "BUY NEW ITEMS" << Color::RESET << Color::CYAN << Color::BOLD
              << "       ║\n";

    std::cout << "║"
              << repeat(" ", left)
              << Color::RESET << "Balance: " << Color::YELLOW << Color::BOLD << playerBalance << Color::RESET
              << Color::CYAN << Color::BOLD
              << repeat(" ", right)
              << "║\n";

    std::cout << "╚═══════════════════════════╝\n" << Color::RESET;


    std::cout << Color::MIDGRAY << "\n[ CLOSE RANGE WEAPONS ]\n" << Color::RESET;
    displayTemplate("close range weapons");
    std::cout << Color::MIDGRAY << "\n[ LONG RANGE WEAPONS ]\n" << Color::RESET;
    displayTemplate("long range weapons");
    std::cout << Color::MIDGRAY << "\n[ DEFENSIVE EQUIPMENT ]\n" << Color::RESET;
    displayTemplate("armor");
    std::cout << Color::MIDGRAY << "\n[ MEDKITS ]\n" << Color::RESET;
    displayTemplate("medkit");
    std::cout<< Color::MIDGRAY << "\n[ BACKPACKS ]\n" << Color::RESET;
    displayTemplate("backpack");
}

void Shop::display()
{
    std::cout << "";
}
