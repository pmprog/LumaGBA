
#pragma once

#include <stdint.h>
#include "../typedefs.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "../platform.h"

#ifndef Colour
struct Colour;
#endif

typedef struct SpriteData
{
    ALLEGRO_BITMAP* cached_image;
    s16             position_x;
    s16             position_y;
    u8              position_plane;
    SpriteSize      graphic_size;
    ColourDepth     graphic_bpp;
    u16             graphic_tile;
    u8              graphic_palette;
    u8              graphic_visible;
    Mirroring       graphic_flip;
} SpriteData;

extern ALLEGRO_EVENT_QUEUE* eventqueue;
extern ALLEGRO_DISPLAY* screen;
extern int screen_bestscale;
extern ALLEGRO_BITMAP* canvas_internal;
extern ALLEGRO_BITMAP* canvas_planes[4];
extern bool canvas_bitmapmode;
extern ColourDepth canvas_bpp;
extern u8 plane_scrollx[4];
extern u8 plane_scrolly[4];
extern Colour canvas_palette[256];
extern u8 character_data[0x20000];
extern u8 sprite_character_data[0x20000];
extern SpriteData sprites[128];
extern ALLEGRO_LOCKED_REGION* bufferlock;
extern char* game_name;
extern int video_width;
extern int video_height;
extern u8 update_required;

extern ALLEGRO_VOICE* audiovoice;
extern ALLEGRO_MIXER* audiomixer;
extern ALLEGRO_AUDIO_STREAM* audiostream;
