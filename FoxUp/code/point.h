#ifndef POINT
#define POINT

class Point {
public:
    double x;
    double y;
    
    Point();
    Point(double, double);
    
    Point operator+(Point);
    Point operator-(Point);
    Point operator*(double);
    Point operator/(double);
};

#endif