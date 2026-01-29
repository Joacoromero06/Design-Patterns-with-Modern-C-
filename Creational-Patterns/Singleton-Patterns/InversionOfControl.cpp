#include "di/include/boost/di.hpp"
#include <iostream>
namespace di = boost::di;  
struct IFoo{
    int state;
    virtual void fooing()=0;
};
struct Foo: public IFoo{
    Foo(){std::cout << "Foo" << state++ << std::endl; }
    void fooing()override{/*nothing*/}
};
int main(){
    auto injector = di::make_injector(
        di::bind<IFoo>.to<Foo>().in(di::singleton),
        di::bind<int>.to(42)
    );
    // create singleton
    injector.create<Foo>();   
    injector.create<Foo>();   
    injector.create<Foo>();   
}