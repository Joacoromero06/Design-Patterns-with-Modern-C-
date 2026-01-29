#include <iostream>
#include <memory>
#include <vector>
#include <string>
struct GraphicObj{
    virtual void draw()=0;
};
struct Circle: public GraphicObj{
    void draw() override { std::cout << "circle" << std::endl;}
};
struct Group: public GraphicObj{
    std::vector<std::unique_ptr<GraphicObj>> objs;
    std::string name;
    Group(const std::string& s): name{s} {}
    void add(GraphicObj& obj){objs.emplace_back(std::make_unique<GraphicObj>(obj));}
    void draw() override{
        std::cout << "group name: " << name << std::endl;
        for( auto&& o: objs )
            o->draw();
    }
};