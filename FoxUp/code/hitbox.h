#include <SDL.h>
#include "Point.h"

#ifndef HITBOX
#define HITBOX

class Hitbox {
public:
    double width;
    double height;
    Point top_left;
    Point offset;
    Point abs_bottom_right;
    Point abs_top_left;
    
    Hitbox(double, double, Point, Point);
    Hitbox();

    void calculateCorners();
    
    bool point_inside(Point);
    bool colliding_with(Hitbox);
    
    void debug_show_corners();
    

};

#endif
