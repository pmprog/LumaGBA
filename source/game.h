
#pragma once

#include "../engine/engine.h"

#define EMPTY_TILE      0
#define WALL_TILE       1
#define ITEM_CROSSPIPE  2
#define ITEM_SIDEPIPE   3
#define ITEM_DOWNPIPE   4
#define ITEM_LASER_R_U  15
#define ITEM_LASER_R_D  16
#define ITEM_LASER_R_L  13
#define ITEM_LASER_R_R  14
#define ITEM_LASER_G_U  7
#define ITEM_LASER_G_D  8
#define ITEM_LASER_G_L  5
#define ITEM_LASER_G_R  6
#define ITEM_LASER_B_U  11
#define ITEM_LASER_B_D  12
#define ITEM_LASER_B_L  9
#define ITEM_LASER_B_R  10
#define ITEM_BATTERY    17
#define ITEM_MIRROR_UR  18
#define ITEM_MIRROR_UL  19
#define ITEM_TARGET_R   20
#define ITEM_TARGET_R_HIT   ITEM_TARGET_R + 128
#define ITEM_TARGET_G   21
#define ITEM_TARGET_G_HIT   ITEM_TARGET_G + 128
#define ITEM_TARGET_B   22
#define ITEM_TARGET_B_HIT   ITEM_TARGET_B + 128
#define INVALID_MAP     127

#define LASER_COLOUR_G          0
#define LASER_COLOUR_B          1
#define LASER_COLOUR_R          2
#define LASER_DIRECTION_LEFT    0
#define LASER_DIRECTION_RIGHT   1
#define LASER_DIRECTION_UP      2
#define LASER_DIRECTION_DOWN    3

typedef struct GameSettings
{
    u32 game_save_marker;
    u16 game_tutorials_enabled;
    u16 game_current_level;
    u16 game_maximum_level;
    u16 game_practice_mode;

    u8  game_current_level_moves_remaining;
    u8  game_current_level_map_layout[80];
} GameSettings;

extern GameSettings game_settings;

void LoadSRAMData();
void SaveSRAMData();

const u8* GetLevelData();

void game_dialoguebox(u8 Plane, u8 X, u8 Y, u8 Width, u8 Height);
u8 game_dialoguebox_sprited(u8 Plane, u8 X, u8 Y, const char* text, u16 text_len, u8 SpriteStartIndex);
void game_print(u8 Plane, u8 X, u8 Y, const char* text, u16 text_len);
void game_printlargenumber(u8 Plane, u8 X, u8 Y, u16 Number, u8 DrawWidth);
u16 game_itemtype_to_graphic(u8 ItemType);
u8 game_itemtype_pickable(u8 ItemType);
