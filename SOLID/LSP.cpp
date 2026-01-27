class Rectangle{
protected:
    int b, h;
public:
    Rectangle(int b, int h): b(b), h(h){}
    int getb() const{return b;}
    int geth() const{return h;}
    virtual void setb(const int b) { this->b = b;}
    virtual void seth(const int h) { this->h = h;}
    int area() const {return b*h;}
};
struct Square: Rectangle{
    Square(int n): Rectangle(n,n){}
    void setb(const int b) override{this->b = h = b;}
    void seth(const int h) override{this->h = b = h;}
};
#include <iostream>
void process(Rectangle& r){
    int b = r.getb();
    r.seth(10);
    std::cout << "Expected area: " << 10*b << " got: " << r.area() << std::endl;
}
int main(){
    Rectangle r{5,5};
    Square c{5};
    process(r);process(c);
    return 0;
}