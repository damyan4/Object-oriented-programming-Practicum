
#include <iostream>
#include <fstream>
using std::cin;
using std::cout;

namespace GlobalConstants {
    constexpr size_t NAME_SIZE = 50;
    constexpr size_t PHONE_SIZE = 20;
    constexpr size_t ADDRESS_SIZE = 100;
};
enum class PizzaType {
    margheritta,
    calcone,
    buratta
};
enum class PizzaSize {
    S,
    M,
    L
};
struct Pizza {
    PizzaType type;
    PizzaSize size;
    double price = 0;
};
struct PizzaOrder {
    char name[GlobalConstants::NAME_SIZE] = "";
    char phone[GlobalConstants::PHONE_SIZE] = "";
    char address[GlobalConstants::ADDRESS_SIZE] = "";
    double total_price = 0;
    Pizza pizzas[10];
    size_t pizza_count = 0;
};



void writeDataInFile(std::ofstream& ofs,const PizzaOrder& order)
{
    ofs.write((const char*)&order, sizeof(order));
}
void saveInFile(const char* file, PizzaOrder* orders, size_t orders_count)
{
    std::ofstream ofs(file, std::ios::binary | std::ios::out);
    if (!ofs.is_open())
        return;

    for (size_t i = 0; i < orders_count; i++)
    {
        writeDataInFile(ofs, orders[i]);
    }
    ofs.close();
}
void readDataFromFile(std::ifstream& ifs)
{
    PizzaOrder ord;
    ifs.read((char*)&ord, sizeof(ord));
    cout << ord.name << " " << ord.phone << " " << ord.address << " "
        << ord.total_price << " " << std::endl; 
    //pizza print
}
void readfromFile(const char* file, const size_t orders_count)
{
    std::ifstream ifs(file, std::ios::binary | std::ios::in);
    if (!ifs.is_open())
        return;

    for (size_t i = 0; i < orders_count; i++)
    {
        readDataFromFile(ifs);
    }
        

}
int main()
{
    Pizza p = { PizzaType::buratta, PizzaSize::M, 10.99 };
    Pizza p1[] = { {PizzaType::buratta, PizzaSize::L, 14.99},
                   {PizzaType::margheritta, PizzaSize::L, 13.99 },
                    PizzaType::calcone, PizzaSize::S, 9.99 };
    
    size_t size = 1;
    PizzaOrder orders[2] = { {"Toni", "0882666578", "Qne Sandanski 1",12.99,p},
                             "Gosho", "0888433232", "Hadzhi Dimitar 100", 34.67, *p1};
    saveInFile("order.dat", orders, 2);
    readfromFile("order.dat", 2);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
