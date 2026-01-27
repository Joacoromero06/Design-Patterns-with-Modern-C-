#include <iostream>
#include <string>
#include <vector>
#include <utility> // For std::move

// ---------------------------------------------------
// 1. FORWARD DECLARATIONS
// We promise the compiler these classes will exist later.
// ---------------------------------------------------
class PersonBuilder;
class PersonDireccionBuilder;
class PersonTrabajoBuilder;

// ---------------------------------------------------
// 2. THE OBJECT (PERSON)
// ---------------------------------------------------
class Person {
    // Grant access to the builders
    friend class PersonBuilder;
    friend class PersonDireccionBuilder;
    friend class PersonTrabajoBuilder;

    // Helper for printing (Friend because it needs private access)
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << "Calle: " << p.calle << " (" << p.localidad << ")" 
                  << " | Puesto: " << p.puesto << " en " << p.empresa 
                  << " ($" << p.salario << ")";
    }

    std::string calle, barrio, localidad, provincia, pais;
    std::string empresa, sector, puesto;
    float salario = 0.0f;

    // Private Constructor: Only builders can create a Person
    Person() = default; 
};

// ---------------------------------------------------
// 3. THE BUILDER BASE
// ---------------------------------------------------
class PersonBuilderBase {
protected:
    Person& person; // Reference to the object being built
    explicit PersonBuilderBase(Person& p) : person{p} {}

public:
    // Conversion operator: Returns the final built object
    operator Person() const {
        return std::move(person);
    }

    // Facet switching methods
    // We DECLARE them here, but cannot DEFINE them yet
    PersonDireccionBuilder vive() const;
    PersonTrabajoBuilder trabaja() const;
};

// ---------------------------------------------------
// 4. THE CONCRETE BUILDERS
// ---------------------------------------------------
class PersonDireccionBuilder : public PersonBuilderBase {
public:
    explicit PersonDireccionBuilder(Person& person) : PersonBuilderBase{person} {}

    PersonDireccionBuilder& en_calle(std::string calle) {
        person.calle = calle;
        return *this;
    }
    PersonDireccionBuilder& en_localidad(std::string localidad) {
        person.localidad = localidad;
        return *this;
    }
    // ... add other setters ...
};

class PersonTrabajoBuilder : public PersonBuilderBase {
public:
    explicit PersonTrabajoBuilder(Person& person) : PersonBuilderBase{person} {}

    PersonTrabajoBuilder& en_empresa(std::string empresa) {
        person.empresa = empresa;
        return *this;
    }
    PersonTrabajoBuilder& puesto(std::string puesto) {
        person.puesto = puesto;
        return *this;
    }
    PersonTrabajoBuilder& ingreso(float salario) {
        person.salario = salario;
        return *this;
    }
};

// ---------------------------------------------------
// 5. THE MAIN BUILDER (THE OWNER)
// ---------------------------------------------------
class PersonBuilder : public PersonBuilderBase {
    Person p; // The actual instance lives here!
public:
    PersonBuilder() : PersonBuilderBase{p} {}
};

// ---------------------------------------------------
// 6. LATE IMPLEMENTATION
// Now the compiler knows what 'PersonDireccionBuilder' is.
// ---------------------------------------------------
PersonDireccionBuilder PersonBuilderBase::vive() const {
    return PersonDireccionBuilder{person};
}

PersonTrabajoBuilder PersonBuilderBase::trabaja() const {
    return PersonTrabajoBuilder{person};
}

// ---------------------------------------------------
// 7. MAIN
// ---------------------------------------------------
int main() {
    Person p = PersonBuilder()
                .vive()
                    .en_calle("Av. Libertador 1234")
                    .en_localidad("Buenos Aires")
                .trabaja()
                    .en_empresa("Tech Corp")
                    .puesto("Developer")
                    .ingreso(120000);

    std::cout << p << std::endl;
    return 0;
}