#include "sprite.h"
#include "hitbox.h"

#ifndef PLATFORM
#define PLATFORM

class Platform {
public:
    Sprite my_sprite;
    Hitbox my_hitbox;
    int x;
    int y;
    int width;
    int height;
    bool can_delete;

    Platform(int, int);
    void blit();
    
};


#endif