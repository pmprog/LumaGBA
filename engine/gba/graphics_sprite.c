
#include "gba.h"

void graphics_sprites_clear()
{
    for(u8 i = 0; i < 128; i++)
    {
        OAM[i].attr0 |= ATTR0_HIDE;
    }
}

void graphics_sprites_characterset_set(u8* CharacterSetSource, u16 FirstCharacter, u16 NumberOfCharacters, ColourDepth BPP)
{
    switch(BPP)
    {
        case COLOURS_4BPP:
            memcpy32((u16*)(MEM_OVRAM + (FirstCharacter * 20)), (u16*)CharacterSetSource, (NumberOfCharacters * 5));
            break;
        case COLOURS_8BPP:
            memcpy32((u16*)(MEM_OVRAM + (FirstCharacter * 64)), (u16*)CharacterSetSource, (NumberOfCharacters * 16));
            break;
        default:
            break;
    }
}

void graphics_sprites_configure(u8 Index, u16 Tile, ColourDepth BPP, u8 PaletteIndex, SpriteSize Size)
{
    u16 bppmap = ATTR0_8BPP;
    switch(BPP)
    {
        case COLOURS_4BPP:
            bppmap = ATTR0_4BPP;
            break;
        case COLOURS_8BPP:
            bppmap = ATTR0_8BPP;
            break;
        default:
            bppmap = ATTR0_8BPP;
            break;
    }
    switch(Size)
    {
        case SIZE_8x8:
            OAM[Index].attr0 = (OAM[Index].attr0 & 0x00FF) | bppmap | ATTR0_SQUARE;
            OAM[Index].attr1 = (OAM[Index].attr1 & 0x3FFF) | ATTR1_SIZE_8;
            break;
        case SIZE_16x16:
            OAM[Index].attr0 = (OAM[Index].attr0 & 0x00FF) | bppmap | ATTR0_SQUARE;
            OAM[Index].attr1 = (OAM[Index].attr1 & 0x3FFF) | ATTR1_SIZE_16;
            break;
        case SIZE_32x32:
            OAM[Index].attr0 = (OAM[Index].attr0 & 0x00FF) | bppmap | ATTR0_SQUARE;
            OAM[Index].attr1 = (OAM[Index].attr1 & 0x3FFF) | ATTR1_SIZE_32;
            break;
        case SIZE_64x64:
            OAM[Index].attr0 = (OAM[Index].attr0 & 0x00FF) | bppmap | ATTR0_SQUARE;
            OAM[Index].attr1 = (OAM[Index].attr1 & 0x3FFF) | ATTR1_SIZE_64;
            break;
    }
    OAM[Index].attr2 = (OAM[Index].attr2 & 0x0C00) | ATTR2_ID(Tile) | ATTR2_PALBANK(PaletteIndex);
}

void graphics_sprites_position(u8 Index, u8 Plane, u8 Visible, s16 X, s16 Y, Mirroring Flip)
{
    OAM[Index].attr0 = (OAM[Index].attr0 & 0xFF00) | ATTR0_Y( Y ) | (Visible == 0 ? ATTR0_HIDE : 0);
    OAM[Index].attr1 = (OAM[Index].attr1 & 0xC000) | ATTR1_X( X ) | ((u16)Flip << 12);
    OAM[Index].attr2 = (OAM[Index].attr2 & 0xF3FF) | ATTR2_PRIO(3 - Plane);
}

void graphics_sprites_animate(u8 Index, u16 Tile, u8 PaletteIndex)
{
    OAM[Index].attr2 = (OAM[Index].attr2 & 0x0C00) | ATTR2_ID(Tile) | ATTR2_PALBANK(PaletteIndex);
}

void graphics_sprites_position_get(u8 Index, u8* Plane, s16* X, s16* Y)
{
    *Plane = (OAM[Index].attr2 & ATTR2_PRIO_MASK) >> ATTR2_PRIO_SHIFT;
    *X = (OAM[Index].attr1 & ATTR1_X_MASK);
    *Y = (OAM[Index].attr0 & ATTR0_Y_MASK);
}
