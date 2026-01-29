struct Singleton{
private:
    Singleton(){}
public:
    static Singleton& get() {
        static Singleton* my_unique_instance = new Singleton();
        return *my_unique_instance;
    }
    Singleton(const Singleton&) = delete; // no copy default
    Singleton(Singleton&&) = delete; // dont let std::move
    Singleton& operator=(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete; 
};