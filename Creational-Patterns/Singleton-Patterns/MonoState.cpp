#include <iostream>
struct Printer{
    static int state;
    int getState()const {return state;}
    void setState(const int s) {state=s;}
    void print();
    friend std::ostream& operator<<(std::ostream& os, Printer p){ return os << p.state << std::endl;}
};
int Printer::state = 0;
int main(){
    auto p1 = Printer{};
    auto p2 = Printer{};
    p1.setState(1);
    p2.setState(2);
    std::cout << p1 << p2 << std::endl;
}