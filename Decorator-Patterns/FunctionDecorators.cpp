#include <functional>
#include <string>
#include <iostream>

// we want to decorate the function loggin everey time is called
struct MakeLogger{ // onlyt void
    std::function<void()> func;
    std::string name;
    MakeLogger(std::function<void()> func, const std::string& s): func{func}, name{s} {}
    void operator()(){
        std::cout << "entering to " << name << std::endl;
        func();
        std::cout << "exiting from " << name << std::endl;
    }
};
int main1(){
    MakeLogger Hello_function_decorated([](){std::cout << "hello function" << std::endl;}, "Hello function");
    Hello_function_decorated();
    return 0;
}
template <typename Func>
struct MakeTemplatedLogger{
    Func func;
    std::string name;
    MakeTemplatedLogger(Func func, const std::string& s): func{func}, name{s} {}
    void operator()(){
        std::cout << "enter to " << name<< std::endl;
        func();
        std::cout << "exit from " << name<< std::endl;

    }
};
template<typename Func> auto make_logger1(Func func, const std::string& s){
    return MakeTemplatedLogger<Func>(func, s);
};
int main2(){
    return 0;
    //auto A = make_logger1<std::function<void>> ([](){std::cout << "i only say hello" << std::endl;}, "HelloFunction");
}
template <typename T>
struct TemplatedLogger;

template<typename R, typename... Args>
struct TemplatedLogger<R(Args...)>{ // a template argument list is not allowed in a declaration of a primary templateC/C++(840)
    std::function<R(Args...)> func;
    std::string name;
    TemplatedLogger(std::function<R(Args...)> func, const std::string& s): func{func}, name{s} {}
    R operator()(Args ...args){
        std::cout << "enter to " << name << std::endl;
        R result = func(args...);
        std::cout << "exit from " << name << std::endl;
        return result;
    }

};

template <typename R, typename... Args>
auto make_logger(R (*func) (Args...), const std::string& name){
    return TemplatedLogger<R(Args...)>(std::function<R(Args...)>(func), name);
}
int add(int x, int y){return x+y;}
int main(){
    auto log_add = make_logger(add, "add");
    std::cout << log_add(3,4) << std::endl;
}