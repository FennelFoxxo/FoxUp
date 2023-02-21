#include <vector>
#include <cmath>
#include <iostream>
#include "platform.h"
#include "globals.h"

void pregenerate_platforms(std::vector<Platform>& all_platforms) {

    world_height = -RES_Y/SCALE; //Makes the bottom of the first platform touch the bottom of the screen

    all_platforms.push_back(Platform(128, rand()%2 + 1)); //Make starting platform

    world_height += SPACE_BETWEEN_PLATFORMS;
    
    while (world_height <= 0) { //Make platforms until they would start to go above the top of the screen
        if (rand()%2 == 0) { all_platforms.push_back(Platform(20, rand()%2+1)); } else //50% chance for 20 pixel long platform
                           { all_platforms.push_back(Platform(40, rand()%2+1)); } //50% chance for 40 pixel long platform
        world_height += SPACE_BETWEEN_PLATFORMS; //Make sure to increase the height, so the next platform has a different y
    }

    LAST_PLATFORM_HEIGHT = world_height - SPACE_BETWEEN_PLATFORMS; //Make sure the next platform will spawn at the right time
    
    world_height = 0; //Make sure world_height ends up at 0
    
}