#include "globals.h"
#include "sprite.h"
#include "point.h"

int SCALE = 6;
int RES_X = 128*SCALE;
int RES_Y = 128*SCALE;
double world_height = 0;
int FPS = 1000;
double TICKS_PER_FRAME = 60.0 / FPS;
int TICKS_PASSED = TICKS_PER_FRAME;

int SPACE_BETWEEN_PLATFORMS = 50;
int LAST_PLATFORM_HEIGHT = -SPACE_BETWEEN_PLATFORMS;
double GAME_SPEED_START = 0.01;
double GAME_SPEED_AFTER_ACC = GAME_SPEED_START;
double GAME_SPEED_CURRENT = GAME_SPEED_START;
double GAME_ACCELERATION = 0.0000003;

double PLAYER_X_AIR_SPEED = 0.000065*SCALE;
double PLAYER_X_GROUND_SPEED = 0.0003*SCALE;
double PLAYER_JUMP_SPEED = 0.13*SCALE;
double PLAYER_FRICTION = 0.01;
double PLAYER_TURN_THRESHOLD = 0.02;
double GRAVITY = 0.00016*SCALE;

bool IS_GAME_STARTED = false;

int SCORE = 0;
int PREV_SCORE = 0;
double SCORE_SCALE = 1;

double SCORE_TEXT_SCALE = 0.8*SCALE;
Point SCORE_TEXT_LOCATION = Point(0.64*RES_X, 0.03*RES_Y);
int PREV_SCORE_Y_ADJ = 7*SCALE;


const Uint8* KEY_STATE_POINTER;

std::map<std::string, Sprite> all_sprites;