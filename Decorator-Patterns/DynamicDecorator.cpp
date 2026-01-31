#include <string>
#include <iostream>
#include <sstream>
struct Shape{
    virtual std::string str() const = 0;
};
struct Circle: public Shape{
    float r;
    explicit Circle(float r): r{r} {}
    std::string str() const override{
        std::ostringstream oss; 
        oss << "i am a circle with radius " << r ;
        return oss.str();
    }
    void resize(float k){r*=k;}
};
struct Rectangle: public Shape{
    float l1, l2;
    explicit Rectangle(float l1, float l2): l1{l1}, l2{l2} {}
    std::string str(){
        std::ostringstream oss;
        oss << "i am a rectangle l1 "<< l1 << "l2 "<<l2;
        return oss.str();
    }
};
struct Square: public Rectangle{
    float l;
    explicit Square(float l): Rectangle{l,l}, l{l} {}
    std::string str() const override{
        std::ostringstream oss;
        oss << "i am an square with side "<< l;
        return oss.str();
    }
};

struct ColoredShape: public Shape{
    const Shape& shape;
    std::string color;
    ColoredShape(const Shape& shape, const std::string& s): shape{shape}, color{s} {}
    std::string str() const override{
        std::ostringstream oss;
        oss << shape.str() << " has colour " << color ;
        return oss.str();
    }
};
struct TransparentShape: public Shape{
    const Shape& shape;
    u_int8_t transparency;
    TransparentShape(const Shape& shape, u_int8_t t): shape{shape}, transparency{t} {}
    std::string str() const override{
        std::ostringstream oss;
        oss << shape.str() << " has transparency " <<static_cast<float>(transparency)/255.f*100.f << "%";
        return oss.str();
    }
};
int main(){
    Square square{2};
    TransparentShape A{square, static_cast<u_int8_t>(85)};
    std::cout << A.str() << std::endl;
    TransparentShape t{A,170};
    ColoredShape B{ t, "multicolor"};
    std::cout << B.str() << std::endl;

}