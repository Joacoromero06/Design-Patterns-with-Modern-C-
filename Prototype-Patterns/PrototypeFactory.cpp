#include <memory>
#include <iostream>
#include <string>
using namespace std;
struct Employee{
    friend class EmployeeFactory;
    string name, street, hub;
    int age;
//private:
    Employee(){}
    Employee(const string& n, const string& s, const string& h, const int a): name{n}, street{s}, hub{h}, age{a} {}
    Employee(const string& n, int age, Employee& e): name{n}, street{e.street}, hub{e.hub}, age{age} {}    
    friend ostream& operator<< (ostream& os, Employee& e ){ return os << e.name; }
};
enum class Prototypes{VECINO, FAMILIAR, AMIGO};
struct EmployeeFactory{
    static Employee vecino;
    static unique_ptr<Employee> newEmployee(Prototypes tipo, const string& name, int age){
        switch (tipo)
        {
        case Prototypes::VECINO: return make_unique<Employee>(name, age, vecino);
        
        default:
            return  make_unique<Employee>();
            exit (1);
            break;
        }
        
    }
};
Employee EmployeeFactory::vecino{"", "maria c aolonso", "barrio huaico", 0};

int main(){
    auto e = EmployeeFactory::newEmployee(Prototypes::VECINO, "nahuel", 24);
    cout << *e << endl;
}
