

/* ======================================================================
*  |         NARRATIVE: General sitution.                               |
*  ======================================================================
*
*   Imagine you are bouldin a physics engine. You HAVE a Particle class.
*   You need to apply forces to it: "Gravity", "Drag", "Springs"
*   Also user-defined forces like "Wind" or "Explosions".
*/


/* ======================================================================
*  |         Dynamic Polymorphis: Editor phase                          |
*  ======================================================================
*
*   You are building the GUI Editor for your engine.
*   The user can add any number of forces to a particle at runtime
*
*   You as programmer, have no idea what forces the user will pick when you compile the code
*   eg: add 10 gravity or 5 springs.
*/

#include <vector>
#include <iostream>

// Abstract class
class ForceGenerator{
public:
    virtual void applyForce(float particleMass) = 0; // virtuals lets child defines it
    virtual ~ForceGenerator(){} // virtual destructor
};

// Concrete implementation 
class Gravity: public ForceGenerator{
public:
    void applyForce(float particleMass){
        std::cout << "Applying force: " << particleMass * -9.8f << std::endl;        
    }
};
class Drag: public ForceGenerator{
public:
    void applyForce(float particleMass){
        std::cout << "Applying drag resistance" << std::endl;        
    }
};

int main1(void){
    // We hold a list of pointer to base class
    std::vector<ForceGenerator*> forces;
    forces.push_back(new Gravity());
    forces.push_back(new Drag());
    for(auto f : forces){
        float particleMass = 10.0f;
        f->applyForce(particleMass);
    }
    return 0;
}

/*
*   The game started, we are in inner loop of physic engime, with 1,000,000 particles.
*   The VTable look up from dynamyc polymorphism is causing cache miss, too slow.
*   You realize, the specific level, only use Gravity.
*   
*   Use templates, to tell compiler what type are using, so compiler hard code the function call
* */

// NO inheritance needed
class Gravity2{
public: 
    void applyForce(float particleMass){
        std::cout << "Applying force: " << particleMass*-9.8f << std::endl;
    }
};
class Drag2{
public:
    void applyForce(float particleMass){
        std::cout << "Drag force applying" << std::endl;
    }
};

// template function
template <typename T>
void runSimulationStep(T& forceStrategy, float mass){
    forceStrategy.applyForce(mass);
}

int main2(void){
    Gravity g;
    Drag d;

    runSimulationStep(g,10.f);
    runSimulationStep(d,10.f);

    return 0;
}


/*
*   You have a particle class, sometimes you want a particles that logs its position to a file
*   just for debugging, sometimes you want a particle that renders a label on screen.
*   
*   You dont want to create a complex inheritance tree like:
*   class LoggedParticle: public Particle or class LabeledParticle: public Particle
*
*   Mixin pattern, create a wrapper that adds functionality to whatever class you give it.
*/
class Particle{
public:
    void move(){std::cout << "PArticle moving: Integrate steps" << std::endl;}
};
class RigidBody{
public:
    void move(){std::cout << "RigidBody moving: Integrate steps" << std::endl;}
};
template<typename T>
class Logger: T{
public:
    void log(){ // can redifine move method, Logger is a child class of T class
        std::cout << "[LOG] obj is about to move" << std::endl;
        T::move();
        std::cout << "[LOG] move finished" << std::endl;
    }
};
int main(void){
    // if try given a instance as a typename dont work
    Logger<Particle> p;
    p.log();
    Logger<RigidBody> rb;
    rb.log();
    return 0;
}