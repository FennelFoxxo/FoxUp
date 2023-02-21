#include "hitbox.h"
#include "point.h"
#include "globals.h"
#include "utility.h"
#include <iostream>

Hitbox::Hitbox(double width, double height, Point offset, Point top_left) {
    this->width = width;
    this->height = height;
    this->offset = offset;
    this->top_left = top_left;
    this->calculateCorners();
}

Hitbox::Hitbox() {
    this->width = 0;
    this->height = 0;
    this->offset = Point();
    this->top_left = Point();
}

void Hitbox::calculateCorners() {
    this->abs_top_left = this->top_left + this->offset;
    this->abs_bottom_right = this->abs_top_left + Point(this->width, -this->height);
}

bool Hitbox::point_inside(Point p) {
    if ((p.x <= this->abs_top_left.x) or (p.x >= this->abs_bottom_right.x)) { return false; }
    if ((p.y <= this->abs_bottom_right.y) or (p.y >= this->abs_top_left.y)) { return false; }
    return true;
}

bool Hitbox::colliding_with(Hitbox h2) {
    if ((this->abs_top_left.x >= h2.abs_bottom_right.x) or (h2.abs_top_left.x >= this->abs_bottom_right.x)) { return false; }
    if ((this->abs_top_left.y <= h2.abs_bottom_right.y) or (h2.abs_top_left.y <= this->abs_bottom_right.y)) { return false; }
    return true;
}

void Hitbox::debug_show_corners() {
    SDL_Rect rect;
    rect.w = 5;
    rect.h = 5;
    
    rect.x = this->abs_top_left.x;
    rect.y = world_y_to_screen_y(this->abs_top_left.y);
    
    SDL_FillRect(gScreenSurface, &rect, SDL_MapRGB(gScreenSurface->format, 255, 0, 0));

    rect.x = this->abs_bottom_right.x;

    SDL_FillRect(gScreenSurface, &rect, SDL_MapRGB(gScreenSurface->format, 0, 255, 0));
    
    rect.y = world_y_to_screen_y(this->abs_bottom_right.y);

    SDL_FillRect(gScreenSurface, &rect, SDL_MapRGB(gScreenSurface->format, 0, 0, 255));
    
    rect.x = this->abs_top_left.x;

    SDL_FillRect(gScreenSurface, &rect, SDL_MapRGB(gScreenSurface->format, 255, 255, 0));
}