#include <string>
#include <memory>
#include <iostream>
struct PersonAPI{
private:
    struct PersonIMPL;
    std::unique_ptr<PersonIMPL> pimpl;   
public:
    PersonAPI(): pimpl{std::make_unique<PersonIMPL>()}{}
    void setName(const std::string& s){
        pimpl->name = s;
    }
    void greet(){pimpl->greet();}
   
};

// in implementation include all heavy libraries
struct PersonAPI::PersonIMPL{
    // holds actually all the data
    std::string name;
    PersonIMPL() {}
    void greet(){std::cout << "hi " << name << std::endl;}  
};
