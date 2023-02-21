#include <SDL.h>
#include <map>
#include "sprite.h"
#include "point.h"

#ifndef GLOBALS
#define GLOBALS


extern int SCALE;
extern int RES_X;
extern int RES_Y;
extern double world_height;
extern int FPS;
extern double TICKS_PER_FRAME;
extern int TICKS_PASSED;

extern int SPACE_BETWEEN_PLATFORMS;
extern int LAST_PLATFORM_HEIGHT;
extern double GAME_SPEED_START;
extern double GAME_SPEED_AFTER_ACC;
extern double GAME_SPEED_CURRENT;
extern double GAME_ACCELERATION;

extern double PLAYER_X_AIR_SPEED;
extern double PLAYER_X_GROUND_SPEED;
extern double PLAYER_JUMP_SPEED;
extern double PLAYER_FRICTION;
extern double PLAYER_TURN_THRESHOLD;
extern double GRAVITY;

extern bool IS_GAME_STARTED;

extern int SCORE;
extern int PREV_SCORE;
extern double SCORE_SCALE;

extern double SCORE_TEXT_SCALE;
extern Point SCORE_TEXT_LOCATION;
extern int PREV_SCORE_Y_ADJ;

extern const Uint8* KEY_STATE_POINTER;

extern SDL_Surface* gScreenSurface;

extern std::map<std::string, Sprite> all_sprites;

#endif