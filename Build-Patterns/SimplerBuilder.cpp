#include <string>
#include <vector>
#include <iostream>
struct HtmlElement{
    std::string name; 
    std::string text; 
    std::vector<HtmlElement> elems;
    HtmlElement(){}
    HtmlElement(const std::string& n, const std::string& t): name{n}, text{t} {}
    std::string str(int ident=0)const {
        std::string code = "", pad;
        code += "<" + name + ">";
        switch (ident)
        {
        case 0: pad = "";break;
        case 1: pad = " ";break;
        case 2: pad = "  ";break;
        case 3: pad = "   ";break;
        case 4: pad = "    ";break;
        default: std::cout << "Error ident no setted" << std::endl;break;
        }
        // code += "\n" + pad;
        code += " " + text + " ";
        for(auto e : elems)
            code += pad + e.str();
        code += "</" + name + ">";
        return code;
    }
};
int main1(){
    std::string words[] = {"Hello", "world"};
    HtmlElement list("ul", "");
    for(auto w : words)
        list.elems.push_back( HtmlElement("li", w) );
    std::cout << list.str(4) << std::endl;
    return 0 ;
}

// Using Simpler Builder pattern
struct HtmlBuilder{
    HtmlElement root;
    HtmlBuilder(std::string root_name){root.name = root_name;}
    HtmlBuilder* add_child(std::string child_name, std::string child_text){
        HtmlElement e{child_name, child_text};
        root.elems.push_back(e);
        return this;
    }
    std::string str(int ident=0)const {
        std::string code = "", pad;
        code += "<" + root.name + ">";
        switch (ident)
        {
        case 0: pad = "";break;
        case 1: pad = " ";break;
        case 2: pad = "  ";break;
        case 3: pad = "   ";break;
        case 4: pad = "    ";break;
        default: std::cout << "Error ident no setted" << std::endl;break;
        }
        // code += "\n" + pad;
        code += " " + root.text + " ";
        for(auto e : root.elems)
            code += pad + e.str();
        code += "</" + root.name + ">";
        return code;
    }
};
int main(){
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "Hello")->add_child("li", "world");
    std::cout << builder.str() << std::endl;

    return 0;
}