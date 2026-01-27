#include <vector>
#include <iostream>
class PersonDireccionBuilder;
class PersonTrabajoBuilder;
class PersonBuilder;
class Person{
    friend class PersonDireccionBuilder;
    friend class PersonTrabajoBuilder;
    friend class PersonBuilderBase;
    friend class PersonBuilder;
    // POdria ser cada atributo del tipo class EnumAtributo

    // direccion
    std::string calle, barrio, localidad, provincia, pais;
    
    // trabajo
    std::string empresa, sector, puesto;
    float salario;
    //static PersonBuilder built(){return PersonBuilder{}; }
    friend std::ostream& operator<<(std::ostream& os, const Person& p){
        return os << "Calle: " << p.calle << " Salario: " << p.salario << std::endl;
    }
    Person(){}
};

class PersonBuilderBase{
    
    protected:
        Person& person;
        explicit PersonBuilderBase(Person& p): person{p} {}
    public:
        operator Person(){return std::move(person);}// why is need it to move the reference? is not this function only for smart pointers?
        PersonTrabajoBuilder trabaja() const;
        PersonDireccionBuilder vive() const;
};
class PersonDireccionBuilder : public PersonBuilderBase{
    public:
    explicit PersonDireccionBuilder(Person& person): PersonBuilderBase{person} {}

    typedef PersonDireccionBuilder self;
    self& en_calle(const std::string& calle){ person.calle = calle; return *this; } // error: member "Person::salario" (declared at line 11) is inaccessibleC/C++(265)
    /*self& en_barrio(const std::string& barrio){ }
    self& en_localidad(const std::string& localidad){}
    self& en_provincia(const std::string& provincia){}
    self& en_pais(const std::string& pais){}*/
};
class PersonTrabajoBuilder : public PersonBuilderBase{
    public:
    explicit PersonTrabajoBuilder(Person& person): PersonBuilderBase{person} {}
    typedef PersonTrabajoBuilder self;
    self& ingreso(float salario){person.salario = salario; return *this;} // error: member "Person::salario" (declared at line 11) is inaccessibleC/C++(265)
    /*self& empresa(const std::string& empresa) {person.empresa = empresa; return *this;}
    self& sector(const std::string& empresa) {person.empresa = empresa; return *this;}
    self& puesto(const std::string& empresa) {person.empresa = empresa; return *this;}*/
};
class PersonBuilder : public PersonBuilderBase{
    Person p; // the built in person
    public:
        PersonBuilder() : PersonBuilderBase{p} {} // error: "Person::Person()" (declared at line 13) is inaccessibleC/C++(330)
};
PersonTrabajoBuilder PersonBuilderBase::trabaja() const{return PersonTrabajoBuilder{person};}
PersonDireccionBuilder PersonBuilderBase::vive() const{return PersonDireccionBuilder{person};} //"PersonDireccionBuilder::PersonDireccionBuilder(Person &person)" (declared at line 35) is inaccessibleC/C++(330)
int main(){
    Person p = PersonBuilder{}.vive().en_calle("Maria c alonso").trabaja().ingreso(10e4);
    std::cout << p;
}