
#include "allegro5.h"

ALLEGRO_BITMAP* canvas_planes[4];
u8 character_data[0x20000];
u16 tilemap_data[4][32 * 32];
u8 plane_scrollx[4];
u8 plane_scrolly[4];

void graphics_tilemap_characterset_set(u8* CharacterSetSource, u16 FirstCharacter, u16 NumberOfCharacters, ColourDepth BPP)
{
	size_t bytestocopy = NumberOfCharacters;
    switch(BPP)
    {
        case COLOURS_4BPP:
            memcpy(&character_data[FirstCharacter * 20], CharacterSetSource, bytestocopy * 20);
            break;
        case COLOURS_8BPP:
            memcpy(&character_data[FirstCharacter * 64], CharacterSetSource, bytestocopy * 64);
            break;
    }
}

void graphics_tilemap_tilemap_settile(u8 Plane, u16 X, u16 Y, u16 Tile)
{
	if (X < 0 || Y < 0 || X > 31 || Y > 31)
	{
		return;
	}
	tilemap_data[Plane][(Y * 32) + X] = Tile;
	ALLEGRO_LOCKED_REGION* rgn = al_lock_bitmap_region(canvas_planes[Plane], X * 8, Y * 8, 8, 8, ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, ALLEGRO_LOCK_WRITEONLY);

	u16 actualtile = (Tile & 0x03FF);
	u16 flipy = (Tile & 0x0800);
	u16 flipx = (Tile & 0x0400);
	u8* p = (u8*)rgn->data;

	for(int y = 0; y < 8; y++)
	{
		int ty = (flipy == 0 ? y : 7 - y);	// Mirror Y
		for(int x = 0; x < 8; x++)
		{
			int tx = (flipx == 0 ? x : 7 - x);	// Mirror X
			u8 palidx = 0;
			switch(canvas_bpp)
			{
				case COLOURS_4BPP:
					palidx = character_data[(actualtile * 20) + (ty * 4) + (tx >> 1)];
					palidx = ( tx % 2 == 0 ? palidx & 0x0F : palidx >> 4 );
					break;
				case COLOURS_8BPP:
					palidx = character_data[(actualtile * 64) + (ty * 8) + tx];
					break;
			}
			int b = (rgn->pitch * y) + (rgn->pixel_size * x);
			p[b + 0] = canvas_palette[palidx].R;
			p[b + 1] = canvas_palette[palidx].G;
			p[b + 2] = canvas_palette[palidx].B;
			p[b + 3] = (palidx == 0 ? 0 : 255);
		}
	}
	al_unlock_bitmap(canvas_planes[Plane]);
}

u16 graphics_tilemap_tilemap_gettile(u8 Plane, u16 X, u16 Y)
{
	if (X < 0 || Y < 0 || X > 31 || Y > 31) { return 0; }
	return tilemap_data[Plane][(Y * 32) + X];
}

void graphics_tilemap_tilemap_setposition(u8 Plane, u16 X, u16 Y)
{
	plane_scrollx[Plane] = X & 0x00FF;
	plane_scrolly[Plane] = Y & 0x00FF;
}
