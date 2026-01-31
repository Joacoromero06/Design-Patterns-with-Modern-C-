#include <iostream>
#include <vector>
struct  Neuron
{
    std::vector<Neuron*> ins, outs;
    unsigned int id;
    Neuron(){
        static unsigned int id = 1;
        this->id = id++;
    }
    template<>void connectTo<Neuron>(Neuron& other){
        outs.push_back(&other);
        other.ins.push_back(this);
    }
};
struct Layer: public std::vector<Neuron> // why not vector<Neuron* or unique_ptr<Neuron>>
{
    Layer(int m){
        while(m-->0)
            this->emplace_back(Neuron{});
    }
};

/* the problem is connect to is a not well think function, 
we should make connecTo<Neuron>(Neuron& other and LAyer& other)
the same for layer, and if another class appear this is terrible
*/