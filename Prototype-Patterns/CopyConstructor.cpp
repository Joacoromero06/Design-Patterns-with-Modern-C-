#include <string>
struct Address{
    std::string streeet, hub;
    Address(const std::string& x, const std::string& y): streeet{x}, hub{y} {}
};
struct Contact{
    std::string name;
    Address ad;
    Contact(Contact& c): name{c.name}, ad{c.ad} {}
    Contact(std::string& n, Address ad): name{n}, ad{ad} {}
};
int main(){
    
    return 0;
}