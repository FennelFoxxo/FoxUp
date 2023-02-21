#include <map>
#include <fstream>
#include <vector>
#include <tuple>
#include <iostream>
#include <SDL_image.h>
#include "utility.h"
#include "globals.h"
#include "sprite.h"

double world_y_to_screen_y(double y_pos) {
    return RES_Y - y_pos + world_height*SCALE;
}

double screen_y_to_world_y(double y_pos) {
    return world_y_to_screen_y(y_pos);
}

SDL_Surface* scale_surface(SDL_Surface* surface_to_scale, int scale) {
    SDL_Rect stretch_rect;
    SDL_Surface* scaled_surface;
    
    stretch_rect.x = 0;
    stretch_rect.y = 0;
    stretch_rect.w = surface_to_scale->w * scale;
    stretch_rect.h = surface_to_scale->h * scale;
    
    scaled_surface = SDL_CreateRGBSurface(0, stretch_rect.w, stretch_rect.h, surface_to_scale->format->BitsPerPixel, surface_to_scale->format->Rmask, surface_to_scale->format->Gmask, surface_to_scale->format->Bmask, surface_to_scale->format->Amask);
    SDL_BlitScaled(surface_to_scale, NULL, scaled_surface, &stretch_rect);
    return scaled_surface;
}

std::vector<std::string> split_string(std::string str, char delimiter) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> splitted;
    
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        splitted.push_back(token);
        str.erase(0, pos+1);
    }
    splitted.push_back(str);
    
    return splitted;
}

std::map<std::string, Sprite> loadSprites() {
    std::map<std::string, Sprite> sprite_dict;

    SDL_Surface* sprite_texture;
    
    std::vector<std::string> line_split;
    std::string line;
    std::ifstream hitbox_file("sprites/hitboxes.txt");
    
    if (hitbox_file.is_open()) {
        while (std::getline(hitbox_file, line)) {
            line_split = split_string(line, ';');

            sprite_texture = IMG_Load((std::string("sprites/") + line_split[0] + ".png").c_str());
            sprite_texture = scale_surface(sprite_texture, SCALE);

            sprite_dict.insert(std::make_pair(line_split[0], Sprite {
                sprite_texture,
                std::stod(line_split[1])*SCALE,
                std::stod(line_split[2])*SCALE,
                std::stod(line_split[3])*SCALE,
                std::stod(line_split[4])*SCALE
            }));
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return sprite_dict;
}

SDL_Rect make_rect(int x, int y, int w, int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    
    return rect;
}

Uint8 get_keyboard_inputs() {
    Uint8 state = 0;
    
    if (KEY_STATE_POINTER[SDL_SCANCODE_LEFT] or KEY_STATE_POINTER[SDL_SCANCODE_A]) {
        state |= 1;
    }
    
    if (KEY_STATE_POINTER[SDL_SCANCODE_RIGHT] or KEY_STATE_POINTER[SDL_SCANCODE_D]) {
        state |= 2;
    }
    
    if (KEY_STATE_POINTER[SDL_SCANCODE_UP] or KEY_STATE_POINTER[SDL_SCANCODE_W] or KEY_STATE_POINTER[SDL_SCANCODE_SPACE]) {
        state |= 4;
    }

    return state;
}