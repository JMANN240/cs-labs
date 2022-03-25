// needed for lab
// Mikhail Nesterenko
// 3/14/2016

#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <algorithm>
#include "CarFactory.hpp"

using std::vector; using std::array;
using std::cout; using std::endl;
using std::find; using std::generate_n;
using std::string;

class CarLot{
public:
    CarLot();
    Car *testDriveCar(){ return currentCar_; }

    // if a car is bought, requests a new one
    void buyCar() { 
        cars4sale_.erase(find(cars4sale_.begin(), cars4sale_.end(), currentCar_));
        cars4sale_.push_back(factories_[rand()%factories_.size()]->requestCar());
        currentCarIndex_ = 0;
        currentCar_ = cars4sale_[currentCarIndex_];
    }

    void nextCar() {
        currentCarIndex_++;
        if (currentCarIndex_ == lotSize_) {
            currentCarIndex_ = 0;
        }
        currentCar_ = cars4sale_[currentCarIndex_];
    }

    int lotSize() {
        return lotSize_;
    }
		     
private:
    vector<Car *> cars4sale_; // vector of cars for sale at the lot
    Car *currentCar_;
    vector<CarFactory *> factories_;
    int lotSize_ = 10;
    int currentCarIndex_ = 0;
};


CarLot::CarLot(){
    // creates 2 Ford factories and 2 Toyota factories 
    factories_.push_back(new FordFactory());   
    factories_.push_back(new ToyotaFactory());
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());

    // gets the first car for sale
    for (int i = 0; i < 10; ++i) {
        cars4sale_.push_back(factories_[rand() % factories_.size()] -> requestCar());
    }
    for (auto it : cars4sale_) {
        cout << it -> getMake() << ' ' << it -> getModel() << endl;
    }
    currentCar_ = cars4sale_.front();
}



CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
    static const std::array<std::string, 5>
    models = {"Corolla", "Camry", "Prius", "4Runner", "Yaris"};
    string wantedModel = models[rand() % models.size()];

    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();
    
    cout << '[' << id << "] \"Hello, I am looking to buy a Toyota " << wantedModel << endl;
    
    for (int i = 0; i < carLotPtr -> lotSize(); ++i) {
        Car *toBuy = carLotPtr -> testDriveCar(); 
        cout << "test driving " 
            << toBuy->getMake() << " "
            << toBuy->getModel() << endl;

        if (toBuy->getMake() == "Toyota" && toBuy->getModel() == wantedModel){
            cout << " love it! buying it!" << endl;
            carLotPtr -> buyCar();
            break;
        } else
            cout << " did not like it!" << endl;
            carLotPtr -> nextCar();
    }
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
    static const std::array<std::string, 4>
    models = {"Focus", "Mustang", "Explorer", "F-150"};
    string wantedModel = models[rand() % models.size()];

    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();
    
    cout << '[' << id << "] \"Hello, I am looking to buy a Ford " << wantedModel << endl;
    
    for (int i = 0; i < carLotPtr -> lotSize(); ++i) {
        Car *toBuy = carLotPtr -> testDriveCar(); 
        cout << "test driving " 
            << toBuy->getMake() << " "
            << toBuy->getModel() << endl;

        if (toBuy->getMake() == "Ford" && toBuy->getModel() == wantedModel){
            cout << " love it! buying it!" << endl;
            carLotPtr -> buyCar();
            break;
        } else
            cout << " did not like it!" << endl;
            carLotPtr -> nextCar();
    }
}



int main() {
    srand(time(nullptr));

    const int numBuyers = 10;
    for(int i = 0; i < numBuyers; ++i)
        if(rand() % 2 == 0)
            toyotaLover(i);
        else
            fordLover(i);
    
}
