
#pragma once

#ifdef LIBGBA
#include "gba/gba.h"
#endif

#ifdef LIBALLEGRO5
#include "a5/allegro5.h"
#endif

void platform_init();
void platform_update();
void platform_shutdown();
u8 platform_updateframes();
void platform_logtext(const char* message);

void audio_music_play(u16 track_index);
void audio_music_stop();
void audio_music_seek(u32 position);
void audio_update();

void input_update();
u16 input_button_pressed(ControllerInput Button);
u16 input_button_held(ControllerInput Button);
u16 input_button_released(ControllerInput Button);

void graphics_mode_bitmap();
void graphics_mode_tilemap(u8 RegularPlanes, ColourDepth BPP);
void graphics_flip();

void graphics_palette_initialise(Palette FromDefault);
void graphics_palette_set(Colour* PaletteArray, int StartIndex, int ColourCount);
void graphics_palette_get(int Index, Colour* Output);
void graphics_palette_rotate(int StartIndex, int ColourCount);

void graphics_bitmap_setpixel(s16 X, s16 Y, u8 PaletteIndex );
void graphics_bitmap_line_horizontal(s16 X1, s16 Y, s16 X2, u8 PaletteIndex );
void graphics_bitmap_line(s16 X1, s16 Y1, s16 X2, s16 Y2, u8 PaletteIndex );
void graphics_bitmap_rectangle(s16 X, s16 Y, s16 Width, s16 Height, u8 PaletteIndex );
void graphics_bitmap_triangle(s16 X1, s16 Y1, s16 X2, s16 Y2, s16 X3, s16 Y3, u8 PaletteIndex );
void graphics_bitmap_circle(s16 X, s16 Y, u8 Radius, u8 PaletteIndex );

void graphics_bitmap_blit256(u8* ImageData, u16 ImageWidth, u16 ImageHeight, u16 DestinationX, u16 DestinationY);
void graphics_bitmap_blit256sub(u8* ImageData, u16 ImageWidth, u16 ImageHeight, u16 DestinationX, u16 DestinationY, u16 SourceX, u16 SourceY, u16 SourceWidth, u16 SourceHeight);

void graphics_tilemap_characterset_set(u8* CharacterSetSource, u16 FirstCharacter, u16 NumberOfCharacters, ColourDepth BPP);
void graphics_tilemap_tilemap_settile(u8 Plane, u16 X, u16 Y, u16 Tile);
u16 graphics_tilemap_tilemap_gettile(u8 Plane, u16 X, u16 Y);
void graphics_tilemap_tilemap_setposition(u8 Plane, u16 X, u16 Y);

void graphics_sprites_clear();
void graphics_sprites_characterset_set(u8* CharacterSetSource, u16 FirstCharacter, u16 NumberOfCharacters, ColourDepth BPP);
void graphics_sprites_configure(u8 Index, u16 Tile, ColourDepth BPP, u8 PaletteIndex, SpriteSize Size);
void graphics_sprites_position(u8 Index, u8 Plane, u8 Visible, s16 X, s16 Y, Mirroring Flip);
void graphics_sprites_animate(u8 Index, u16 Tile, u8 PaletteIndex);
void graphics_sprites_position_get(u8 Index, u8* Plane, s16* X, s16* Y);

void network_init(NetworkConnectionCallback ConnectionCallback, NetworkDataCallback DataCallback);
void network_server_start();
void network_server_stop();
void network_client_start();
void network_client_stop();
void network_sendword(u16 Data);

void savegame_read(void* Buffer, u16 BufferLength);
void savegame_write(void* Buffer, u16 BufferLength);
