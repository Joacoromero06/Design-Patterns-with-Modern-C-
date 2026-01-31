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
/*
Pointer to IMPLementation
Is great because let you api class just be a tini object where the pointer is just 8 bytes
This is fantastic to compilers because you DECLARE IMPLClass exists but no how is it, so
holding a pointer lets the compiler to go forward without goint to an extens implementation

GOAL: Changing private data not force to recompile
*/