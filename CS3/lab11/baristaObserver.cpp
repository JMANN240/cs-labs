#include <unordered_set>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <deque>
#include "drink.hpp"

using std::unordered_set;
using std::cout; using std::endl;
using std::string; using std::to_string;
using std::rand;
using std::deque;

class Customer {
public:
   Customer(const string&, class Barista*);
   bool checkOrder();
   string getName() const { return name_; }
   Drink* getOrder() const {return order_; }
   void recieveOrder() { hasOrder_ = true; }
   bool hasOrder() { return hasOrder_; }
private:
   string name_;
   class Barista* b_;
   Drink* order_;
   bool hasOrder_ = false;
}; 

class Barista {
public:
    Barista() {}
    void announceOrder();
    void takeOrder(Customer* c) { customers_.insert(c); }
    Drink* getCurrentOrder() const { return currentOrder_; }
    size_t numOfCustomers() const { return customers_.size(); }
private:
    std::unordered_set<Customer*> customers_;
    Drink* currentOrder_ = nullptr;
};

void Barista::announceOrder() {
    currentOrder_ = (*customers_.begin())->getOrder();
    cout << endl << "Barista: Order up! " << currentOrder_->getName() << '!' << endl;
    for (unordered_set<Customer*>::iterator it = customers_.begin(); it != customers_.end();) {
        if ((*it)->checkOrder()) {
            it = customers_.erase(it);
        } else {
            ++it;
        }
    }
}

Customer::Customer(const string &name, Barista* b): name_(name), b_(b) {
    int size = rand() % 3;
    switch (size) {
        case 0:
            order_ = new Coffee(DrinkType::small, size+1); break;
        case 1:
            order_ = new Coffee(DrinkType::medium, size+2); break;
        case 2:
            order_ = new Coffee(DrinkType::large, size+3); break;
    }

    int topping;
    int nToppings = 0;
    do {
        topping = rand() % 5;
        switch (topping) {
            case 0:
                order_ = new WithSprinkles(order_);
                break;
            case 1:
                order_ = new WithCaramel(order_);
                break;
            case 2:
                order_ = new WithMilkFoam(order_);
                break;
            case 3:
                order_ = new WithIce(order_);
                break;
        }
        nToppings++;
    } while (topping != 4 && nToppings < 5);
    cout << name_ << ": I would like a " << order_->getName() << endl;
}

bool Customer::checkOrder() {
    cout << name_ << ": Oh boy! I hope it is mine! ";
	if (b_->getCurrentOrder() == order_) {
        cout <<"It is! Thanks!" << endl;
        recieveOrder();
    } else {
        cout << "Nope, maybe next time." << endl;
    }
    return b_->getCurrentOrder() == order_;
}

int main() {
    srand(time(nullptr));
    Barista barista;
    int r;
    barista.takeOrder(new Customer("Customer " + to_string(barista.numOfCustomers()), &barista));
    do {
        r = rand() % 2;
        if (r) {
            barista.announceOrder();
        } else {
            barista.takeOrder(new Customer("Customer " + to_string(barista.numOfCustomers()), &barista));
        }
    } while (barista.numOfCustomers() != 0);
}
