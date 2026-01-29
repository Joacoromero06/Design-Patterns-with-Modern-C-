#include <iostream>
#include <memory>
#include <map>

class Drink{};
// Abstract type of Drink
class HotDrink: public Drink{
public:
    virtual void prepare()=0;
};

// concrete 'HotDrinks'
class Tea: public HotDrink{public: void prepare() override{std::cout << "making tea" << std::endl;}};
class Coffe: public HotDrink{public: void prepare() override{std::cout << "making coffe" << std::endl;}};

// Abstract Factory of hot drinks
class HotDrinkFactory{
public:
    virtual std::unique_ptr<HotDrink> make()=0;
};

// concrete 'Factory of hot drinks'
class TeaFactory: public HotDrinkFactory{
    std::unique_ptr<HotDrink> make() override{
        return std::make_unique<Tea>(); // no suitable user-defined conversion from "std::__detail::__unique_ptr_t<Tea>" (aka "std::unique_ptr<Tea, std::default_delete<Tea>>") to "std::unique_ptr<HotDrink, std::default_delete<HotDrink>>" existsC/C++(312) 
    }
};
class CoffeFactory: public HotDrinkFactory{
public:
    std::unique_ptr<HotDrink> make() override{
        return std::make_unique<Coffe>(); // no suitable user-defined conversion from "std::__detail::__unique_ptr_t<Tea>" (aka "std::unique_ptr<Tea, std::default_delete<Tea>>") to "std::unique_ptr<HotDrink, std::default_delete<HotDrink>>" existsC/C++(312)
    }
};



class ColdDrink: public Drink{
public:
    virtual void serve()=0;
};

// concrete 'ColdDrinks'
class Batido: public ColdDrink{
public:
    void serve() override{std::cout << "serving batido" << std::endl;}
};
class Helado: public ColdDrink{
public:
    void serve() override{std::cout << "serving helado" << std::endl;}
};

// Abstract Factory of cold drinks
class ColdDrinkFactory{
public:
    virtual std::unique_ptr<ColdDrink> make()=0;
};
// concrete 'Factory of cold drinks'
class BatidoFactory: public ColdDrinkFactory{
public: 
    std::unique_ptr<ColdDrink> make() override{
        return std::make_unique<Batido>();
    }
};
class HeladoFactory: public ColdDrinkFactory{
    std::unique_ptr<ColdDrink> make() override{
        return std::make_unique<Helado>();
    }
};


// General Drink Factory API
enum class Drinks{TEA, COFFE, HELADO, BATIDO};
class DrinkFactory{
    std::map< Drinks,std::unique_ptr<HotDrinkFactory> > hot_factories;
    std::map< Drinks,std::unique_ptr<ColdDrinkFactory> > cold_factories;
public:
    DrinkFactory(){ 
        hot_factories[Drinks::TEA] = std::make_unique<TeaFactory>(); 
        hot_factories[Drinks::COFFE] = std::make_unique<CoffeFactory>();  
        cold_factories[Drinks::BATIDO] = std::make_unique<BatidoFactory>();
        cold_factories[Drinks::HELADO] = std::make_unique<HeladoFactory>();
    }
    std::unique_ptr<Drink> make_drink(Drinks drink){
        std::unique_ptr<Drink> return_drink;
        switch (drink) 
        {
        case Drinks::HELADO: case Drinks::BATIDO:
        {
            auto cold_drink = cold_factories[drink]->make();
            cold_drink->serve();
            return_drink = std::move(cold_drink); 
            break;
        }
        case Drinks::COFFE: case Drinks::TEA:
        {
            auto hot_drink = hot_factories[drink]->make();
            hot_drink->prepare(); 
            return_drink = std::move(hot_drink);
            break;
        }
        default:
            break;
        }
        return return_drink;
    }
};
int main(){
    DrinkFactory f;
    auto d1 = f.make_drink(Drinks::TEA);
    auto d2 = f.make_drink(Drinks::HELADO);
}

