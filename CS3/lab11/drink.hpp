// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// 11/15/2016

#include <string>

using std::string;

enum class DrinkType {small, medium, large};

class Drink{
public:
   Drink(DrinkType type=DrinkType::small, double price=0):
                 type_(type), price_(price){}
   virtual double getPrice() const;
   virtual string getName() const;
   bool nameContains(string search) const;
private: 
   double price_;
   DrinkType type_;
};

class Coffee: public Drink{
public:
    Coffee(DrinkType type=DrinkType::small, double price=0): Drink(type, price) {};
    double getPrice() const override;
    string getName() const override;
};

class WithSprinkles: public Drink {
public:
    WithSprinkles(const Drink* wrapped): wrapped_(wrapped) {}
    double getPrice() const override;
    string getName() const override;
private:
    const Drink* wrapped_;
};

class WithCaramel: public Drink {
public:
    WithCaramel(const Drink* wrapped): wrapped_(wrapped) {}
    double getPrice() const override;
    string getName() const override;
private:
    const Drink* wrapped_;
};

class WithMilkFoam: public Drink {
public:
    WithMilkFoam(const Drink* wrapped): wrapped_(wrapped) {}
    double getPrice() const override;
    string getName() const override;
private:
    const Drink* wrapped_;
};

class WithIce: public Drink {
public:
    WithIce(const Drink* wrapped): wrapped_(wrapped) {}
    double getPrice() const override;
    string getName() const override;
private:
    const Drink* wrapped_;
};