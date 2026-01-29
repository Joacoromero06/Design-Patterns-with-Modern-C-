#include <boost/functional/hash.hpp>

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <iostream>
#include <map>
#define DEBUG(msg) std::cout << "["<< __FILE__ <<"]" << "["<< __LINE__ <<"] : " << msg << std::endl;
#define min(x,y) ((x) < (y))? (x): (y) 
#define max(x,y) ((x) > (y))? (x): (y) 

struct Point{
    int x, y; 
    Point(int x, int y): x{x}, y{y} {}
    friend std::size_t hash_value(const Point& p){ // where is this method used?
        std::size_t seed = 0x725C686F;
        boost::hash_combine(seed, p.x); 
        boost::hash_combine(seed, p.y);
        return seed;
    }
};
struct Line{
    Point start, end; 
    Line(Point s, Point e): start{s}, end{e} {}
    friend std::size_t hash_value(const Line& l){ // where is this method used?
        std::size_t seed = 0x22ACF;
        boost::hash_combine(seed, l.start); // hash_combine search for hash_value of point?
        boost::hash_combine(seed, l.end);
        return seed;
    }
};
struct VectorObject{
    virtual std::vector<Line>::iterator begin()=0;
    virtual std::vector<Line>::iterator end()=0;
};
struct VectorRectangle: public VectorObject{
private:
    std::vector<Line> lines;
public:
    VectorRectangle(int x, int y, int width, int height){
        lines.emplace_back(Line{ Point{x,y}       , Point{x+width, y}       });
        lines.emplace_back(Line{ Point{x,y}       , Point{x, y+height}      });
        lines.emplace_back(Line{ Point{x+width,y} , Point{x+width, y+height}});
        lines.emplace_back(Line{ Point{x,y+height}, Point{x+width, y+height}});
    }
    std::vector<Line>::iterator begin()override{ return lines.begin(); }
    std::vector<Line>::iterator end()override{ return lines.end(); }
};

// adapter, we have lines to draw, but only know how to draw points
struct Line2Point{
    typedef std::vector<Point> Points;
    static std::map<std::size_t, Points> cache;
private:
    std::size_t line_hash;
    Points points;
public:
    virtual Points::iterator begin(){return cache[line_hash].begin();} // why virtual?
    virtual Points::iterator end()  {return cache[line_hash].end();}
    Line2Point(Line& line){
        static boost::hash<Line> hash; // hash search for hash_value function?
        line_hash = hash(line);

        if(cache.find(line_hash) != cache.end())
            return; // already exists
        int left   = min(line.start.x, line.end.x);
        int right  = max(line.start.x, line.end.x);
        int top    = max(line.start.y, line.end.y);
        int bottom = min(line.start.y, line.end.y);
        if(left - right == 0)
            for(int i=bottom; i<= top; i++)
                points.emplace_back(Point{left, i});
        else if(top - bottom == 0)
            for(int i=left; i <= right; i++)
                points.emplace_back(Point{bottom, i});
        else 
            DEBUG("erro solo lineas horizontales o vertical R^2")
    }
};
std::map<std::size_t, Line2Point::Points> Line2Point::cache; 


// incomplete type "void" is not allowedC/C++(70)
void drawPoints(SDL_Renderer* render, std::vector<Point>::iterator start, std::vector<Point>::iterator end){
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    for(auto it=start; it!=end; it++)
        SDL_RenderDrawPoint(render, it->x, it->y);
}
int main(){
    if (SDL_Init(SDL_INIT_VIDEO) < 1){DEBUG("no se inicializo");}
    SDL_Window* window = SDL_CreateWindow(
        "Drawing geometry objects",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(render, 255,255,255,255);
    SDL_RenderClear(render);

    std::vector<std::shared_ptr<VectorObject>> objs{
        std::make_shared<VectorRectangle>(10,10, 50,50),
        std::make_shared<VectorRectangle>(5, 5, 70, 100)
    };
    for(auto& obj:objs)
        for(auto& line:*obj){
            Line2Point points{line};
            drawPoints(render, points.begin(), points.end());
        }


    // drawPoints()..

    SDL_RenderPresent(render);
    SDL_Delay(4000);

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}