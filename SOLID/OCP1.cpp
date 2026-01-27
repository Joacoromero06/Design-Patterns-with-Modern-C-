enum class Color{r,g,b};
enum class Size{l, m, s};

#include <iostream>
#include <vector>
#include <string>
struct Product{ std::string s; Color c; Size z;};

// implementation without following OPEN CLOSE Principle
struct ProductFilter{ 
    typedef std::vector<Product*> Items; 
    Items by_color(Items, Color);};

ProductFilter::Items ProductFilter::by_color(Items items, Color color)
{
    Items result;
    for (auto& p : items)
        if( p->c == color )
            result.push_back(p);
    
    return result;
}
int main1(){
    Product apple1{"apple", Color::r, Size::s};
    Product apple2{"apple", Color::g, Size::s};
    Product tree{"tree", Color::g, Size::m};
    std::vector<Product*> items{&apple1, &apple2, &tree };
    ProductFilter filter;
    std::vector<Product*> filter_items = filter.by_color(items, Color::g);
    for(auto& p: filter_items)
        std::cout << p << std::endl;
    return 0;
}