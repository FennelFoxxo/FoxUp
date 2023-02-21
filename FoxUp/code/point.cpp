#include "Point.h"

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Point Point::operator+(Point c2) {
    return Point(this->x + c2.x, this->y + c2.y);
}

Point Point::operator-(Point c2) {
    return Point(this->x - c2.x, this->y - c2.y);
}

Point Point::operator*(double s) {
    return Point(this->x * s, this->y * s);
}

Point Point::operator/(double s) {
    return Point(this->x / s, this->y / s);
}