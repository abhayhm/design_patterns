#include <iostream>
#include <memory>
using namespace std;

class Pizza
{
public:
    virtual string description() const = 0;
    virtual double price() const = 0;
    virtual ~Pizza() = default;
};

class MargheritaPizza : public Pizza
{
public:
    string description() const override
    {
        return "Margherita Pizza";
    }

    double price() const override
    {
        return 9.99;
    }
};

class HawaiianPizza : public Pizza
{
public:
    string description() const override
    {
        return "Hawaiian Pizza";
    }

    double price() const override
    {
        return 11.99;
    }
};

class PepperoniPizza : public Pizza
{
public:
    string description() const override
    {
        return "Pepperoni Pizza";
    }

    double price() const override
    {
        return 12.99;
    }
};

class Toppings: public Pizza{
private:
    const Pizza *pizza;
public:
    Toppings(const Pizza *p): pizza(p){}
    
    string description() const override{
        return pizza->description();
    }

    double price() const override{
        return pizza->price();
    }
};

class MushroomToppings: public Toppings{
public:
    MushroomToppings(const Pizza *p): Toppings(p) {}

    string description() const override{
        return Toppings::description() + " with mushroom toppings";
    }

    double price() const override{
        return Toppings::price() + 2.99;
    }
};

class ExtraCheese: public Toppings{
public:
    ExtraCheese(const Pizza *p): Toppings(p) {}
    
    string description() const override{
        return Toppings::description() + " with extra cheese";
    }
    
    double price() const override{
        return Toppings::price() + 1.99;
    }
};

int main()
{
    const std::unique_ptr<Pizza> pizzas[]{
        make_unique<MargheritaPizza>(),
        make_unique<PepperoniPizza>(),
        make_unique<HawaiianPizza>()};

    for (const auto &pizza : pizzas)
    {
        cout << pizza->description() << " costs $" << pizza->price() << endl;
    }

    const std::unique_ptr<Toppings> toppings[]{
        make_unique<MushroomToppings>(&*pizzas[1]), //unique_ptr is not regular pointer 
        make_unique<ExtraCheese>(&*pizzas[2]), //unique_ptr is not regular pointer
        make_unique<ExtraCheese>(&*toppings[0])
    };

    for (const auto &pizzawithtoppings : toppings)
    {
        cout << pizzawithtoppings->description() << " costs $" << pizzawithtoppings->price() << endl;
    }
    return 0;
}