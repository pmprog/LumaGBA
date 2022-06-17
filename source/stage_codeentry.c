
#include "stage_codeentry.h"
#include "../resources/codeentry.h"
#include "../resources/titlescreen.h"
#include "stage_menu.h"
#include "stage_level.h"
#include "game.h"

void codeentry_configurecursor();

u8 codeentry_cursorx;
u8 codeentry_cursory;
u8 codeentry_currentcode[4] = { ' ', ' ', ' ', ' ' };
u8 codeentry_codepos;

extern u8 spritescreated;
u8 codeentry_dialogueopen;

const char* codeentry_levelpasswords[] = {
 "PQUM",
 "BOOF",
 "TZTK",
 "BDMO",
 "CZPJ",
 "RPMT",
 "YBIG",
 "WZJV",
 "AXRF",
 "MVNC",
 "TYHC",
 "TIHI",
 "WWPE",
 "JCBN",
 "ANCV",
 "UKNP",
 "CAMK",
 "MTPL",
 "HNRA",
 "EUHO",
 "FQRS",
 "LYEY",
 "GKAE",
 "VPTV",
 "EVGE",
 "EOWA",
 "AMQD",
 "RIEB",
 "UXFP",
 "UGOV",
 "KJAH",
 "XGQL",
 "IJDU",
 "FHYB",
 "LKRH",
 "TITT",
 "QQSF",
 "JXZC",
 "YQJA",
 "RQSN",
 "JEJA",
 "ZROY",
 "SBZN",
 "RNXB",
 "CHUX",
 "VHCM",
 "OMJO",
 "PILC",
 "OEXC",
 "GYSC",
 "PHRA",
 "EJNM",
 "XFMD",
 "OBZX",
 "XVHP",
 "WBFS",
 "ASLW",
 "NQGK",
 "SAWS",
 "VSCA",
 "AMYL",
 "YLMP",
 "LBFJ",
 "YBBJ",
 "BUJF",
 "RMOX",
 "DEAC",
 "IPLJ",
 "SFVU",
 "IIWW",
 "LZUR",
 "MSMO",
 "MTAF",
 "ACWR",
 "RTDI",
 "BPGM",
 "AEZJ",
 "MSXR",
 "SQSH",
 "SUZL",
 "BCRW",
 "CVOG",
 "DPFV",
 "DAPE",
 "ZQQW",
 "UKLR",
 "GNPV",
 "CEXR",
 "IISC",
 "PNRM",
 "WAZK",
 "LWZF",
 "JRFY",
 "HSFT",
 "JYJO",
 "LBJA",
 "JDMN",
 "USTD",
 "XKPD",
 "IIIU",
 "FSEY",
 "ZLEZ",
 "RCFI",
 "OFRO",
 "XYOD",
 "DSKK",
 "DKGN",
 "ACMA",
 "ETKT",
 "MXKC",
 "VSDE",
 "OCJW",
 "VMGP",
 "FNZG",
 "JEMR",
 "JHIT",
 "BFME",
 "VMPH",
 "TYDO",
 "MOWL",
 "OGTO",
 "KKYI",
 "FQEM",
 "HMSZ",
 "TTHA",
 "ZFYX",
 "DFGB",
 "AGRE",
};

extern u16 cursor_ramp[];
extern u8 cursor_ramppos;
extern u8 cursor_rampdelay;

void codeentry_start()
{
    codeentry_cursorx = 0;
    codeentry_cursory = 0;
    codeentry_codepos = 0;
    codeentry_currentcode[0] = ' ';
    codeentry_currentcode[1] = ' ';
    codeentry_currentcode[2] = ' ';
    codeentry_currentcode[3] = ' ';

    codeentry_dialogueopen = 0;
    cursor_ramppos = 0;
    cursor_rampdelay = 0;
	for(int y = 0; y < 20; y++)
	{
		for(int x = 0; x < 30; x++)
		{
			graphics_tilemap_tilemap_settile(0, x, y, codeentry_tmx_tile_layer_1_data[(y * 30) + x]);
			graphics_tilemap_tilemap_settile(1, x, y, 0);
			graphics_tilemap_tilemap_settile(2, x, y, 0);
		}
	}

	graphics_tilemap_tilemap_setposition(0, 0, 0);
	graphics_tilemap_tilemap_setposition(1, 0, 0);
	graphics_tilemap_tilemap_setposition(2, 0, 0);

    codeentry_configurecursor();
}

void codeentry_finish()
{
    audio_music_stop();
	graphics_sprites_position(0, 0, 0, 0, 0, MIRROR_NONE);
    graphics_sprites_position(1, 0, 0, 0, 0, MIRROR_NONE);
    graphics_sprites_position(2, 0, 0, 0, 0, MIRROR_NONE);
    graphics_sprites_position(3, 0, 0, 0, 0, MIRROR_NONE);
}

void codeentry_update()
{
    if( codeentry_dialogueopen != 0 )
    {
        if(input_button_pressed(BUTTON_A) || input_button_pressed(BUTTON_B) || input_button_pressed(BUTTON_Start))
        {
            for (u8 sprite = 4; sprite < 4 + spritescreated; sprite++)
            {
                graphics_sprites_position(sprite, 0, 0, 0, 0, MIRROR_NONE);
            }
            codeentry_dialogueopen = 0;
        }
        return;
    }


    game_print(0, 13, 4, codeentry_currentcode, 4);
    codeentry_configurecursor();

    if(input_button_pressed(DPAD_Up))
    {
        if( codeentry_cursory > 0 ) { codeentry_cursory--; }
    }
    if(input_button_pressed(DPAD_Down))
    {
        if( codeentry_cursory < (codeentry_cursorx == 6 ? 2 : 4) ) { codeentry_cursory++; }
        if( codeentry_cursory == 4 && codeentry_cursorx > 1 ) { codeentry_cursorx = 1; }
    }
    if(input_button_pressed(DPAD_Left))
    {
        if( codeentry_cursorx > 0 ) { codeentry_cursorx--; }
    }
    if(input_button_pressed(DPAD_Right))
    {
        if( codeentry_cursorx < 6 ) { codeentry_cursorx++; }
        if( codeentry_cursory == 4 && codeentry_cursorx > 1 ) { codeentry_cursorx = 6; codeentry_cursory = 2; }
        if( codeentry_cursorx == 6 && codeentry_cursory > 2 ) { codeentry_cursory = 2; }
    }

    if(input_button_pressed(BUTTON_A) || input_button_pressed(BUTTON_B) || input_button_pressed(BUTTON_Start))
    {
        if( codeentry_cursorx == 6 )
        {
            switch( codeentry_cursory )
            {
                case 0:
                    for(int i = 0; i < 128; ++i)
                    {
                        if( codeentry_levelpasswords[i][0] == codeentry_currentcode[0] &&
                            codeentry_levelpasswords[i][1] == codeentry_currentcode[1] &&
                            codeentry_levelpasswords[i][2] == codeentry_currentcode[2] &&
                            codeentry_levelpasswords[i][3] == codeentry_currentcode[3])
                        {
                            game_settings.game_current_level = i;
                            game_settings.game_maximum_level = i;
                            SaveSRAMData();
                            engine_changestage((StageRecord*)&level_stage);
                            return;
                        }
                    }

                    spritescreated = game_dialoguebox_sprited(2, 5, 7, "+  INVALID  CODE  +", 19, 4);
                    codeentry_currentcode[0] = ' ';
                    codeentry_currentcode[1] = ' ';
                    codeentry_currentcode[2] = ' ';
                    codeentry_currentcode[3] = ' ';
                    codeentry_codepos = 0;
                    codeentry_dialogueopen = 1;
                    graphics_sprites_position(0, 0, 0, 0, 0, MIRROR_NONE);
                    graphics_sprites_position(1, 0, 0, 0, 0, MIRROR_NONE);
                    graphics_sprites_position(2, 0, 0, 0, 0, MIRROR_NONE);
                    graphics_sprites_position(3, 0, 0, 0, 0, MIRROR_NONE);

                    break;
                case 1:
                    if( codeentry_codepos > 0 )
                    {
                        codeentry_currentcode[--codeentry_codepos] = ' ';
                    }
                    break;
                case 2:
                    engine_changestage((StageRecord*)&mainmenu_stage);
                    return;
                    break;
            }
        }
        else if( codeentry_codepos < 4 )
        {
            u8 chartouse = 'A' + (codeentry_cursory * 6) + codeentry_cursorx;
            codeentry_currentcode[codeentry_codepos] = chartouse;
            codeentry_codepos++;
        }
    }

}

void codeentry_configurecursor()
{
	cursor_rampdelay = (cursor_rampdelay + 1) % 3;
	if( cursor_rampdelay == 0 )
	{
		cursor_ramppos = (cursor_ramppos + 1) % 6;
		graphics_sprites_configure(2, cursor_ramp[cursor_ramppos], COLOURS_8BPP, 0, SIZE_16x16);
	}

	graphics_sprites_configure(0, cursor_ramp[cursor_ramppos], COLOURS_8BPP, 0, SIZE_8x8);
    graphics_sprites_configure(1, cursor_ramp[cursor_ramppos] + 2, COLOURS_8BPP, 0, SIZE_8x8);
    graphics_sprites_configure(2, cursor_ramp[cursor_ramppos] + 4, COLOURS_8BPP, 0, SIZE_8x8);
    graphics_sprites_configure(3, cursor_ramp[cursor_ramppos] + 6, COLOURS_8BPP, 0, SIZE_8x8);

    u8 xpos = 16;
    u8 ypos = 16;

    xpos = 28 + (codeentry_cursorx * 24);
    ypos = 60 + (codeentry_cursory * 16);

	graphics_sprites_position(0, 0, 1, xpos, ypos, MIRROR_NONE);
    graphics_sprites_position(1, 0, 1, xpos + (codeentry_cursorx == 6 ? 32 : 8), ypos, MIRROR_NONE);
    graphics_sprites_position(2, 0, 1, xpos, ypos + 8, MIRROR_NONE);
    graphics_sprites_position(3, 0, 1, xpos + (codeentry_cursorx == 6 ? 32 : 8), ypos + 8, MIRROR_NONE);

}
