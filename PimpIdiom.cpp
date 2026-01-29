#include <string>
#include <iostream>
struct Person{
    // all features
    std::string name;
    void greet();
    Person();
    ~Person();

    // all delegated to the implementation
    class PersonImplementation;
    PersonImplementation* implementation; // why must be a pointer?
};
struct Person::PersonImplementation{ // why Person::Myclass? Is not necessary i Person:: prefix, i believe.
    void greet(Person* p);
};

// only the stuff Person class do
Person::Person(): implementation{new PersonImplementation} {}
Person::~Person(){delete implementation;}

void Person::greet(){implementation->greet(this);}
void Person::PersonImplementation::greet(Person* p){std::cout << "hi " << p->name << std::endl;}
