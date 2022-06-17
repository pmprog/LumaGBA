
#include "gba.h"

// C64 palette
const u16 c64palette[] = {
    RGB8macro(   0,   0,   0 ), //  0 : Transparent
    RGB8macro(   0,   0,   0 ), //  1 : Black
    RGB8macro( 255, 255, 255 ), //  2 : White
    RGB8macro( 136,   0,   0 ), //  3 : Red
    RGB8macro( 170, 255, 238 ), //  4 : Cyan
    RGB8macro( 204,  68, 204 ), //  5 : Purple
    RGB8macro(   0, 204,  85 ), //  6 : Green
    RGB8macro(   0,   0, 170 ), //  7 : Blue
    RGB8macro( 238, 238, 119 ), //  8 : Yellow
    RGB8macro( 221, 136,  85 ), //  9 : Orange
    RGB8macro( 102,  68,   0 ), // 10 : Brown
    RGB8macro( 255, 119, 119 ), // 11 : Pink
    RGB8macro(  51,  51,  51 ), // 12 : Dark Grey
    RGB8macro( 119, 119, 119 ), // 13 : Mid Grey
    RGB8macro( 170, 255, 102 ), // 14 : Light Green
    RGB8macro(   0, 136, 255 ), // 15 : Light Blue
    RGB8macro( 187, 187, 187 ), // 16 : Light Grey
};

// ARNE16 and ARNE32 palettes ( http://androidarts.com/palette/16pal.htm )
const u16 arnepalette[] = {
    RGB8macro(   0,   0,   0 ), //  0 : Transparent
    RGB8macro(   0,   0,   0 ), //  1 : Black
    RGB8macro( 157, 157, 157 ), //  2 : Grey
    RGB8macro( 255, 255, 255 ), //  3 : White
    RGB8macro( 190,  38,  51 ), //  4 : Red
    RGB8macro( 224, 111, 139 ), //  5 : Meat
    RGB8macro(  73,  60,  43 ), //  6 : Dark Brown
    RGB8macro( 164, 100,  34 ), //  7 : Brown
    RGB8macro( 235, 137,  49 ), //  8 : Orange
    RGB8macro( 247, 226, 107 ), //  9 : Yellow
    RGB8macro(  47,  72,  78 ), // 10 : Dark Green
    RGB8macro(  68, 137,  26 ), // 11 : Green
    RGB8macro( 163, 206,  39 ), // 12 : Slime Green
    RGB8macro(  27,  38,  50 ), // 13 : Night Blue
    RGB8macro(   0,  87, 132 ), // 14 : Sea Blue
    RGB8macro(  49, 162, 242 ), // 15 : Sky Blue
    RGB8macro( 178, 220, 239 ), // 16 : Cloud Blue

    RGB8macro(  52,  42, 151 ), // 17 : 
    RGB8macro( 101, 109, 113 ), // 18 : 
    RGB8macro( 204, 204, 204 ), // 19 : 
    RGB8macro( 115,  41,  48 ), // 20 : 
    RGB8macro( 203,  67, 167 ), // 21 : 
    RGB8macro(  82,  79,  64 ), // 22 : 
    RGB8macro( 173, 157,  51 ), // 23 : 
    RGB8macro( 236,  71,   0 ), // 24 : 
    RGB8macro( 250, 180,  11 ), // 25 : 
    RGB8macro(  17,  94,  51 ), // 26 : 
    RGB8macro(  20, 128, 126 ), // 27 : 
    RGB8macro(  21, 194, 165 ), // 28 : 
    RGB8macro(  34,  90, 246 ), // 29 : 
    RGB8macro( 153, 100, 249 ), // 30 : 
    RGB8macro( 247, 142, 214 ), // 31 : 
    RGB8macro( 244, 185, 144 ), // 32 : 
};

void graphics_mode_bitmap()
{
    REG_DISPCNT = DCNT_MODE4 | DCNT_BG2 | DCNT_OBJ | DCNT_OBJ_1D;
}

void graphics_mode_tilemap(u8 RegularPlanes, ColourDepth BPP)
{
    u16 bitdepth = BG_8BPP;
    switch(BPP)
    {
        case COLOURS_4BPP:
            bitdepth = BG_4BPP;
            break;
        case COLOURS_8BPP:
            bitdepth = BG_8BPP;
            break;
        default:
            bitdepth = BG_8BPP;
            break;
    }
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
    REG_BG0CNT = BG_WRAP | BG_SIZE0 | BG_SBB(20) | BG_PRIO(3) | bitdepth;
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;
    if( RegularPlanes > 1 )
    {
        REG_DISPCNT |= DCNT_BG1;
        REG_BG1CNT = BG_WRAP | BG_SIZE0 | BG_SBB(25) | BG_PRIO(2) | bitdepth;
        REG_BG1HOFS = 0;
        REG_BG1VOFS = 0;
    }
    if( RegularPlanes > 2 )
    {
        REG_DISPCNT |= DCNT_BG2;
        REG_BG2CNT = BG_WRAP | BG_SIZE0 | BG_SBB(30) | BG_PRIO(1) | bitdepth;
        REG_BG2HOFS = 0;
        REG_BG2VOFS = 0;
    }
    if( RegularPlanes > 3 )
    {
        REG_DISPCNT |= DCNT_BG3;
        REG_BG3CNT = BG_WRAP | BG_SIZE0 | BG_SBB(35) | BG_PRIO(0) | bitdepth;
        REG_BG3HOFS = 0;
        REG_BG3VOFS = 0;
    }
}

void graphics_palette_initialise(Palette FromDefault)
{
    u16* bptr = pal_bg_mem;
    u16* cptr = pal_obj_mem;

    switch(FromDefault)
    {
        case PALETTE_C64:
            for( int i = 0; i <= 16; i++ )
            {
                *bptr++ = c64palette[i];
                *cptr++ = c64palette[i];
            }
            break;
        case PALETTE_ARNE16:
            for( int i = 0; i <= 16; i++ )
            {
                *bptr++ = arnepalette[i];
                *cptr++ = arnepalette[i];
            }
            break;
        case PALETTE_ARNE32:
            for( int i = 0; i <= 32; i++ )
            {
                *bptr++ = arnepalette[i];
                *cptr++ = arnepalette[i];
            }
            break;
    }
}

void graphics_palette_set(Colour* PaletteArray, int StartIndex, int ColourCount)
{
    u16* bptr = pal_bg_mem;
    u16* cptr = pal_obj_mem;

    for(int i = 0; i < ColourCount; i++)
    {
        bptr[StartIndex + i] = RGB8macro(PaletteArray[i].R, PaletteArray[i].G, PaletteArray[i].B);
        cptr[StartIndex + i] = bptr[StartIndex + i];
    }
}

void graphics_palette_get(int Index, Colour* Output)
{
    u16* bptr = pal_bg_mem;
    u16 col = bptr[Index];
    Output->R = col & 0x1F;
    Output->G = (col >> 5) & 0x1F;
    Output->B = (col >> 10) & 0x1F;
}

void graphics_palette_rotate(int StartIndex, int ColourCount)
{
    u16* bptr = pal_bg_mem;
    u16* cptr = pal_obj_mem;

    u16 temp = bptr[StartIndex];
    for(int i = 0; i < ColourCount - 1; i++)
    {
        bptr[StartIndex + i] = bptr[StartIndex + i + 1];
        cptr[StartIndex + i] = cptr[StartIndex + i + 1];
    }
    bptr[StartIndex + ColourCount - 1] = temp;
    cptr[StartIndex + ColourCount - 1] = temp;
}

void graphics_flip()
{
    //vid_vsync();
    VBlankIntrWait();
    mmFrame();
}
