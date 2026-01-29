#include <iostream>
#include <cmath>
struct Point1{
    float x, y;
    // cartesian
    Point1(float x,float y): x{x}, y{y} {}

    // polar impossible
};

/*Factory methods*/
struct Point2{
private:
    float x,y;
    Point2(float x,float y): x{x}, y{y} {}
public:
    friend std::ostream& operator<<(std::ostream& os, Point2 p){
        return os << "(" << p.x << "," << p.y << ")";
    }
    static Point2 newCartesian(float x, float y){return Point2{x, y};}
    static Point2 newPolar(float r, float theta){return Point2{r*std::cos(theta), r*std::sin(theta)};}
};
int main1(){
    Point2 p = Point2::newPolar(.42, 12);
    std::cout << p << std::endl;
    return 0;
}

/*Factory methods segregated*/
struct Point3{
    friend class Point3Factory;
    float x, y;
private:
    Point3(float x, float y): x{x}, y{y} {}
public:
    friend std::ostream& operator<<(std::ostream& os, Point3 p){return os << "(" << p.x << "," << p.y << ")";}
};
struct Point3Factory{
    static Point3 newCartesian(float x, float y){return Point3{x, y};}
    static Point3 newPolar(float r, float theta){return Point3{r*std::cos(theta), r*std::sin(theta)};}
};
int main2(){
    Point3 p = Point3Factory::newPolar(1,0);
    std::cout << p << std::endl;
    return 0;
}
struct Point4Factory;
struct Point4{
    float x, y;
private:
    Point4(float x, float y): x{x}, y{y} {}
    struct Point4Factory{
    public:
        static Point4 newCartesian(float x, float y){return Point4{x, y};}
        static Point4 newPolar(float r, float theta){return Point4{r*std::cos(theta), r*std::sin(theta)};}
    private:
        Point4Factory() {}
    };
public:
    static Point4Factory factory;
    friend std::ostream& operator<< (std::ostream& os, Point4 p){return os << "(" << p.x<<"," << p.y << ")";}
};
int main(){
    Point4 p = Point4::factory.newPolar(1, 3.14);
    std::cout << p << std::endl;
    return 0;
}
