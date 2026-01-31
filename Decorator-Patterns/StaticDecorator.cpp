#include <string>
#include <sstream>
#include <iostream>
#include <type_traits>
#include <utility>
using namespace std;
struct Shape{
    virtual string str() const =0;
};
struct Circle: public Shape{
    float r;
    Circle(float r): r{r} {}
    string str() const override{ostringstream oss; oss << "i am a circle radius " << r; return oss.str();}
};
struct Square: public Shape{
    float l;
    Square(float l): l{l} {}
    string str() const override{ostringstream oss; oss << "i am a square side " << l; return oss.str();}
};
/*mixin inheritance*/

template <typename T> // parent class is T
struct ColoredShape: public T{
    static_assert(is_base_of<Shape, T>::value, "Template argument must be child of Shape class");
    string color;
    template <typename... Args> // more than one type name in a list Args
    ColoredShape(string color, Args ...args): // a list of parameters, that must match with Args types
    T(forward<Args>(args)...), // unpack each forward<Args[i]> args[i]
    color(color) {}
    string str() const override{
        ostringstream oss;
        oss << T::str() << " my color is " << color ;
        return oss.str();
    }
};

template <typename T> 
struct TransparentShape: public T{
    u_int8_t t;
    template <typename... Args>
    TransparentShape(u_int8_t t, Args... args):
    T(forward<Args>(args) ...),
    t(t)
    {}
    string str() const override{
        ostringstream oss;
        oss << T::str() << " my transparency " << static_cast<float>(t) /255.f*100.f << "%";
        return oss.str();
    }
};
int main(){
    ColoredShape<TransparentShape<Circle>> A{"red", 51, 1.f};
    cout << A.str() << std::endl;
}
