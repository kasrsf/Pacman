#ifndef CONSTANTS_H
#define CONSTANTS_H

static const int PORTAL_LEFT_X = -1;
static const int PORTAL_LEFT_Y = 14; 

static const int PORTAL_RIGHT_X = 28;
static const int PORTAL_RIGHT_Y = 14;

static const int MODE_RIGHT = 0;
static const int MODE_LEFT = 1;
static const int MODE_UP = 2;
static const int MODE_DOWN = 3;
static const int MODE_DYING = 4;
static const int NUM_OF_MODES = 5;

const int TILE_WIDTH = 20;
const int TILE_HEIGHT = 20;

const int CLIP_WIDTH = 30;
const int CLIP_HEIGHT = 30;

const int TILES_PER_ROW = 28;
const int TILES_PER_COL = 31;

const int NUM_OF_TILES = TILES_PER_COL * TILES_PER_ROW;

const int BOTTOM = 50;

const int SCREEN_WIDTH = TILES_PER_ROW * TILE_WIDTH;
const int SCREEN_HEIGHT = (TILES_PER_COL * TILE_HEIGHT) + BOTTOM;

const int FRAMES_PER_SECOND = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / FRAMES_PER_SECOND;

const int NOTHING = 0;
const int SMALL_DOT = 1;
const int LARGE_DOT = 2;
const int WALL = 3;
const int FENCE = 4;
const int GHOST = 5;
const int TILE_TYPES = 6;

const int LAZY_FONT = 0;

const int WHITE_COLOR = 0;

const int SCORE_POS_X = 10;
const int SCORE_POS_Y = 630;

const int SCORE_TEXT_SIZE = 28;

const int GHOST_HOUSE_STARTX = 10;
const int GHOST_HOUSE_ENDX = 17;
const int GHOST_HOUSE_STARTY = 12;
const int GHOST_HOUSE_ENDY = 16;

const int GHOST_HOUSE_EXITX = 13;
const int GHOST_HOUSE_EXITY = 11;

const int PACMAN_STARTX = 270;
const int PACMAN_STARTY = 340;


static const int CLYDE_STARTX = 220;
static const int CLYDE_STARTY = 300;

static const int CLYDE_SCATTERX = 0;
static const int CLYDE_SCATTERY = 31;

const int CLYDE_TRAIL_RADIUS = 8;

static const int BLINKY_STARTX = 220;
static const int BLINKY_STARTY = 260;

static const int BLINKY_SCATTERX = 25;
static const int BLINKY_SCATTERY = 0;

static const int PINKY_STARTX = 320;
static const int PINKY_STARTY = 260;

static const int PINKY_SCATTERX = 1;
static const int PINKY_SCATTERY = -1;

static const int PINKY_TARGET_OFFSET = 4;

static const int INKY_STARTX = 320;
static const int INKY_STARTY = 300;

static const int INKY_SCATTERX = 25;
static const int INKY_SCATTERY = 31;

static const int INKY_TARGET_OFFSET = 2;

static const int GHOST_SCATTER_INTERVAL = 10000; // miliseconds

static const int CHASE_MODE_DURATION = 7000; //miliseconds

static const int GHOST_DEATH_DURATION = 5000;

static const int BLINKY_ID = 0;
static const int INKY_ID = 1;
static const int PINKY_ID = 2;
static const int CLYDE_ID = 3;

#endif
