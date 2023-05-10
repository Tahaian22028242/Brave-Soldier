#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


//Audio
static Mix_Chunk* g_background_music = NULL;
static Mix_Chunk* g_menu_music = NULL;
static Mix_Chunk* g_game_over_music = NULL;
static Mix_Chunk* g_sound_bullet_main = NULL;
static Mix_Chunk* g_sound_bullet_threats = NULL;
static Mix_Chunk* g_sound_explosion = NULL;
static Mix_Chunk* g_sound_explosion_dead = NULL;

//Screen
const int FRAMES_PER_SECOND = 25;
const int SCREEN_WIDTH = 1131;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int SPEED_SCREEN = 50;

const int RENDER_DRAW_COLOR = 0XFF;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

static char g_name_background[] = {"img//newbackground.png"};
static char g_name_over[] = {"img//mission_failed.png"};
static char g_name_map[] = {"map//map01.dat"};

static char g_name_main_right[] = {"img//player_right.png"};
static char g_name_main_left[] = {"img//player_left.png"};
static char g_name_main_jump_left[] = {"img//jump_left.png"};
static char g_name_main_jump_right[] = {"img//jump_right.png"};
static char g_name_dynamic_threat_left[] = {"img//threat_left.png"};
static char g_name_dynamic_threat_right[] = {"img//threat_right.png"};
static char g_name_static_threat[] = {"img//threat_level.png"};
static char g_name_main_bullet[] = {"img//player_bullet.png"};
static char g_name_big_threat_bullet[] = {"img//bullet_threat.png"};
static char g_name_small_threat_bullet[] = {"img//bullet_threat1.png"};
static char g_name_boss_bullet[] = {"img//boss_bullet.png"};
static char g_name_exp[] = {"img//exp3.png"};
static char g_name_boss[] = {"img//boss_object.png"};

static char g_name_background_music[] = {"sound//Action.wav"};
static char g_name_menu_music[] = {"sound//backsound.wav"};
static char g_name_game_over_music[] = {"sound//gameover.wav"};
static char g_name_audio_bullet_main[] = {"sound//Fire.wav"};
static char g_name_audio_bullet_threats[]  = {"sound//Laser.wav"};
static char g_name_audio_exp[] = {"sound//Explosion+1.wav"};
static char g_name_audio_exp_dead[] = {"sound//Bomb1.wav"};
static char kSoundBeep[] = {"sound//beep_.wav"};
static char g_name_sound_increase[] = {"sound//two_beep_.wav"};

#define TILE_SIZE 64
#define BLANK_TILE 0

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 4
#define STATE_MONEY2 14

#define COMEBACK_TIME 10
#define DELAY_TIME_FOR_COLLISION 50

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};


typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};


typedef struct GeometricFormat
{
public:
    GeometricFormat(int left, int top, int width, int height)
    {
        left_ = left;
        top_ = top;
        width_ = width;
        height_ = height;
    }
    int left_;
    int top_;
    int width_;
    int height_;
};

typedef struct ColorData
{
public:
    ColorData(Uint8 r, Uint8 g, Uint8 b)
    {
        red_ = r, green_ = g, blue_ = b;
    }
    Uint8 red_;
    Uint8 green_;
    Uint8 blue_;
};

namespace SDLCommonFunction
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    int MakeRandValue(const int& div_val = 400);
    bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
}

#endif
