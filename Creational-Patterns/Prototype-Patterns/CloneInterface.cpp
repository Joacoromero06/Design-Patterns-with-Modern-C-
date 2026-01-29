#include <iostream>
#include <string>
#include <memory>
template<typename T> class Clonable{
public:
    virtual std::unique_ptr<T> clone()=0;
    ~Clonable() = default;
};
struct Address{
    std::string stree, hub, province;
    Address(const std::string& x, const std::string& y, const std::string& z): stree{x}, hub{y}, province{z} {}
};
struct Contact: public Clonable<Contact>{
    std::string name;
    Address add;
    Contact(Address ad, std::string n): add{ad}, name{n} {}
    std::unique_ptr<Contact> clone(){return std::make_unique<Contact>(*this);}
    friend std::ostream& operator<<(std::ostream& os, Contact& c){return os << c.name; }
};
int main(){
    // los que viven en mi calle
    Contact prototype{{"maria c alonso", "barrio huaico", "salta"}, "joaco"};
    
    auto c = prototype.clone();

    std::cout << *c << std::endl;
}