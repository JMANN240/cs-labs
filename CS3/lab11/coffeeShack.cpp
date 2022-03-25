#include "drink.hpp"
#include <iostream>
#include <string>

using std::cout; using std::cin; using std::endl;
using std::string;

int main() {
    char size;
    do {
        cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
        cin >> size;
    } while (size != 'l' && size != 'm' && size != 's');
    Drink* coffee;
    switch (size) {
        case 'l':
            coffee = new Coffee(DrinkType::large, 3.0);
            break;
        case 'm':
            coffee = new Coffee(DrinkType::medium, 2.0);
            break;
        case 's':
            coffee = new Coffee(DrinkType::small, 1.0);
            break;
    }
    char topping;
    do {
        cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? ";
        cin >> topping;
        switch (topping) {
            case 's':
                coffee = new WithSprinkles(coffee);
                break;
            case 'c':
                coffee = new WithCaramel(coffee);
                break;
            case 'f':
                coffee = new WithMilkFoam(coffee);
                break;
            case 'i':
                coffee = new WithIce(coffee);
                break;
        }
    } while (topping != 'n');
    //cout << sprink->getName() << " | " << sprink->getPrice() << endl;
    cout << "Can I get your name? ";
    string name;
    cin >> name;
    cout << endl;
    cout << name << ", your " << coffee->getName() << " is ready. It will be $" << coffee->getPrice() << ", please." << endl;
}