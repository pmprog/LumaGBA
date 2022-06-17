
#include "allegro5.h"

SpriteData sprites[128];
u8 sprite_character_data[0x20000];

void graphics_sprites_clear()
{
    for(u8 i = 0; i < 128; i++)
    {
        sprites[i].graphic_visible = 0;
    }
}

void graphics_sprites_characterset_set(u8* CharacterSetSource, u16 FirstCharacter, u16 NumberOfCharacters, ColourDepth BPP)
{
    size_t bytestocopy = NumberOfCharacters;
    switch(BPP)
    {
        case COLOURS_4BPP:
            memcpy(&sprite_character_data[(FirstCharacter * 20)], CharacterSetSource, (bytestocopy * 20));
            break;
        case COLOURS_8BPP:
            memcpy(&sprite_character_data[(FirstCharacter * 64)], CharacterSetSource, (bytestocopy * 64));
            break;
    }
}

void graphics_sprites_configure(u8 Index, u16 Tile, ColourDepth BPP, u8 PaletteIndex, SpriteSize Size)
{
    sprites[Index].graphic_size = Size;
    sprites[Index].graphic_bpp = BPP;
    if(sprites[Index].cached_image != NULL)
    {
        al_destroy_bitmap(sprites[Index].cached_image);
    }
    switch(sprites[Index].graphic_size)
    {
        case SIZE_8x8:
            sprites[Index].cached_image = al_create_bitmap(8, 8);
            break;
        case SIZE_16x16:
            sprites[Index].cached_image = al_create_bitmap(16, 16);
            break;
        case SIZE_32x32:
            sprites[Index].cached_image = al_create_bitmap(32, 32);
            break;
        case SIZE_64x64:
            sprites[Index].cached_image = al_create_bitmap(64, 64);
            break;
    }
    graphics_sprites_animate(Index, Tile, PaletteIndex);
}

void graphics_sprites_position(u8 Index, u8 Plane, u8 Visible, s16 X, s16 Y, Mirroring Flip)
{
    sprites[Index].position_x = X;
    sprites[Index].position_y = Y;
    sprites[Index].position_plane = Plane;
    sprites[Index].graphic_visible = Visible;
    sprites[Index].graphic_flip = Flip;
}

void graphics_sprites_animate(u8 Index, u16 Tile, u8 PaletteIndex)
{
    sprites[Index].graphic_palette = PaletteIndex;
    sprites[Index].graphic_tile = Tile;
    u8 tilewidth = 0;
    u8 tilehigh = 0;
    switch(sprites[Index].graphic_size)
    {
        case SIZE_8x8:
            tilewidth = 1;
            tilehigh = 1;
            break;
        case SIZE_16x16:
            tilewidth = 2;
            tilehigh = 2;
            break;
        case SIZE_32x32:
            tilewidth = 4;
            tilehigh = 4;
            break;
        case SIZE_64x64:
            tilewidth = 8;
            tilehigh = 8;
            break;
    }
    // TODO: Render Cached Image

    ALLEGRO_LOCKED_REGION* rgn = al_lock_bitmap(sprites[Index].cached_image, ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, ALLEGRO_LOCK_WRITEONLY);
    u16 curtile = sprites[Index].graphic_tile >> 1;
    u8* p = (u8*)rgn->data;

    for(int ty = 0; ty < tilehigh; ty++)
    {
        for(int tx = 0; tx < tilewidth; tx++)
        {
            for(int y = 0; y < 8; y++)
            {
                for(int x = 0; x < 8; x++)
                {
                    u8 palidx = 0;
                    switch (sprites[Index].graphic_bpp)
                    {
                        case COLOURS_4BPP:
                            palidx = sprite_character_data[(curtile * 20) + (y * 4) + (x >> 1)];
                            palidx = (tx % 2 == 0 ? palidx & 0x0F : palidx >> 4);
                            break;
                        case COLOURS_8BPP:
                            palidx = sprite_character_data[(curtile * 64) + (y * 8) + x];
                            break;
                    }
                    int b = (rgn->pitch * ((ty * 8) + y)) + (rgn->pixel_size * ((tx * 8) + x));
                    p[b + 0] = canvas_palette[palidx].R;
                    p[b + 1] = canvas_palette[palidx].G;
                    p[b + 2] = canvas_palette[palidx].B;
                    p[b + 3] = (palidx == 0 ? 0 : 255);
                }
            }
            curtile++;
        }
    }

    al_unlock_bitmap(sprites[Index].cached_image);

}

void graphics_sprites_position_get(u8 Index, u8* Plane, s16* X, s16* Y)
{
    *Plane = sprites[Index].position_plane;
    *X = sprites[Index].position_x;
    *Y = sprites[Index].position_y;
}
