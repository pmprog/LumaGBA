
#include "stage_tutorial.h"
#include "stage_level.h"
#include "game.h"

u16 tutorial_level = 0;
u8 tutorial_step = 0;

extern u16 cursor_ramp[];
extern u8 cursor_ramppos;
extern u8 cursor_rampdelay;
extern s16 cursor_positionx;
extern s16 cursor_positiony;


const char* const tute_level1_step0_text[] = {
    "THE AIM IS TO LIGHT",
    "ALL THE COLOURED TARGETS",
    "WITHIN THE NUMBER OF",
    "SHIFTS AVAILABLE",
};

const char* const tute_level1_step1_text[] = {
    "USING LASERS OF THE MATCHING",
    "COLOUR TO LIGHT THEM...",
};

const char* const tute_level1_step2_text[] = {
    "LASERS NEED TO TOUCH A",
    "BATTERY TO OBTAIN POWER...",
};

const char* const tute_level1_step3_text[] = {
    "MOVE THE CURSOR TO SELECT",
    "THE BATTERY, THEN HOLD A",
    "OR B AND PRESS DOWN TO",
    "MOVE IT INTO POSITION",
};

const char* const tute_level2_step0_text[] = {
    "TRY MOVING THESE",
    "BATTERIES TO FINISH",
    "THE LEVEL",
};

const char* const tute_level3_step0_text[] = {
    "MOVE MIRRORS AROUND",
    "TO REFLECT THE BEAM",
    "OF THE LASER SO IT",
    "POINTS IN THE",
    "DESIRED DIRECTION",
};

const char* const tute_level3_step1_text[] = {
    "HINT: YOU MIGHT",
    "NEED TO MOVE THE",
    "BATTERIES FIRST",
};

const char* const tute_level6_step0_text[] = {
    "LASERS CAN ALSO BE MOVED",
    "AND A SINGLE BATTERY CAN",
    "POWER MULTIPLE LASERS",
};

void tutorial_start()
{
    switch( game_settings.game_current_level )
    {
        case 0:
            switch( tutorial_step )
            {
                case 0:
                    game_dialoguebox(1, 5, 2, 25, 5);
                    game_print(2, 6, 3, tute_level1_step0_text[0], 19);
                    game_print(2, 6, 4, tute_level1_step0_text[1], 24);
                    game_print(2, 6, 5, tute_level1_step0_text[2], 20);
                    game_print(2, 6, 6, tute_level1_step0_text[3], 16);
                    graphics_tilemap_tilemap_settile( 1, 18, 7, 473 );
                    graphics_tilemap_tilemap_settile( 1, 19, 7, 474 );
                    break;
                case 1:
                    game_dialoguebox(1, 1, 10, 29, 3);
                    game_print(2, 2, 11, tute_level1_step1_text[0], 28);
                    game_print(2, 2, 12, tute_level1_step1_text[1], 23);
                    graphics_tilemap_tilemap_settile( 1, 2, 13, 473 );
                    graphics_tilemap_tilemap_settile( 1, 3, 13, 474 );
                    break;
                case 2:
                    game_dialoguebox(1, 0, 4, 27, 3);
                    game_print(2, 1, 5, tute_level1_step2_text[0], 22);
                    game_print(2, 1, 6, tute_level1_step2_text[1], 26);
                    graphics_tilemap_tilemap_settile( 1, 0, 7, 473 );
                    graphics_tilemap_tilemap_settile( 1, 1, 7, 474 );
                    break;
                case 3:
                    game_dialoguebox(1, 0, 3, 26, 5);
                    game_print(2, 1, 4, tute_level1_step3_text[0], 25);
                    game_print(2, 1, 5, tute_level1_step3_text[1], 24);
                    game_print(2, 1, 6, tute_level1_step3_text[2], 22);
                    game_print(2, 1, 7, tute_level1_step3_text[3], 21);
                    graphics_tilemap_tilemap_settile( 1, 0, 2, 471 );
                    graphics_tilemap_tilemap_settile( 1, 1, 2, 472 );
                    break;
            }
            break;

        case 1:
            game_dialoguebox(1, 4, 5, 20, 4);
            game_print(2, 5, 6, tute_level2_step0_text[0], 16);
            game_print(2, 5, 7, tute_level2_step0_text[1], 19);
            game_print(2, 5, 8, tute_level2_step0_text[2], 9);
            graphics_tilemap_tilemap_settile( 1, 6, 9, 473 );
            graphics_tilemap_tilemap_settile( 1, 7, 9, 474 );
            break;

        case 2:
            switch( tutorial_step )
            {
                case 0:
                    game_dialoguebox(1, 5, 3, 20, 6);
                    game_print(2, 6, 4, tute_level3_step0_text[0], 19);
                    game_print(2, 6, 5, tute_level3_step0_text[1], 19);
                    game_print(2, 6, 6, tute_level3_step0_text[2], 18);
                    game_print(2, 6, 7, tute_level3_step0_text[3], 13);
                    game_print(2, 6, 8, tute_level3_step0_text[4], 17);
                    graphics_tilemap_tilemap_settile( 1, 18, 2, 471 );
                    graphics_tilemap_tilemap_settile( 1, 19, 2, 472 );
                    break;
                case 1:
                    game_dialoguebox(1, 7, 5, 17, 4);
                    game_print(2, 8, 6, tute_level3_step1_text[0], 15);
                    game_print(2, 8, 7, tute_level3_step1_text[1], 16);
                    game_print(2, 8, 8, tute_level3_step1_text[2], 15);
                    graphics_tilemap_tilemap_settile( 1, 18, 4, 471 );
                    graphics_tilemap_tilemap_settile( 1, 19, 4, 472 );
                    break;
            }
            break;

        case 5:
            game_dialoguebox(1, 2, 7, 25, 4);
            game_print(2, 3, 8, tute_level6_step0_text[0], 24);
            game_print(2, 3, 9, tute_level6_step0_text[1], 24);
            game_print(2, 3,10, tute_level6_step0_text[2], 21);
            graphics_tilemap_tilemap_settile( 1, 6, 11, 473 );
            graphics_tilemap_tilemap_settile( 1, 7, 11, 474 );
            break;


        default:
            tutorial_level = game_settings.game_current_level;
            break;
    }
}

void tutorial_finish()
{
    
}

void tutorial_update()
{
	cursor_rampdelay = (cursor_rampdelay + 1) % 3;
	if( cursor_rampdelay == 0 )
	{
		cursor_ramppos = (cursor_ramppos + 1) % 6;
		graphics_sprites_configure(2, cursor_ramp[cursor_ramppos], COLOURS_8BPP, 0, SIZE_16x16);
	}


    if( input_button_pressed(BUTTON_A) || input_button_pressed(BUTTON_B) )
    {
        switch( game_settings.game_current_level )
        {
            case 0:
                if( tutorial_step < 3 )
                {
                    tutorial_step++;
                }
                else
                {
                    tutorial_level = game_settings.game_current_level + 1;
                    tutorial_step = 0;
                }
                break;

            case 1:
                tutorial_level = game_settings.game_current_level + 1;
                tutorial_step = 0;
                break;

            case 2:
                if( tutorial_step < 1 )
                {
                    tutorial_step++;
                }
                else
                {
                    tutorial_level = game_settings.game_current_level + 1;
                    tutorial_step = 0;
                }
                break;

            default:
                tutorial_level = game_settings.game_current_level + 1;
                tutorial_step = 0;
                break;
        }
        engine_changestage((StageRecord*)&level_stage);
    }
}

u8 tutorial_doeslevelhavetutorial(u16 level)
{
    if( level == 5 ) { return 1; }
    return (level < 3 ? 1 : 0);
}
