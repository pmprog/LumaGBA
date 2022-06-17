
#include "allegro5.h"

Colour canvas_palette[256];
bool canvas_bitmapmode;
ColourDepth canvas_bpp;

// C64 palette
const Colour c64palette[] = {
    {0,   0,   0}, //  0 : Transparent
    {0,   0,   0}, //  1 : Black
    {255, 255, 255}, //  2 : White
    {136,   0,   0}, //  3 : Red
    {170, 255, 238}, //  4 : Cyan
    {204,  68, 204}, //  5 : Purple
    {0, 204,  85}, //  6 : Green
    {0,   0, 170}, //  7 : Blue
    {238, 238, 119}, //  8 : Yellow
    {221, 136,  85}, //  9 : Orange
    {102,  68,   0}, // 10 : Brown
    {255, 119, 119}, // 11 : Pink
    {51,  51,  51}, // 12 : Dark Grey
    {119, 119, 119}, // 13 : Mid Grey
    {170, 255, 102}, // 14 : Light Green
    {0, 136, 255}, // 15 : Light Blue
    {187, 187, 187}, // 16 : Light Grey
};

// ARNE16 and ARNE32 palettes ( http://androidarts.com/palette/16pal.htm )
const Colour arnepalette[] = {
    {0,   0,   0}, //  0 : Transparent
    {0,   0,   0}, //  1 : Black
    {157, 157, 157}, //  2 : Grey
    {255, 255, 255}, //  3 : White
    {190,  38,  51}, //  4 : Red
    {224, 111, 139}, //  5 : Meat
    {73,  60,  43}, //  6 : Dark Brown
    {164, 100,  34}, //  7 : Brown
    {235, 137,  49}, //  8 : Orange
    {247, 226, 107}, //  9 : Yellow
    {47,  72,  78}, // 10 : Dark Green
    {68, 137,  26}, // 11 : Green
    {163, 206,  39}, // 12 : Slime Green
    {27,  38,  50}, // 13 : Night Blue
    {0,  87, 132}, // 14 : Sea Blue
    {49, 162, 242}, // 15 : Sky Blue
    {178, 220, 239}, // 16 : Cloud Blue

    {52,  42, 151}, // 17 : 
    {101, 109, 113}, // 18 : 
    {204, 204, 204}, // 19 : 
    {115,  41,  48}, // 20 : 
    {203,  67, 167}, // 21 : 
    {82,  79,  64}, // 22 : 
    {173, 157,  51}, // 23 : 
    {236,  71,   0}, // 24 : 
    {250, 180,  11}, // 25 : 
    {17,  94,  51}, // 26 : 
    {20, 128, 126}, // 27 : 
    {21, 194, 165}, // 28 : 
    {34,  90, 246}, // 29 : 
    {153, 100, 249}, // 30 : 
    {247, 142, 214}, // 31 : 
    {244, 185, 144}, // 32 : 
};

void graphics_mode_bitmap()
{
    //REG_DISPCNT = MODE_4 | BG2_ON | OBJ_ON | OBJ_1D_MAP;
    canvas_bitmapmode = true;
}

void graphics_mode_tilemap(u8 RegularPlanes, ColourDepth BPP)
{
    canvas_bitmapmode = false;
    canvas_bpp = BPP;
    if( canvas_planes[0] == NULL ) { canvas_planes[0] = al_create_bitmap(256, 256); }
    al_set_target_bitmap(canvas_planes[0]);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    if (RegularPlanes > 1)
    {
        if( canvas_planes[1] == NULL ) { canvas_planes[1] = al_create_bitmap(256, 256); }
        al_set_target_bitmap(canvas_planes[1]);
        al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    }
    else
    {
        if( canvas_planes[1] != NULL ) { al_destroy_bitmap(canvas_planes[1]); canvas_planes[1] = NULL; }
    }
    if (RegularPlanes > 2)
    {
        if( canvas_planes[2] == NULL ) { canvas_planes[2] = al_create_bitmap(256, 256); }
        al_set_target_bitmap(canvas_planes[2]);
        al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    }
    else
    {
        if( canvas_planes[2] != NULL ) { al_destroy_bitmap(canvas_planes[2]); canvas_planes[2] = NULL; }
    }
}

void graphics_palette_initialise(Palette FromDefault)
{
    switch (FromDefault)
    {
    case PALETTE_C64:
        for (int i = 0; i < 16; i++)
        {
          canvas_palette[i] = c64palette[i];
        }
        break;
    case PALETTE_ARNE16:
        for (int i = 0; i < 16; i++)
        {
          canvas_palette[i] = arnepalette[i];
        }
        break;
    case PALETTE_ARNE32:
        for (int i = 0; i < 32; i++)
        {
          canvas_palette[i] = arnepalette[i];
        }
        break;
    }
}

void graphics_palette_set(Colour* PaletteArray, int StartIndex, int ColourCount)
{
    for (int i = 0; i < ColourCount; i++)
    {
        canvas_palette[StartIndex + i] = PaletteArray[i];
    }
}

void graphics_palette_get(int Index, Colour* Output)
{
    Output->R = canvas_palette[Index].R;
    Output->G = canvas_palette[Index].G;
    Output->B = canvas_palette[Index].B;
}

void graphics_palette_rotate(int StartIndex, int ColourCount)
{
    Colour temp = canvas_palette[StartIndex];
    for(int i = 0; i < ColourCount - 1; i++)
    {
        canvas_palette[StartIndex + i] = canvas_palette[StartIndex + i + 1];
    }
    canvas_palette[StartIndex + ColourCount - 1] = temp;
}

void graphics_flip()
{

    if( canvas_bitmapmode )
    {
        al_unlock_bitmap( canvas_internal );
    }
    else
    {
        al_set_target_bitmap(canvas_internal);
        for(int i = 0; i < 4; i++)
        {
            if(canvas_planes[i] != NULL)
            {
                al_draw_bitmap(canvas_planes[i], 0 - plane_scrollx[i], 0 - plane_scrolly[i], 0);
                al_draw_bitmap(canvas_planes[i], 0 - plane_scrollx[i] + 256, 0 - plane_scrolly[i], 0);
                al_draw_bitmap(canvas_planes[i], 0 - plane_scrollx[i], 0 - plane_scrolly[i] + 256, 0);
                al_draw_bitmap(canvas_planes[i], 0 - plane_scrollx[i] + 256, 0 - plane_scrolly[i] + 256, 0);            
            }
            
            // TODO: Draw sprites on plane
            for(int s = 128; s >= 0; s--)
            {
                if( sprites[s].graphic_visible != 0 && sprites[s].cached_image != NULL && sprites[s].position_plane == i )
                {
                    al_draw_bitmap(sprites[s].cached_image, sprites[s].position_x, sprites[s].position_y, 0);
                }
            }
        }
    }

    al_set_target_backbuffer(screen);
    
    // Draw canvas scaled, and in the middle
    al_draw_scaled_bitmap(canvas_internal, 0, 0, 240, 160, 0, 0, 240 * screen_bestscale, 160 * screen_bestscale, 0);

    al_flip_display();

    if( canvas_bitmapmode )
    {
        bufferlock = al_lock_bitmap( canvas_internal, ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, ALLEGRO_LOCK_READWRITE );
    }
    else
    {
        al_set_target_bitmap(canvas_internal);
        al_clear_to_color(al_map_rgb(canvas_palette[0].R, canvas_palette[0].G, canvas_palette[0].B));
    }
}
