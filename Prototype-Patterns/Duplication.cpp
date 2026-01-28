//ordinary duplication
#include <iostream>
#include <string>
#include <memory>
#include <vector>
struct Adress{
    std::string street, hub, province;
    Adress(const std::string& s, const std::string& h, const std::string& p): street{s}, hub{h}, province{p} {}
};
struct Contact{
    std::string name;
    std::shared_ptr<Adress> adress;
    Contact(const std::string& name, std::shared_ptr<Adress> adress): name{name}, adress{adress} {}
    friend std::ostream& operator<<(std::ostream& os, Contact c){
        return os << c.name;
    }
};
int main(){
    auto prototype = std::make_shared<Adress>("Lerma 41", "Huaico", "Salta");
    std::vector<Contact> contact_list = {Contact{"Joaco", prototype}, Contact{"Jhon", prototype}, Contact{"Juli", prototype}};
    for (auto c: contact_list)
        std::cout << c << std::endl;
    return 0;
}