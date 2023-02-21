#include <map>
#include <vector>
#include <SDL.h>
#include "sprite.h"

#ifndef UTILITY
#define UTILITY

double world_y_to_screen_y(double);

double screen_y_to_world_y(double);

SDL_Surface* scale_surface(SDL_Surface*, int);

std::vector<std::string> split_string(std::string, char);

std::map<std::string, Sprite> loadSprites();

SDL_Rect make_rect(int, int, int, int);

Uint8 get_keyboard_inputs();

#endif