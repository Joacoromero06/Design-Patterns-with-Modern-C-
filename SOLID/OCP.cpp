// Implementation with OCP
enum class Color{r,g,b};
enum class Size{l, m, s};

#include <iostream>
#include <vector>
#include <string>
struct Product{ std::string s; Color c; Size z;};

namespace FilterInterfaces
{
    template <typename T> struct Specification{ // interface
        virtual bool satisfies(T* obj) = 0; // virtual to tell c++ search actual method satisfies of actual class
    };

    template<typename T>struct Filter{
        typedef std::vector<T*> Items;
        virtual Items filter(Items items, Specification<T>&spec);
    };
    template<typename T> struct AndSpecification: Specification<T>{
        Specification<T>& fst;
        Specification<T>& snd;
        AndSpecification(Specification<T>& f, Specification<T>& s): fst{f}, snd{s}{}
        bool satisfies(T* obj) override{
            return fst.satisfies(obj) && snd.satisfies(obj);
        }
    };
}; // namespace FilterInterfaces

typedef std::vector<Product*> Items;
using namespace FilterInterfaces;
struct ProductFilter: Filter<Product>{
    Items filter(Items items, Specification<Product>&prod_spec) override{
        Items result;
        for (auto&p : items)
            if( prod_spec.satisfies(p) )
                result.push_back(p);
        return result;
    }
};  
struct RedSpecification : Specification<Product>{
    bool satisfies(Product* p)override{
        return p->c == Color::r;
    }
};
struct ColorSpecification: Specification<Product>{
    Color c;
    ColorSpecification(Color c): c{c} {} 
    bool satisfies(Product* p) override {return p->c == c;}
};
struct SizeSpecification: Specification<Product>{
    Size z;
    SizeSpecification(Size z): z{z} {}
    bool satisfies(Product* p) override{return p->z == z;}
};

typedef Specification<Product> Spec;

int main(){
    SizeSpecification spec_small{Size::s};
    ColorSpecification spec_red{Color::r};
    ProductFilter filter{};
    Product apple1{"apple", Color::r, Size::s};
    Product apple2{"apple", Color::g, Size::s};
    Product sandia{"sandia", Color::g, Size::m};

    Items items{&apple1, &apple2, &sandia};
    Items red_fruits = filter.filter(items, spec_red);
    if (red_fruits.empty())
        std::cout << "empty" << std::endl; // is empty, some error happens in filter logic
    for (auto p: red_fruits)
        std::cout << p << std::endl;

    AndSpecification<Product> red_small_spec{spec_red, spec_small};
    Items red_small_fruits = filter.filter(items, red_small_spec);
    for (auto p: red_small_fruits)
        std::cout << p << std::endl;
    
    return 0;
}


