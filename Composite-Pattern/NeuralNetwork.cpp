#include <vector>
#include <iostream>
struct Neuron;

template<typename Self>
struct SomeNeurons{
    template<typename T> void connectTo(T&other);
    
    //virtual Self* begin()=0;
    //virtual Self* end()=0;
};

struct Neuron: public SomeNeurons<Neuron>
{
    std::vector<Neuron> ins, outs;
    unsigned int id;
    Neuron(){static unsigned int id=1; this->id = id++;} // static in a function means that is the same id for all calls?
    Neuron* begin(){return this;}
    Neuron* end(){return this + 1;}
};

struct Layer: std::vector<Neuron>, SomeNeurons<Layer> // why not Neuron* or unique_ptr<Neuron>, we are saving actual neurons objects
{
    Layer(int n){while (n-->0)this->emplace_back(Neuron{}); }
};

template<typename Self>
template<typename T> 
void SomeNeurons<Self>::connectTo(T&other){
        for (Neuron& from: *static_cast<Self*>(this)) // why self* as pointer , can be <Self>(*this)
            for(Neuron& to: other)                   // casting is ok because this is of Self class actually, at least how we use SomeNeuron template class
            {                                       // why dereferencing the result of static_cast?
                from.outs.emplace_back(to);
                to.ins.emplace_back(from);
            }
    }

int main(){
    Neuron n1{}, n2{};
    Layer l1{4}, l2{10};

    n1.connectTo(l1);
    l2.connectTo(l1);
    std::cout << "Connected?" << std::endl;
}