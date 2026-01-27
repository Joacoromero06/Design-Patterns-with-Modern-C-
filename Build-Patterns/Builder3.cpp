#include <vector>
#include <iostream>

struct Tag{
    std::string name;
    std::string text;
    std::vector<Tag> childs;
    std::vector< std::pair<std::string, std::string> > attributes;

    friend std::ostream& operator<<(std::ostream& os, const Tag& tag){
        os << "<" << tag.name ;
        for (auto a: tag.attributes)
            os << " " <<a.first << "=" << a.second;
        os << ">";
        if(!tag.text.empty()) os << " " << tag.text;
        for (auto e: tag.childs)
            os << "     " << e ;
        os << "</" << tag.name << ">";
        return os;
    }
    protected:
    Tag(const std::string& name, const std::string& text): name{name}, text{text}{}
    Tag(const std::string& name, const std::vector<Tag>& childs): name{name}, childs{childs} {}

};
// Hierarchical constructors defining a tree objects using nested constructors
struct P: Tag{
    explicit P(const std::string& text): Tag{"P", text} {}
    explicit P(const std::initializer_list<Tag>& childs): Tag{"P", childs} {}
};
// initializer_lis is the type of vec = {a, b, c}; an array
// emplace back recieves
struct IMG: Tag{
    explicit IMG(const std::string& url): Tag{"IMG", ""} {
        attributes.emplace_back("src", url);
    }
};
int main(){
    std::cout << P{ IMG {"https/github/images.png"} } << std::endl;
    return 0;
}