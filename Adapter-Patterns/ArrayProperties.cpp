#include <array>
#include <algorithm>
#include <numeric>
#define max(a,b) ((a)>(b))? (a):(b)
struct Criature1{ // error prone, no open to add features
    int s, i, h;
    Criature1(int s, int i, int h): s{s}, i{i}, h{h} {}
    // all getter setters
    int sumStatistics(){return s+i+h;}
    int avarageStatistics(){return sumStatistics()/3;}
    int maxStatitistic(){return max(s,max(i,h));}
};
struct Criature{
    enum Abilities{STRENGTH=0, AGILITY, INTELLIGENCE, N};
    std::array<int, N> abilities;

    int getStrength(){return abilities[STRENGTH];}
    void setStrength(int strength){ abilities[STRENGTH]=strength;}
    // ...
    int sumStatistics(){return std::accumulate(abilities.begin(), abilities.end(), 0);}
    float avarageStatistics(){return sumStatistics()/N;}
    int maxStatistics(){return *std::max_element(abilities.begin(), abilities.end());}
};