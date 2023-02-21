#include <math.h>
#include <iostream>
#include "platform.h"
#include "globals.h"
#include "sprite.h"
#include "hitbox.h"
#include "point.h"
#include "utility.h"

Platform::Platform(int size, int version) {
    std::string version_string = std::to_string(size) + "w_" + std::to_string(version);
    this->my_sprite = all_sprites[version_string];
    this->width = this->my_sprite.texture->w;
    this->height = this->my_sprite.texture->h;
    
    int min_x = ceil(this->width/2.0);
    int max_x = floor(RES_X - this->width/2.0);

    if (min_x >= max_x) {
        this->x = min_x;
    } else {
        this->x = rand()%(max_x-min_x) + min_x;
    }

    this->y = screen_y_to_world_y(-this->height);
    
    this->can_delete = false;

    this->my_hitbox = Hitbox(this->my_sprite.hb_width, this->my_sprite.hb_height, Point(this->my_sprite.hb_tlx, this->my_sprite.hb_tly), Point(this->x - this->width/2.0, this->y));
}

void Platform::blit() {
    int blit_x = round(this->x - this->width/2.0);
    int blit_y = round(world_y_to_screen_y(this->y));
    SDL_Rect rect = make_rect(blit_x, blit_y, 0, 0);
    SDL_BlitSurface(this->my_sprite.texture, NULL, gScreenSurface, &rect);
    
    if (this->y < world_height*SCALE) {
        this->can_delete = true;
    }
}