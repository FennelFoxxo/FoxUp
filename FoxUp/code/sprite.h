#include <SDL.h>

#ifndef SPRITE
#define SPRITE

struct Sprite {
    SDL_Surface* texture;
    double hb_tlx; //Hitbox top left x pos
    double hb_tly; //Hitbox top left y pos
    double hb_width; //Width of hitbox
    double hb_height; //Height of hitbox
};

#endif