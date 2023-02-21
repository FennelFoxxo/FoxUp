#include <vector>
#include "player.h"
#include "point.h"
#include "globals.h"
#include "platform.h"
#include "utility.h"
#include <iostream>

Player::Player() {}

Player::Player(Point starting_pos) {
    this->pos = starting_pos;
    this->vel = Point(0,0);
    
    this->facing_right = false;
    this->in_air = false;
    this->falling = false;
    this->dead = false;
    
    this->walking_width = all_sprites["walk_left"].texture->w;
    
    this->update_sprite();
}

void Player::update(Uint8 key_inputs, std::vector<Platform> platform_list) {
    if (key_inputs & 1) {
        this->vel.x -= PLAYER_X_AIR_SPEED*TICKS_PASSED; //Move left
    }
    if (key_inputs & 2) {
        this->vel.x += PLAYER_X_AIR_SPEED*TICKS_PASSED; //Move right
    }
    if (abs(this->vel.x) > PLAYER_TURN_THRESHOLD) { //Turn left or right if only above certain threshold, so the sprite doesn't flip left/right too fast
        if (this->vel.x > 0) {
            this->facing_right = true;
        } else {
            this->facing_right = false;
        }
    }

    this->vel.y -= GRAVITY*TICKS_PASSED;
    
    this->pos = this->pos + (this->vel*TICKS_PASSED);

    if (this->pos.x - this->walking_width/2.0 < 0) { //Make sure edge of sprite doesn't go off left edge of screen
        this->pos.x = this->walking_width/2.0;
        if (this->vel.x < 0) {
            this->vel.x = 0;
        }
    }
    if (this->pos.x + this->walking_width/2.0 > RES_X) { //Make sure edge of sprite doesn't go off right edge of screen
        this->pos.x = RES_X - this->walking_width/2.0;
        if (this->vel.x > 0) {
            this->vel.x = 0;
        }
    }

    this->update_sprite();
    this->my_hitbox.top_left = Point(this->pos.x - this->current_width/2.0, this->pos.y + this->current_height);
    this->my_hitbox.calculateCorners();
    this->my_hitbox.abs_bottom_right.y -= 0.1; //Hack so the player doesn't quickly alternate between on a platform and falling, because of a rounding error
    
    bool on_platform = false;
    double platform_y = world_height*SCALE;
    
    if (this->vel.y <= 0) { //Only do collisions with platforms if the player is moving down
        for (auto platform = platform_list.begin(); platform != platform_list.end(); platform++) { //For every platform...
            if (this->my_hitbox.colliding_with(platform->my_hitbox)) { //Check if player is colliding, then if the player is...
                on_platform = true; //You should be able to understand this one
                platform_y = platform->my_hitbox.abs_top_left.y; //Store the platform's y position
            }
        }
    }

    if (this->pos.y < world_height*SCALE) {
        this->dead = true;
        IS_GAME_STARTED = false;
    }
    
    if (on_platform) { //If on a platform
        //std::cout << SCORE+1000 << std::endl;
        this->in_air = false;
        if (this->vel.y < 0) {
            this->vel.y = 0; //Make sure velocity is positive
        }
        if (true) {//(this->pos.y < platform_y) {
            this->pos.y = platform_y; //Make sure player doesn't go below the platform
        }
        if (key_inputs & 4) {
            this->vel.y = PLAYER_JUMP_SPEED; //Allow the player to jump
            IS_GAME_STARTED = true; //Also start the game, this is very important
        }
        this->vel.x /= (PLAYER_FRICTION*TICKS_PASSED) + 1; //Slow the player, due to friction
        if (key_inputs & 1) {
            this->vel.x -= PLAYER_X_GROUND_SPEED*TICKS_PASSED; //Because PLAYER_X_AIR_SPEED is negligible compared to this, this is pretty much the speed the player will move at when on a platform
        }
        if (key_inputs & 2) {
            this->vel.x += PLAYER_X_GROUND_SPEED*TICKS_PASSED; //Same deal as above, except for moving right
        }
    } else { //If not on a platform
        //std::cout << SCORE << std::endl;
        this->in_air = true;
        if (this->vel.y  < 0) {
            this->falling = true;
        } else {
            this->falling = false;
        }
    }
    
    this->update_sprite();
    
}

void Player::update_sprite() {
    if (this->facing_right) {
        if (this->in_air) {
            if (this->falling) {
                this->my_sprite = all_sprites["fall_right"];
            } else {
                this->my_sprite = all_sprites["jump_right"];
            }
        } else {
            this->my_sprite = all_sprites["walk_right"];
        }
    } else {
        if (this->in_air) {
            if (this->falling) {
                this->my_sprite = all_sprites["fall_left"];
            } else {
                this->my_sprite = all_sprites["jump_left"];
            }
        } else {
            this->my_sprite = all_sprites["walk_left"];
        }
    }
    this->current_width = this->my_sprite.texture->w;
    this->current_height = this->my_sprite.texture->h;

    this->my_hitbox.width = this->my_sprite.hb_width;
    this->my_hitbox.height = this->my_sprite.hb_height;
    this->my_hitbox.offset = Point(this->my_sprite.hb_tlx, this->my_sprite.hb_tly);
}

void Player::blit() {
    int blit_x = this->pos.x - this->current_width/2.0;
    int blit_y = world_y_to_screen_y(this->pos.y + this->current_height);

    SDL_Rect rect = make_rect(blit_x, blit_y, 0, 0);
    SDL_BlitSurface(this->my_sprite.texture, NULL, gScreenSurface, &rect);
    
}