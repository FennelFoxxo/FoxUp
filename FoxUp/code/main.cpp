/*
Compiler
Include paths: .;C:\mingw_dev_lib\include\SDL2;C:\mingw_dev_lib\lib
Linker
Linker Options: -s;-static;-lsetupapi;-lhid;-mwindows;-lole32;-loleaut32;-lversion;-lwinmm;-limm32;-lm;-liconv;-lSDL2_image
Libraries Search Path: C:\mingw_dev_lib\lib\
Libraries: libSDL2main.a;libSDL2.a;libSDL2_image.a
*/

//Using SDL and standard IO

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <map>
#include <iostream>
#include <vector>
#include "globals.h"
#include "point.h"
#include "hitbox.h"
#include "utility.h"
#include "utility2.h"
#include "sprite.h"
#include "platform.h"
#include "timer.h"
#include "player.h"
#include "custom_font.h"
#include "custom_font_data.h"

//Screen dimension constants

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;

//The image we will load and show on the screen
SDL_Surface* gFontSurface = NULL;

Player player;
std::vector<Platform> all_platforms;

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};


bool initSDL() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    
    //Create window
    gWindow = SDL_CreateWindow("FoxUp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RES_X, RES_Y, SDL_WINDOW_SHOWN);
    
    if(gWindow == NULL) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    
    int imgFlags = IMG_INIT_PNG;
    if( !(IMG_Init(imgFlags) & imgFlags) ) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }
    
    //Get window surface
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    gRenderer = SDL_GetRenderer(gWindow);
    
    return true;
}

void closeSDL() {
    //Deallocate surface
    SDL_FreeSurface(gFontSurface);
    gFontSurface = NULL;
    
    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
}

void initGame() {
    GAME_SPEED_AFTER_ACC = GAME_SPEED_START;
    GAME_SPEED_CURRENT = GAME_SPEED_START;
    world_height = 0;
    SCORE = 0;

    all_platforms.clear();
    pregenerate_platforms(all_platforms);

    player = Player(Point(RES_X/2.0, all_platforms.begin()->my_hitbox.abs_top_left.y));
}

int main( int argc, char* args[] ) {

    if (!initSDL()) {
        return 1;
    }

    all_sprites = loadSprites();
    
    initGame();

    font game_font = *load_font(dot_matrix_font);
    game_font.size = SCORE_TEXT_SCALE;
    game_font.dot_scale = 1;
    gFontSurface = game_font.set_blank_surface(20);
    
    Uint8 key_inputs;
    
    Timer fps_timer;
    
    SDL_Rect score_rect;
    
    KEY_STATE_POINTER = SDL_GetKeyboardState(NULL);

    bool quit = false;
    
    SDL_Event e;

    while (!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        fps_timer.start();
        
        SDL_FillRect(gScreenSurface, NULL, 0x808080);
        
        if (world_height - LAST_PLATFORM_HEIGHT > SPACE_BETWEEN_PLATFORMS) {
            //all_platforms.push_back(Platform(128, rand()%2 + 1));
            all_platforms.push_back(Platform((rand()%2 + 1)*20, rand()%2 + 1));
            LAST_PLATFORM_HEIGHT = world_height;
        }
        
        for (auto platform = all_platforms.begin(); platform != all_platforms.end(); platform++) {
            platform->blit();
        }
        
        if (all_platforms.size()) {
            if (all_platforms[0].can_delete) { //Unless we're making more than one platform every tick, this should be plenty
                all_platforms.erase(all_platforms.begin());
            }
        }
        
        key_inputs = 0;
        key_inputs = get_keyboard_inputs();
        
        
        player.blit();
        
        SCORE = world_height*SCORE_SCALE;
        
        //Render score
        game_font.set_color(255,255,255);
        game_font.render_text(std::string(" SCORE:") + std::to_string(SCORE), gFontSurface);
        score_rect = make_rect(SCORE_TEXT_LOCATION.x, SCORE_TEXT_LOCATION.y, 0, 0);
        SDL_BlitSurface(gFontSurface, NULL, gScreenSurface, &score_rect);
        
        if (SCORE >= PREV_SCORE) {
            PREV_SCORE = SCORE;
            game_font.set_color(255,64,64);
        }

        //Render previous score, using old rect and surface
        score_rect.y += PREV_SCORE_Y_ADJ;
        game_font.render_text(std::string("RECORD:") + std::to_string(PREV_SCORE), gFontSurface);
        SDL_BlitSurface(gFontSurface, NULL, gScreenSurface, &score_rect);
        
        //Update the surface
        SDL_UpdateWindowSurface(gWindow);

        TICKS_PASSED = fps_timer.getTicks();
        if (TICKS_PASSED < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME - TICKS_PASSED);
        }
        TICKS_PASSED = fps_timer.getTicks();
        
        //std::cout << TICKS_PASSED << std::endl;
        //std::cout << world_height << std::endl;
        
        //All this stuff is after the delay, so we can scale it by the time elapsed. This makes sure the game runs at the same speed, even if at a lower framerate

        player.update(key_inputs, all_platforms);

        if (player.dead) {
            initGame();
        }
        
        if (IS_GAME_STARTED) {
            GAME_SPEED_AFTER_ACC += GAME_ACCELERATION*TICKS_PASSED;
            GAME_SPEED_CURRENT = GAME_SPEED_AFTER_ACC + (player.pos.y - world_height*SCALE)/SCALE/3500;
            world_height += GAME_SPEED_CURRENT*TICKS_PASSED;
        }


    }
    
    closeSDL();
    
    return 0;
}