
#include "stage_complete.h"
#include "../resources/completion.h"
#include "game.h"

extern u8 spdelay;
extern u16 spposx;
extern u16 stposh;

const char* const finalscrolltext[] =
{
    "            ",
    "------------",
	"            ",
	"* CONGRATS *",
	"            ",
	"------------",
	"            ",
	"YOU HAVE    ",
	"MANAGED TO  ",
	"SOLVE ALL   ",
	"THE PUZZLES ",
	"FOUND IN    ",
	"LUMA...     ",
	"            ",
	"WE KNEW YOU ",
	"COULD DO IT!",
	"            ",
	"------------",
	"            ",
	"CREDITS:    ",
	"            ",
	"CONCEPT:    ",
	" SHALLAN    ",
	"            ",
	"GBA CODE:   ",
	" PMPROG     ",
	"            ",
	"GRAPHICS:   ",
	" HELP-      ",
	"   COMPUTER ",
	" SHALLAN    ",
	" PMPROG     ",
	"            ",
	"MUSIC:      ",
	" RICHMOND-  ",
	"       MIKE ",
	" MA2E/DSR   ",
	"            ",
	"LEVELS:     ",
	" AIRJURI    ",
	" AKMAFIN    ",
	" AMOK       ",
	" CHISWICKED ",
	" ELDRITCH   ",
	" FURROY     ",
	" MRG8472    ",
	" OLDSKOOL-  ",
	"      CODER ",
	" PHAZE101   ",
	" RICHMOND-  ",
	"       MIKE ",
	" SHALLAN    ",
	" SPIRITHUND ",
	" STEPZ      ",
	" VOID       ",
	" WAULOK     ",
	" WIZARDNJ   ",
	" ZOOPERDAN  ",
	"            ",
	"------------",
	"            ",
	"THANK YOU TO",
	"SHALLAN FOR ",
	"ALLOWING ME ",
	"TO PORT THE ",
	"GAME, AND TO",
	"THOSE LISTED",
	"ABOVE FOR   ",
	"MAKING THE  ",
	"GAME WHAT IT",
	"IS...       ",
	"            ",
	"THANKS TO   ",
	"ZOOPERDAN   ",
	"AND MA2E/DSR",
	"FOR LETTING ",
	"ME USE THE  ",
	"AMIGA PORT'S",
	"MUSIC.      ",
	"            ",
	"I HOPE YOU  ",
	"HAVE ENJOYED",
	"PLAYING THE ",
	"GAME! *     ",
	"            ",
	"SEE YOU FOR ",
	"THE NEXT    ",
	"GAME...     ",
	"            ",
	"  -- PMPROG ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
	"            ",
};

void gamecomplete_start()
{
	spdelay = 0;
	spposx = 0;
	stposh = 0;

    graphics_tilemap_tilemap_setposition(0, 0, 0);  // Background
    graphics_tilemap_tilemap_setposition(1, 0, 0);  // Scroll Text
    graphics_tilemap_tilemap_setposition(2, 4, 4);  // Lasers

	for(int y = 0; y < 20; y++)
	{
		for(int x = 0; x < 30; x++)
		{
			graphics_tilemap_tilemap_settile(0, x, y, completion_tmx_completebkg_data[(y * 30) + x]);
			graphics_tilemap_tilemap_settile(1, x, y, completion_tmx_completemid_data[(y * 30) + x]);
			graphics_tilemap_tilemap_settile(2, x, y, completion_tmx_completeupr_data[(y * 30) + x]);
		}
	}

	audio_music_play(1);
}

void gamecomplete_finish()
{
    
}

void gamecomplete_update()
{
	u8 x;
	u8 y;
	spdelay = (spdelay + 1) % 3;
	if( spdelay == 0 )
	{
		stposh = (stposh + 1) % 8;
		graphics_tilemap_tilemap_setposition(1, 0, stposh);  // Scroll Text

		if( stposh == 0 )
		{
			for(y = 2; y < 17; y++)
			{
				for(x = 9; x < 21; x++)
				{
					u16 tileidx = graphics_tilemap_tilemap_gettile(1, x, y + 1);
					graphics_tilemap_tilemap_settile(1, x, y, tileidx);
				}
			}

			game_print(1, 9, 17, finalscrolltext[spposx], 12);
			spposx = (spposx + 1) % 105;
		}
	}
}
