#include "drink.hpp"
#include <string>
#include <iostream>

using std::string;
using std::cout; using std::endl;

double Drink::getPrice() const { return price_; };
string Drink::getName() const { 
    switch (type_) {
        case DrinkType::large:
            return "large";
        case DrinkType::medium:
            return "medium";
        case DrinkType::small:
            return "small";
    }
    return "none";
};

bool Drink::nameContains(string search) const {
    string name = getName();
    //cout << "looking for " << search << endl;
    for (int i = 0; i < name.size() - search.size() + 1; ++i) {
        //cout << name.substr(i, search.size()) << endl;
        if (name.substr(i, search.size()) == search) {
            //cout << "found " << search << endl;
            return true;
        }
    }
    //cout << "no " << search << endl;
    return false;
}

double Coffee::getPrice() const { return Drink::getPrice(); };
string Coffee::getName() const { return Drink::getName() + " coffee"; };

double WithSprinkles::getPrice() const { return wrapped_->getPrice() + 0.5; };
string WithSprinkles::getName() const {
    string wrapped_name = wrapped_->getName();
    size_t last_space = wrapped_name.find_last_of(' ');
    string last_token = wrapped_name.substr(last_space+1, string::npos);
    return wrapped_name + (last_token == "coffee" ? " with " : ", ") + "sprinkles"; 
};

double WithCaramel::getPrice() const { return wrapped_->getPrice() + 0.2; };
string WithCaramel::getName() const {
    string wrapped_name = wrapped_->getName();
    size_t last_space = wrapped_name.find_last_of(' ');
    string last_token = wrapped_name.substr(last_space+1, string::npos);
    return wrapped_name + (last_token == "coffee" ? " with " : ", ") + "caramel"; 
};

double WithMilkFoam::getPrice() const { return wrapped_->getPrice() + 0.4; };
string WithMilkFoam::getName() const {
    string wrapped_name = wrapped_->getName();
    size_t last_space = wrapped_name.find_last_of(' ');
    string last_token = wrapped_name.substr(last_space+1, string::npos);
    return wrapped_name + (last_token == "coffee" ? " with " : ", ") + "foam"; 
};

double WithIce::getPrice() const { return wrapped_->getPrice() + 0.1; };
string WithIce::getName() const {
    string wrapped_name = wrapped_->getName();
    size_t last_space = wrapped_name.find_last_of(' ');
    string last_token = wrapped_name.substr(last_space+1, string::npos);
    return wrapped_name + (last_token == "coffee" ? " with " : ", ") + "ice"; 
};