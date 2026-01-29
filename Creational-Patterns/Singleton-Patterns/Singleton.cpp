#include <string>
#include <map>
#include <iostream>
struct Database{
virtual int get_population(const std::string& country)=0;
};
struct SingletonDatabase: public Database{
private:
    SingletonDatabase(){/*read data*/}
public:
    int get_population (const std::string& country) override{
        return 2; // the way to query the database
    }
    static SingletonDatabase& get(){
        static SingletonDatabase* db = new SingletonDatabase();
        return *db;
    }
    SingletonDatabase(const SingletonDatabase&) = delete;
    SingletonDatabase(SingletonDatabase&&) = delete;
    SingletonDatabase operator=(const SingletonDatabase&) = delete;
    SingletonDatabase operator=(SingletonDatabase&&) = delete;

};
struct UseSingletonDatabase{
    int sum_all(){
        int n = 10; // supose size database is 10, here we query the length
        int sum=0;
        for(int i=1; i <= n; i++)
            sum += SingletonDatabase::get().get_population("i-th country");
        return sum;
    }
};
// the problem is that is useage is too dependant on the singleton property
struct ConfiguarableUseSingletonDatabase{
    Database& db; // hold an abstract reference
    explicit ConfiguarableUseSingletonDatabase(Database& db): db{db} {}
    int sum_all(){
        int n = 10; // query db
        int sum = 0;
        for(int i = 1 ; i <= n; i++)
            sum += db.get_population("ith country name");
        return sum;
    }
};
// for test we can use another Database
struct DummyDatabase: public Database{
    std::map<std::string, int> capitals;
    DummyDatabase(){
        capitals["bsas"] = int(1000);
        capitals["salta"] = 300;
        capitals["santa cruz"] = 100;
    }
    int get_population(const std::string& country ) override {return capitals[country];} // member function declared with 'override' does not override a base class memberC/C++(1455)
};
int main(){
    auto db = DummyDatabase{};
    auto tester = ConfiguarableUseSingletonDatabase{db}; /*a cast to abstract class "DummyDatabase" is not allowed:C/C++(389)
Singleton.cpp(56, 53): pure virtual function "Database::get_population" has no overrider*/
    std::cout << tester.sum_all() << std::endl;
    return 0;
}