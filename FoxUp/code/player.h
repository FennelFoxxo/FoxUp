#include <vector>
#include "point.h"
#include "platform.h"
#include "sprite.h"
#include "hitbox.h"

#ifndef PLAYER
#define PLAYER

class Player {
public:
    Point pos;
    Point vel;
    
    int walking_width;
    int current_width;
    int current_height;
    
    bool facing_right;
    bool in_air;
    bool falling;
    bool dead;
    
    Sprite my_sprite;
    Hitbox my_hitbox;
    
    Player();
    Player(Point);
    void update(Uint8, std::vector<Platform>);
    void update_sprite();
    void blit();
    
};


#endif