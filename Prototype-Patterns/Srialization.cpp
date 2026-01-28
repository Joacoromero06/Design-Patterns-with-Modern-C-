// first use of boost, gpt example, not mine.
#include <iostream>
#include <string>
#include <sstream> // For stringstream (memory buffer)

// Boost Headers
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp> // Needed for std::string
#include <boost/serialization/access.hpp> // Needed for the 'friend' declaration

using namespace std;

// 1. The Dependency (Address)
struct Address {
    string street;
    int number;

    Address() {} // Default constructor required for deserialization
    Address(string s, int n) : street(s), number(n) {}

private:
    // Grant access to Boost
    friend class boost::serialization::access;

    // The Recipe: "Here is how you save/load me"
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & street;
        ar & number;
    }
};

// 2. The Complex Object (Contact)
struct Contact {
    string name;
    Address* address = nullptr; // A Pointer! The tricky part.

    Contact() {} // Default constructor required
    Contact(string n, Address* a) : name(n), address(a) {}
    
    // Destructor to clean up memory
    ~Contact() { delete address; }

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & name;
        ar & address; // Boost automatically handles the pointer logic!
    }
};

// 3. The Cloning Logic (The "Teleporter")
// This function takes ANY object 'T', serializes it to RAM, and re-creates it.
template <typename T>
T clone(const T& source) {
    // A. Serialize (Save to memory)
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << source; // Write object to stream

    // B. Deserialize (Load from memory)
    std::string serialized_data = oss.str();
    std::istringstream iss(serialized_data);
    boost::archive::text_iarchive ia(iss);
    
    T result;
    ia >> result; // Read object from stream
    return result;
}

// 4. Usage
int main() {
    // Step 1: Create the Original (The Prototype)
    Contact john{"John Doe", new Address{"Baker St", 221}};

    // Step 2: CLONE it
    // We don't call a copy constructor. We teleport it.
    Contact jane = clone(john);

    // Step 3: Modify the Clone
    jane.name = "Jane Smith";
    jane.address->street = "Wall St"; // Modify the address
    jane.address->number = 100;

    // Step 4: Verify Deep Copy
    cout << "Original: " << john.name << " lives at " 
         << john.address->street << " " << john.address->number << endl;
         
    cout << "Clone:    " << jane.name << " lives at " 
         << jane.address->street << " " << jane.address->number << endl;
}