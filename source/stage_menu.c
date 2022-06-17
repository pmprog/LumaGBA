
#include "stage_menu.h"
#include "../resources/titlescreen.h"
#include "game.h"
#include "stage_level.h"
#include "stage_codeentry.h"
#include <string.h>

u8 spdelay = 0;
u16 spposx = 0;
u16 stposh = 0;
size_t top_scrolltext_len;
const char* top_scrolltext =
							"WELCOME TO LUMA           "
                            "GBA PORT BY               "
							"GRAPHICS BY               "
                            "MUSIC BY MA2E/DSR         "
							"PUBLISHED BY          "
                            "\x1C\x1D BATTERY, MOVABLE           "
                            "\x14\x15 \x18\x19 MIRRORS, MOVABLE        "
                            "\xBC\xBD LASER, MOVABLE             "
                            "\xB0\xB1 TARGET, STATIC             "
                            "\x04\x05 \x08\x09 \x0C\x0D \x10\x11 WALLS, STATIC             "
                            "          ";
const char* mid_scrolltext =
							"ORIGINAL DESIGN/GAME BY   "
                            "MARK 'PMPROG' WATKIN      "
                            "HELPCOMPUTER, SHALLAN,    "
                            "ORIGINAL BY               "
                            "PHOENIX WARE          "
                            "\x1E\x1F PROVIDES POWER TO          "
                            "\x16\x17 \x1A\x1B REFLECTS LASERS BY      "
                            "\xBE\xBF MATCH THE COLOURS TO       "
                            "\xB2\xB3 HIT WITH THE CORRECT       "
                            "\x06\x07 \x0A\x0B \x0E\x0F \x12\x13 BLOCKS LASERS ENTIRELY OR"
                            "          ";
const char* bot_scrolltext =
                            "SIMON 'SHALLAN' JAMESON   "
                            "POLYMATH PROGRAMMING      "
                            "AND PMPROG                "
                            "MIKE RICHMOND             "
                            "                      "
                            "   LASERS                     "
                            "      90 DEGREES              "
                            "   THE RESPECTIVE TARGETS     "
                            "   LASER TO ACTIVATE          "
                            "            LIMITS DIRECTION OF BEAM       "
                            "          ";

u8 menu_selected = 0;
u8 menu_helpscrollpos = 0;
/*
const char* bottom_scrolltext[] = {
	"   SEE HELP PROMPTS IN THE FIRST FEW LEVELS                                                               ",
	"   NORMAL - LIMITED SHIFTS, NO LEVEL SKIP, SAVING      PRACTICE - NO SHIFT LIMIT, LEVEL SKIP, NO SAVING   ",
	"   PLAY THE GAME!                                                                                         ",
	"   SELECT YOUR STARTING LEVEL BY ENTERING A LEVEL CODE                                                    ",
};
*/

void mainmenu_scrolltext();
void mainmenu_print(u8 X, u8 Y, const char* text, u16 text_len);
void mainmenu_printoptions();
void mainmenu_printcursor();

void mainmenu_start()
{
	spdelay = 0;
	spposx = 0;
	stposh = 0;
	top_scrolltext_len = strlen(top_scrolltext);

	for(int y = 0; y < 20; y++)
	{
		for(int x = 0; x < 30; x++)
		{
			graphics_tilemap_tilemap_settile(0, x, y, titlescreen2_tmx_bottom_layer_data[(y * 30) + x]);
			graphics_tilemap_tilemap_settile(1, x, y, titlescreen2_tmx_mid_layer_data[(y * 30) + x]);
			graphics_tilemap_tilemap_settile(2, x, y, titlescreen2_tmx_top_layer_data[(y * 30) + x]);
		}
	}

    LoadSRAMData();
	mainmenu_printoptions();
	mainmenu_printcursor();
	graphics_tilemap_tilemap_setposition(0, 0, 0);
	graphics_tilemap_tilemap_setposition(1, 0, 0);
	graphics_tilemap_tilemap_setposition(2, 0, 0);

    audio_music_play(1);
}

void mainmenu_finish()
{
	graphics_tilemap_tilemap_setposition(1, 0, 0);
}

void mainmenu_update()
{
	spdelay = (spdelay + 1) % 2;
	if( spdelay == 0 ) { mainmenu_scrolltext(); }

	if( input_button_pressed(DPAD_Down) ) { menu_selected = (menu_selected + 1) % 5; menu_helpscrollpos = 0; mainmenu_printcursor(); }
	if( input_button_pressed(DPAD_Up) ) { menu_selected = (menu_selected + 4) % 5; menu_helpscrollpos = 0; mainmenu_printcursor(); }

	if (input_button_pressed(BUTTON_QUIT))
	{
		engine_changestage(NULL);
		return;
	}

	switch( menu_selected )
	{
		case 2:
			if( input_button_pressed(DPAD_Left) || input_button_pressed(BUTTON_A) || input_button_pressed(DPAD_Right) || input_button_pressed(BUTTON_B)  || input_button_pressed(BUTTON_Start) )
			{
				game_settings.game_tutorials_enabled = 1 - game_settings.game_tutorials_enabled;
				mainmenu_printoptions();
			}
			break;
		case 4:
			if( input_button_pressed(BUTTON_A) || input_button_pressed(BUTTON_B) || input_button_pressed(BUTTON_Start) )
			{
				engine_changestage((StageRecord*)&codeentry_stage);
				return;
			}
			break;
		case 1:
			if( input_button_pressed(DPAD_Left) || input_button_pressed(BUTTON_A) || input_button_pressed(DPAD_Right) || input_button_pressed(BUTTON_B)  || input_button_pressed(BUTTON_Start) )
			{
				game_settings.game_practice_mode = 1 - game_settings.game_practice_mode;
				mainmenu_printoptions();
			}
			break;
		case 0:
			if( input_button_pressed(BUTTON_A) || input_button_pressed(BUTTON_B) || input_button_pressed(BUTTON_Start) )
			{
                audio_music_stop();
                SaveSRAMData();
				engine_changestage((StageRecord*)&level_stage);
				return;
			}
			break;
        case 3:
			if( input_button_pressed(DPAD_Left) || input_button_pressed(BUTTON_A) )
			{
				if( game_settings.game_current_level > 0 ) { game_settings.game_current_level--; }
				mainmenu_printoptions();
			}
			if( input_button_pressed(DPAD_Right) || input_button_pressed(BUTTON_B) )
			{
				if( game_settings.game_current_level < game_settings.game_maximum_level ) { game_settings.game_current_level++; }
				mainmenu_printoptions();
			}
            break;
	}

}

void mainmenu_scrolltext()
{
	spposx++;
	if(spposx == 8)
	{
		for(int x = 1; x < 30; x++)
		{
			graphics_tilemap_tilemap_settile(0, x - 1, 6, graphics_tilemap_tilemap_gettile(0, x, 6));
            graphics_tilemap_tilemap_settile(0, x - 1, 7, graphics_tilemap_tilemap_gettile(0, x, 7));
            graphics_tilemap_tilemap_settile(0, x - 1, 8, graphics_tilemap_tilemap_gettile(0, x, 8));
		}
		graphics_tilemap_tilemap_settile(0, 29, 6, (u16)top_scrolltext[stposh]);
        graphics_tilemap_tilemap_settile(0, 29, 7, (u16)mid_scrolltext[stposh]);
        graphics_tilemap_tilemap_settile(0, 29, 8, (u16)bot_scrolltext[stposh]);
		stposh = (stposh + 1) % top_scrolltext_len;

/*
		for(int x = 3; x < 28; x++)
		{
			graphics_tilemap_tilemap_settile(1, x - 1, 18, graphics_tilemap_tilemap_gettile(1, x, 18));
		}
		graphics_tilemap_tilemap_settile(1, 27, 18, (u16)bottom_scrolltext[menu_selected][menu_helpscrollpos]);
		menu_helpscrollpos = (menu_helpscrollpos + 1) % 106;
*/
		spposx = 0;
	}
	graphics_tilemap_tilemap_setposition(0, spposx, 0);
}

void mainmenu_print(u8 X, u8 Y, const char* text, u16 text_len)
{
	game_print(2, X, Y, text, text_len);
}

void mainmenu_printoptions()
{
    mainmenu_print( 17, 13, (game_settings.game_practice_mode == 0 ? "NORMAL  " : "PRACTICE"), 8);
	mainmenu_print( 17, 14, (game_settings.game_tutorials_enabled != 0 ? "YES" : "NO "), 3);

	u16 curlvl = game_settings.game_current_level + 1;
	char numstr[4] = "    ";
	for(s8 i = 3; i >= 0; i--)
	{
		numstr[i] = '0' + (curlvl % 10);
		curlvl /= 10;
	}
	for(s8 i = 0; i < 4; i++)
	{
		if( numstr[i] == '0' )
		{
			numstr[i] = ' ';
		}
		else
		{
			break;
		}
	}
	mainmenu_print( 17, 16, (const char*)&numstr, 4);
}

void mainmenu_printcursor()
{
	graphics_tilemap_tilemap_settile(2, 3, 11, (menu_selected == 0 ? 59 : 0));
	graphics_tilemap_tilemap_settile(2, 3, 13, (menu_selected == 1 ? 59 : 0));
	graphics_tilemap_tilemap_settile(2, 3, 14, (menu_selected == 2 ? 59 : 0));
	graphics_tilemap_tilemap_settile(2, 3, 16, (menu_selected == 3 ? 59 : 0));
    graphics_tilemap_tilemap_settile(2, 3, 17, (menu_selected == 4 ? 59 : 0));
}
