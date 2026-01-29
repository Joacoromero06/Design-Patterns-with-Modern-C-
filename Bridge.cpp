#include <iostream>
struct Renderer{
    virtual void render_circle(float x, float y, float r)=0;
};
struct VectorRenderer:Renderer
{
    void render_circle(float x, float y, float r) override{
        std::cout << "Formulas for draw 3d circle" << std::endl;
    }
};
struct RasterRenderer: Renderer
{
    void render_circle(float x, float y, float r) override{
        std::cout << "Drawing circle per pixel" << std::endl;
    }
};
struct Shape{
protected:
    Renderer& renderer;
    Shape(Renderer& r): renderer{r} {}
public:
    virtual void draw()=0;
    virtual void resize(float k)=0;
};
struct Circle: Shape{
    float x, y, r;
    Circle(float x, float y, float r, Renderer& re): Shape{re}, x{x}, y{y}, r{r} {}
    void draw() override{renderer.render_circle(x, y, r);}
    void resize(float k) override{r*=k;}

}; 
