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
   Customer(const string&);
   bool checkOrder();
   string getName() const { return name_; }
   Drink* getOrder() const {return order_; }
   void recieveOrder() { hasOrder_ = true; }
   bool hasOrder() { return hasOrder_; }
   void setBarista(class Barista* b) { b_ = b; }
private:
   string name_;
   class Barista* b_;
   Drink* order_;
   bool hasOrder_ = false;
}; 

class Barista {
public:
    Barista(Barista* successor = nullptr, string rank = ""): successor_(successor), rank_(rank) {}
    void announceOrder();
    virtual void takeOrder(Customer* c);
    Drink* getCurrentOrder() const { return currentOrder_; }
    size_t numOfCustomers() const {
        return customers_.size();
    }
    string getRank() const { return rank_; }
protected:
    std::unordered_set<Customer*> customers_;
    Drink* currentOrder_ = nullptr;
private:
    Barista* successor_;
    string rank_;
};

void Barista::takeOrder(Customer* c) {
    if (successor_ != nullptr) {
        successor_->takeOrder(c);
    } else {
        cout << "Nobody can take this order!" << endl;
    }
}

void Barista::announceOrder() {
    if (customers_.size() != 0) {
        currentOrder_ = (*customers_.begin())->getOrder();
        cout << endl << getRank() << " Barista: Order up! " << currentOrder_->getName() << '!' << endl;
        for (unordered_set<Customer*>::iterator it = customers_.begin(); it != customers_.end();) {
            if ((*it)->checkOrder()) {
                it = customers_.erase(it);
            } else {
                ++it;
            }
        }
    }
}

class JuniorBarista: public Barista {
public:
    JuniorBarista(Barista* successor = nullptr): Barista(successor, "Junior") {}
    void takeOrder(Customer* c) override {
        if (c->getOrder()->nameContains("sprinkles") || c->getOrder()->nameContains("caramel") || c->getOrder()->nameContains("foam") || c->getOrder()->nameContains("ice")) {
            Barista::takeOrder(c);
        } else {
            cout << "Junior Barista: I can take your order!" << endl;
            customers_.insert(c);
            c->setBarista(this);
        }
    }
};

class SeniorBarista: public Barista {
public:
    SeniorBarista(Barista* successor = nullptr): Barista(successor, "Senior") {}
    void takeOrder(Customer* c) override {
        if (c->getOrder()->nameContains("foam")) {
            Barista::takeOrder(c);
        } else {
            cout << "Senior Barista: I can take your order!" << endl;
            customers_.insert(c);
            c->setBarista(this);
        }
    }
};

class Manager: public Barista {
public:
    Manager(Barista* successor = nullptr): Barista(successor, "Manager") {}
    void takeOrder(Customer* c) override {
        cout << "Manager: I can take your order!" << endl;
        customers_.insert(c);
        c->setBarista(this);
    }
};

Customer::Customer(const string &name): name_(name) {
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
    Barista* manager = new Manager();
    Barista* seniorBarista = new SeniorBarista(manager);
    Barista* juniorBarista = new JuniorBarista(seniorBarista);
    int r;
    int customer_number = 0;
    juniorBarista->takeOrder(new Customer("Customer " + to_string(++customer_number)));
    do {
        r = rand() % 2;
        if (r) {
            juniorBarista->announceOrder();
            seniorBarista->announceOrder();
            manager->announceOrder();
        } else {
            juniorBarista->takeOrder(new Customer("Customer " + to_string(++customer_number)));
        }
    } while (juniorBarista->numOfCustomers() != 0 || seniorBarista->numOfCustomers() != 0 || manager->numOfCustomers() != 0);
}
