#include <map>
#include <functional>
#include <iostream>
#include <memory>

enum class Drinks{TEA, COFFE, BATIDO, HELADO};

class Drink{};

class HotDrink: public Drink{
public: 
    virtual void prepare()=0;
};
class Tea: public HotDrink{
public:
    void prepare() override {std::cout << "making tea" << std::endl;}
};
class Coffe: public HotDrink{
public:
    void prepare() override {std::cout << "making coffe" << std::endl;}
};

class ColdDrink: public Drink{
public:
    virtual void serve()=0;
};
class Helado: public ColdDrink{
public:
    void serve() override {std::cout << "making helado" << std::endl;}
};
class Batido: public ColdDrink{
public:
    void serve() override {std::cout << "making batido" << std::endl;}
};

class DrinkFactory{
    std::map<  Drinks, std::function< std::unique_ptr<Drink>() >  > factories;
public:
    DrinkFactory(){
        factories[Drinks::BATIDO] = [] { // expression must be a modifiable lvalueC/C++(137)
            auto p = std::make_unique<Batido>();
            p->serve();
            return std::move(p);
        };
        factories[Drinks::HELADO] = [] {
            auto p = std::make_unique<Helado>();
            p->serve();
            return std::move(p);
        };
        factories[Drinks::TEA] = [] {
            auto p = std::make_unique<Tea>();
            p->prepare();
            return std::move(p);
        };
        factories[Drinks::COFFE] = [] {
            auto p = std::make_unique<Coffe>();
            p->prepare();
            return std::move(p);
        };
    }
    std::unique_ptr<Drink> make_drink(Drinks drink){
        return factories[drink]();
    }
};

int main(){
    DrinkFactory f{};
    f.make_drink(Drinks::TEA);
    f.make_drink(Drinks::HELADO);

    return 0;
}