
#include "stage_level.h"
#include "../resources/playarea.h"
#include "game.h"
#include "stage_levelcomplete.h"
#include "stage_menu.h"
#include "stage_tutorial.h"


extern u8 spdelay;
extern u16 spposx;
extern u16 stposh;
extern const char* codeentry_levelpasswords[];

const char* lvl_scrolltext = "USE DPAD TO MOVE - HOLD A OR B TO PICK UP TILE - USE DPAD WHILST HOLDING TILE TO SLIDE TILE - PRESS SELECT TO RESTART LEVEL - PRESS START TO RETURN TO MENU - ";

const char* lvl_scrolltextpractice = "USE DPAD TO MOVE - HOLD A OR B TO PICK UP TILE - USE DPAD WHILST HOLDING TILE TO SLIDE TILE - PRESS SELECT TO RESTART LEVEL - PRESS START TO RETURN TO MENU - L AND R BUTTONS TO SWAP LEVELS - ";

u8 password_timeout;
u8 password_displaytype;
u8 level_author[8];

u16 cursor_ramp[] = { 544, 552, 560, 568, 560, 552 }; // { 272, 276, 280, 284 };
u8 cursor_ramppos = 0;
u8 cursor_rampdelay = 0;

s16 cursor_positionx = 0;
s16 cursor_positiony = 0;

u8 moving_delay = 0;
u8 moving_itemtype = 0;

u8 moving_spriteindex = 255;
s16 moving_targetx = 0;
s16 moving_targety = 0;

u16 lasers_progress = 0;
u8  lasers_complete = 0;

u8 target_count = 99;
u8 target_hit = 0;

void level_findtarget(s8 HorizontalDelta, s8 VerticalDelta);
void level_settile(u8 X, u8 Y, u8 ItemType);
void level_tracelasers();
u8 level_tracelaser_single(u8* MapX, u8* MapY, u8 LaserColour, u8* MovingDirection);
void level_scrolltext();
void level_mergelaser(u8 TileX, u8 TileY, u16 WantTile);
void level_swappasswordtext();

void level_start()
{
	spdelay = 0;
	spposx = 0;
	stposh = 0;

    password_timeout = 0;
    password_displaytype = 0;

	for(int x = 0; x < 30; x++)
	{
		graphics_tilemap_tilemap_settile(0, x, 19, 0);
	}

	level_resetlevel();
	graphics_sprites_configure(2, cursor_ramp[cursor_ramppos], COLOURS_8BPP, 0, SIZE_16x16);
	graphics_sprites_position(2, 2, 1, 0, 0, MIRROR_NONE);
	graphics_tilemap_tilemap_setposition(0, 0, 4);

    audio_music_play(3);
	//audio_music_seek(16);
}

void level_finish()
{
	audio_music_stop();
	graphics_sprites_position(2, 2, 0, 0, 0, MIRROR_NONE);
}

void level_update()
{

	if( game_settings.game_tutorials_enabled != 0 && tutorial_level <= game_settings.game_current_level && tutorial_doeslevelhavetutorial(game_settings.game_current_level) != 0 )
	{
		engine_changestage((StageRecord*)&tutorial_stage);
		return;
	}

	spdelay = (spdelay + 1) % 2;
	if (spdelay == 0) { level_scrolltext(); }

    password_timeout = ( password_timeout + 1 ) % 128;
    if( password_timeout == 0 ) { level_swappasswordtext(); }

	if (game_settings.game_practice_mode != 0)
	{
		if (input_button_pressed(BUTTON_L))
		{
			if (game_settings.game_current_level > 0) { game_settings.game_current_level--; }
			level_resetlevel();
			return;
		}

		if (input_button_pressed(BUTTON_R))
		{
			if (game_settings.game_current_level < 127) { game_settings.game_current_level++; }
			level_resetlevel();
			return;
		}
	}

	u16 numtoprint = game_settings.game_current_level_moves_remaining;
	game_printlargenumber(1, 22, 14, numtoprint, 4);

	cursor_rampdelay = (cursor_rampdelay + 1) % 3;
	if( cursor_rampdelay == 0 )
	{
		cursor_ramppos = (cursor_ramppos + 1) % 6;
		graphics_sprites_configure(2, cursor_ramp[cursor_ramppos], COLOURS_8BPP, 0, SIZE_16x16);
	}

	if (input_button_pressed(BUTTON_QUIT) || input_button_pressed(BUTTON_Start))
	{
		engine_changestage((StageRecord*)&mainmenu_stage);
		return;
	}

	u8 sprite_plane = 0;
	s16 sprite_x = 0;
	s16 sprite_y = 0;
	if( moving_spriteindex == 255 )
	{

		if( input_button_pressed( BUTTON_Select ) )
		{
			level_resetlevel();
			return;
		}

		// Draw Lasers!
		if( lasers_complete == 0 )
		{
			level_tracelasers();
			return;
		}

		if( target_count == target_hit || game_settings.game_current_level_moves_remaining == 0 )
		{
			// Level Complete
			engine_changestage((StageRecord*)&levelcomplete_stage);
			return;
		}

		if( input_button_held( BUTTON_A ) || input_button_held( BUTTON_B ) )
		{
			u8 tileitem = game_settings.game_current_level_map_layout[(cursor_positiony * 10) + cursor_positionx];
			if( game_itemtype_pickable(tileitem) != 0 )
			{
				moving_itemtype = tileitem;
				graphics_sprites_configure(1, game_itemtype_to_graphic(moving_itemtype) << 1, COLOURS_8BPP, 0, SIZE_16x16);
				graphics_sprites_position(1, 2, 1, cursor_positionx << 4, cursor_positiony << 4, MIRROR_NONE);
				if( input_button_pressed( DPAD_Down ) && cursor_positiony < 7 )
				{
					level_findtarget(0, 1);
                    if( moving_targetx >> 4 != cursor_positionx || moving_targety >> 4 != cursor_positiony )
                    {
                        level_settile(cursor_positionx, cursor_positiony, EMPTY_TILE);
                        moving_spriteindex = 1;
                        if (game_settings.game_practice_mode == 0)
                        {
                            game_settings.game_current_level_moves_remaining--;
                        }
                        if (input_button_held(BUTTON_A))
                        {
                            cursor_positionx = moving_targetx >> 4;
                            cursor_positiony = moving_targety >> 4;
                            graphics_sprites_position(2, 2, 1, cursor_positionx << 4, cursor_positiony << 4, MIRROR_NONE);
                        }
                    }
				}
				else if( input_button_pressed( DPAD_Up ) && cursor_positiony > 0 )
				{
					level_findtarget(0, -1);
                    if( moving_targetx >> 4 != cursor_positionx || moving_targety >> 4 != cursor_positiony )
                    {
                        level_settile(cursor_positionx, cursor_positiony, EMPTY_TILE);
                        moving_spriteindex = 1;
                        if (game_settings.game_practice_mode == 0)
                        {
                            game_settings.game_current_level_moves_remaining--;
                        }
                        if (input_button_held(BUTTON_A))
                        {
                            cursor_positionx = moving_targetx >> 4;
                            cursor_positiony = moving_targety >> 4;
                            graphics_sprites_position(2, 2, 1, cursor_positionx << 4, cursor_positiony << 4, MIRROR_NONE);
                        }
                    }
				}
				else if( input_button_pressed( DPAD_Right ) && cursor_positionx < 9 )
				{
					level_findtarget(1, 0);
                    if( moving_targetx >> 4 != cursor_positionx || moving_targety >> 4 != cursor_positiony )
                    {
                        level_settile(cursor_positionx, cursor_positiony, EMPTY_TILE);
                        moving_spriteindex = 1;
                        if (game_settings.game_practice_mode == 0)
                        {
                            game_settings.game_current_level_moves_remaining--;
                        }
                        if (input_button_held(BUTTON_A))
                        {
                            cursor_positionx = moving_targetx >> 4;
                            cursor_positiony = moving_targety >> 4;
                            graphics_sprites_position(2, 2, 1, cursor_positionx << 4, cursor_positiony << 4, MIRROR_NONE);
                        }
                    }
				}
				else if( input_button_pressed( DPAD_Left ) && cursor_positionx > 0 )
				{
					level_findtarget(-1, 0);
                    if( moving_targetx >> 4 != cursor_positionx || moving_targety >> 4 != cursor_positiony )
                    {
                        level_settile(cursor_positionx, cursor_positiony, EMPTY_TILE);
                        moving_spriteindex = 1;
                        if (game_settings.game_practice_mode == 0)
                        {
                            game_settings.game_current_level_moves_remaining--;
                        }
                        if (input_button_held(BUTTON_A))
                        {
                            cursor_positionx = moving_targetx >> 4;
                            cursor_positiony = moving_targety >> 4;
                            graphics_sprites_position(2, 2, 1, cursor_positionx << 4, cursor_positiony << 4, MIRROR_NONE);
                        }
                    }
				}
			}
		}
		else
		{
            if( moving_delay == 0 )
            {
                graphics_sprites_position(1, 2, 0, 0, 0, MIRROR_NONE);		// Turn off "moving tile" sprite
                if( input_button_held( DPAD_Down ) && cursor_positiony < 7 )
                {
                    moving_spriteindex = 2;
                    cursor_positiony++;
                }
                else if( input_button_held( DPAD_Up ) && cursor_positiony > 0 )
                {
                    moving_spriteindex = 2;
                    cursor_positiony--;
                }
                else if( input_button_held( DPAD_Right ) && cursor_positionx < 9 )
                {
                    moving_spriteindex = 2;
                    cursor_positionx++;
                }
                else if( input_button_held( DPAD_Left ) && cursor_positionx > 0 )
                {
                    moving_spriteindex = 2;
                    cursor_positionx--;
                }
                moving_targetx = cursor_positionx << 4;
                moving_targety = cursor_positiony << 4;
                moving_itemtype = 0;
                moving_delay = 12;
            }
            else if( moving_delay > 0 )
            {
                moving_delay--;
            }
            if( input_button_held(DPAD_Left | DPAD_Down | DPAD_Right | DPAD_Up) == 0 )
            {
                moving_delay = 0;
            }
		}
	}
	else
	{
        if( input_button_held(DPAD_Left | DPAD_Down | DPAD_Right | DPAD_Up) == 0 )
        {
            moving_delay = 0;
        }

		graphics_sprites_position_get(moving_spriteindex, &sprite_plane, &sprite_x, &sprite_y);
		if( sprite_x < moving_targetx ) { sprite_x += 2; }
		if( sprite_x > moving_targetx ) { sprite_x -= 2; }
		if( sprite_y < moving_targety ) { sprite_y += 2; }
		if( sprite_y > moving_targety ) { sprite_y -= 2; }
		graphics_sprites_position(moving_spriteindex, sprite_plane, 1, sprite_x, sprite_y, MIRROR_NONE);
		if( sprite_x == moving_targetx && sprite_y == moving_targety )
		{
			if( moving_itemtype != 0 )
			{
				// Drop sprite back into map
				level_settile( (moving_targetx >> 4), (moving_targety >> 4), moving_itemtype );
				graphics_sprites_position(1, 2, 0, 0, 0, MIRROR_NONE);		// Turn off "moving tile" sprite
				moving_itemtype = 0;
				lasers_progress = 0;
				lasers_complete = 0;
			}
			moving_spriteindex = 255;
		}
	}

}

void level_resetlevel()
{
	u8 x = 0;
	u8 y = 0;
	graphics_tilemap_tilemap_setposition(1, 0, 0);
	graphics_tilemap_tilemap_setposition(2, 4, 4);
	for(y = 0; y < 20; y++)
	{
		for(x = 0; x < 30; x++)
		{
			if( y < 19 ) { graphics_tilemap_tilemap_settile(0, x, y, playarea_tmx_bottom_layer_data[(y * 30) + x]); }
			graphics_tilemap_tilemap_settile(1, x, y, playarea_tmx_mid_layer_data[(y * 30) + x]);
			graphics_tilemap_tilemap_settile(2, x, y, playarea_tmx_top_layer_data[(y * 30) + x]);
		}
	}

	const u8* leveldata = GetLevelData();
	for(x = 0; x < 10; x++)
	{
		for(y = 0; y < 8; y++)
		{
			if( (leveldata[x] & ( 1 << y )) != 0 )
			{
				level_settile(x, y, WALL_TILE);
			}
			else
			{
				level_settile(x, y, EMPTY_TILE);
			}
		}
	}
	// Load Items
	u8 itemptr = 10;
	target_count = 0;
	while(leveldata[itemptr] != 0xFF)
	{
		u8 itemtype = leveldata[itemptr];
		u8 itempos = leveldata[itemptr + 1];
		x = itempos >> 4;
		y = itempos & 0x0F;
		level_settile(x, y, itemtype);

		if( itemtype == ITEM_TARGET_R || itemtype == ITEM_TARGET_G || itemtype == ITEM_TARGET_B )
		{
			target_count++;
		}

		itemptr++;
		itemptr++;
	}
	itemptr++;
	x = 21;
	// Load Name
	while(leveldata[itemptr] != 0x00)
	{
		graphics_tilemap_tilemap_settile(1, x, 10, leveldata[itemptr] );
        level_author[x - 21] = leveldata[itemptr];
		x++;
		itemptr++;
	}
	itemptr++;
	game_settings.game_current_level_moves_remaining = (game_settings.game_practice_mode != 0 ? 99 : leveldata[itemptr]);
	u16 numtoprint = 128;
	numtoprint = game_settings.game_current_level + 1;
	game_printlargenumber(1, 23, 7, numtoprint, 3);
	numtoprint = game_settings.game_current_level_moves_remaining;
	game_printlargenumber(1, 22, 14, numtoprint, 4);

	lasers_progress = 0;
	lasers_complete = 0;

	cursor_positionx = 0;
	cursor_positiony = 0;
	moving_spriteindex = 255;
	graphics_sprites_position(2, 2, 1, 0, 0, MIRROR_NONE);
	moving_targetx = 0;
	moving_targety = 0;
}

void level_findtarget(s8 HorizontalDelta, s8 VerticalDelta)
{
	u8 targetx = cursor_positionx;
	u8 targety = cursor_positiony;

	while(1)
	{
		s8 checkx = targetx + HorizontalDelta;
		s8 checky = targety + VerticalDelta;
		if( checkx >= 0 && checkx < 10 && checky >= 0 && checky < 8 && game_settings.game_current_level_map_layout[(checky * 10) + checkx] == EMPTY_TILE )
		{
			targetx = checkx;
			targety = checky;
		}
		else
		{
			break;
		}
	}

	moving_targetx = targetx << 4;
	moving_targety = targety << 4;
}

void level_settile(u8 X, u8 Y, u8 ItemType)
{
	u16 itemgraphic = game_itemtype_to_graphic(ItemType);
	graphics_tilemap_tilemap_settile(1, (X << 1)    , (Y << 1)    , itemgraphic +  0);
	graphics_tilemap_tilemap_settile(1, (X << 1) + 1, (Y << 1)    , itemgraphic +  1);
	graphics_tilemap_tilemap_settile(1, (X << 1)    , (Y << 1) + 1, itemgraphic +  2);
	graphics_tilemap_tilemap_settile(1, (X << 1) + 1, (Y << 1) + 1, itemgraphic +  3);
	game_settings.game_current_level_map_layout[(Y * 10) + X] = ItemType;
}

void level_tracelasers()
{
	// Just bypass laser drawing for now
	u8 needsmoretracing = 0;
	u8 y;
	u8 x;

	target_hit = 0;

	for (y = 0; y < 18; y++)
	{
		for (x = 0; x < 22; x++)
		{
			graphics_tilemap_tilemap_settile(2, x, y, 0);
		}
	}

	// Reset "hit" targets
	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 10; x++)
		{
			switch(game_settings.game_current_level_map_layout[(y * 10) + x])
			{
				case ITEM_TARGET_R:
				case ITEM_TARGET_G:
				case ITEM_TARGET_B:
					level_settile(x, y, game_settings.game_current_level_map_layout[(y * 10) + x]);
					break;
			}
		}
	}

	for(y = 0; y < 8; y++ )
	{
		for(x = 0; x < 10; x++)
		{
			if( game_settings.game_current_level_map_layout[(y * 10) + x] >= ITEM_LASER_G_L
				&& game_settings.game_current_level_map_layout[(y * 10) + x] <= ITEM_LASER_R_D )
			{
				u8 batteryattached = 0;
				if (x > 0 && game_settings.game_current_level_map_layout[(y * 10) + x - 1] == ITEM_BATTERY) { batteryattached++; }
				if (x < 9 && game_settings.game_current_level_map_layout[(y * 10) + x + 1] == ITEM_BATTERY) { batteryattached++; }
				if (y > 0 && game_settings.game_current_level_map_layout[((y-1) * 10) + x] == ITEM_BATTERY) { batteryattached++; }
				if (y < 7 && game_settings.game_current_level_map_layout[((y+1) * 10) + x] == ITEM_BATTERY) { batteryattached++; }

				if (batteryattached > 0)
				{
					u8 tracex = x;
					u8 tracey = y;
					u8 colour = (game_settings.game_current_level_map_layout[(y * 10) + x] - ITEM_LASER_G_L) >> 2;
					u8 direction = (game_settings.game_current_level_map_layout[(y * 10) + x] - ITEM_LASER_G_L) % 4;
					u8 lastmov = 0;
					for (u8 t = 0; t <= lasers_progress; t++)
					{
						lastmov = level_tracelaser_single(&tracex, &tracey, colour, &direction);
						if (lastmov == 0) { break; }
					}
					needsmoretracing += lastmov;
				}
			}
		}
	}

	if (needsmoretracing == 0)
	{
		lasers_complete = 1;
	}
	else
	{
		lasers_progress++;
	}
}

// Returns 0 if path is blocked
u8 level_tracelaser_single(u8* MapX, u8* MapY, u8 LaserColour, u8* MovingDirection)
{
	u16 lasertiles = 432 + (10 * LaserColour);
	u8 mapx = *MapX;
	u8 mapy = *MapY;

	switch(*MovingDirection)
	{
		case LASER_DIRECTION_LEFT:
			if( mapx == 0 ) { return 0; }
			mapx--;
			break;
		case LASER_DIRECTION_RIGHT:
			if( mapx == 9 ) { return 0; }
			mapx++;
			break;
		case LASER_DIRECTION_UP:
			if( mapy == 0 ) { return 0; }
			mapy--;
			break;
		case LASER_DIRECTION_DOWN:
			if( mapy == 7 ) { return 0; }
			mapy++;
			break;
	}

	switch( game_settings.game_current_level_map_layout[(mapy * 10) + mapx] )
	{
		case WALL_TILE:
		case ITEM_BATTERY:
		case ITEM_LASER_B_D:
		case ITEM_LASER_B_U:
		case ITEM_LASER_B_L:
		case ITEM_LASER_B_R:
		case ITEM_LASER_R_D:
		case ITEM_LASER_R_U:
		case ITEM_LASER_R_L:
		case ITEM_LASER_R_R:
		case ITEM_LASER_G_D:
		case ITEM_LASER_G_U:
		case ITEM_LASER_G_L:
		case ITEM_LASER_G_R:
			level_rollbacklaser(mapx, mapy, *MovingDirection);
			return 0;
			break;
		case ITEM_TARGET_R:
			level_rollbacklaser(mapx, mapy, *MovingDirection);
			if(LaserColour == LASER_COLOUR_R) 
			{ 
				target_hit++; 
				graphics_tilemap_tilemap_settile(1, (mapx << 1), (mapy << 1), graphics_tilemap_tilemap_gettile(1, (mapx << 1), (mapy << 1)) + 4);
				graphics_tilemap_tilemap_settile(1, (mapx << 1) + 1, (mapy << 1), graphics_tilemap_tilemap_gettile(1, (mapx << 1) + 1, (mapy << 1)) + 4);
				graphics_tilemap_tilemap_settile(1, (mapx << 1), (mapy << 1) + 1, graphics_tilemap_tilemap_gettile(1, (mapx << 1), (mapy << 1) + 1) + 4);
				graphics_tilemap_tilemap_settile(1, (mapx << 1) + 1, (mapy << 1) + 1, graphics_tilemap_tilemap_gettile(1, (mapx << 1) + 1, (mapy << 1) + 1) + 4);
				return 0; 
			}
			break;
		case ITEM_TARGET_G:
			level_rollbacklaser(mapx, mapy, *MovingDirection);
			if(LaserColour == LASER_COLOUR_G) 
			{ 
				target_hit++; 
				graphics_tilemap_tilemap_settile(1, (mapx << 1), (mapy << 1), graphics_tilemap_tilemap_gettile(1, (mapx << 1), (mapy << 1)) + 4);
				graphics_tilemap_tilemap_settile(1, (mapx << 1) + 1, (mapy << 1), graphics_tilemap_tilemap_gettile(1, (mapx << 1) + 1, (mapy << 1)) + 4);
				graphics_tilemap_tilemap_settile(1, (mapx << 1), (mapy << 1) + 1, graphics_tilemap_tilemap_gettile(1, (mapx << 1), (mapy << 1) + 1) + 4);
				graphics_tilemap_tilemap_settile(1, (mapx << 1) + 1, (mapy << 1) + 1, graphics_tilemap_tilemap_gettile(1, (mapx << 1) + 1, (mapy << 1) + 1) + 4);
				return 0; 
			}
			break;
		case ITEM_TARGET_B:
			level_rollbacklaser(mapx, mapy, *MovingDirection);
			if (LaserColour == LASER_COLOUR_B) 
			{ 
				target_hit++; 
				graphics_tilemap_tilemap_settile(1, (mapx << 1), (mapy << 1), graphics_tilemap_tilemap_gettile(1, (mapx << 1), (mapy << 1)) + 4);
				graphics_tilemap_tilemap_settile(1, (mapx << 1) + 1, (mapy << 1), graphics_tilemap_tilemap_gettile(1, (mapx << 1) + 1, (mapy << 1)) + 4);
				graphics_tilemap_tilemap_settile(1, (mapx << 1), (mapy << 1) + 1, graphics_tilemap_tilemap_gettile(1, (mapx << 1), (mapy << 1) + 1) + 4);
				graphics_tilemap_tilemap_settile(1, (mapx << 1) + 1, (mapy << 1) + 1, graphics_tilemap_tilemap_gettile(1, (mapx << 1) + 1, (mapy << 1) + 1) + 4);
				return 0; 
			}
			break;
		case ITEM_MIRROR_UL:
			switch(*MovingDirection)
			{
				case LASER_DIRECTION_LEFT:
					*MovingDirection = LASER_DIRECTION_DOWN;
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 2, (mapy << 1) + 1, lasertiles + 1);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 8);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 8);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 2, lasertiles + 4);
					break;
				case LASER_DIRECTION_RIGHT:
					*MovingDirection = LASER_DIRECTION_UP;
					graphics_tilemap_tilemap_settile(2, (mapx << 1), (mapy << 1) + 1, lasertiles + 1);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 7);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 7);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1), lasertiles + 4);
					break;
				case LASER_DIRECTION_UP:
					*MovingDirection = LASER_DIRECTION_RIGHT;
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 2, (mapy << 1) + 1, lasertiles + 1);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 8);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 8);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 2, lasertiles + 4);
					break;
				case LASER_DIRECTION_DOWN:
					*MovingDirection = LASER_DIRECTION_LEFT;
					graphics_tilemap_tilemap_settile(2, (mapx << 1), (mapy << 1) + 1, lasertiles + 1);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 7);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 7);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1), lasertiles + 4);
					break;
			}
			break;
		case ITEM_MIRROR_UR:
			switch(*MovingDirection)
			{
				case LASER_DIRECTION_LEFT:
					*MovingDirection = LASER_DIRECTION_UP;
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 2, (mapy << 1) + 1, lasertiles + 1);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 6);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 6);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1), lasertiles + 4);
					break;
				case LASER_DIRECTION_RIGHT:
					*MovingDirection = LASER_DIRECTION_DOWN;
					graphics_tilemap_tilemap_settile(2, (mapx << 1), (mapy << 1) + 1, lasertiles + 1);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 9);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 9);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 2, lasertiles + 4);
					break;
				case LASER_DIRECTION_UP:
					*MovingDirection = LASER_DIRECTION_LEFT;
					graphics_tilemap_tilemap_settile(2, (mapx << 1), (mapy << 1) + 1, lasertiles + 1);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 9);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 9);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 2, lasertiles + 4);
					break;
				case LASER_DIRECTION_DOWN:
					*MovingDirection = LASER_DIRECTION_RIGHT;
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 2, (mapy << 1) + 1, lasertiles + 1);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 6);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 6);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1), lasertiles + 4);
					break;
			}
			break;

		default:

			if( game_settings.game_current_level_map_layout[(mapy * 10) + mapx] == ITEM_SIDEPIPE )
			{
				if( *MovingDirection == LASER_DIRECTION_UP || *MovingDirection == LASER_DIRECTION_DOWN )
				{
					level_rollbacklaser(mapx, mapy, *MovingDirection);
					return 0;
				}
			}
			if( game_settings.game_current_level_map_layout[(mapy * 10) + mapx] == ITEM_DOWNPIPE )
			{
				if( *MovingDirection == LASER_DIRECTION_LEFT || *MovingDirection == LASER_DIRECTION_RIGHT )
				{ 
					level_rollbacklaser(mapx, mapy, *MovingDirection);
					return 0; 
				}
			}

			switch (*MovingDirection)
			{
				case LASER_DIRECTION_LEFT:
					graphics_tilemap_tilemap_settile(2, (mapx << 1), (mapy << 1) + 1, lasertiles + 1);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 1);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 1);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 2, (mapy << 1) + 1, lasertiles + 1);
					break;
				case LASER_DIRECTION_RIGHT:
					graphics_tilemap_tilemap_settile(2, (mapx << 1), (mapy << 1) + 1, lasertiles + 1);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 1);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 1);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 2, (mapy << 1) + 1, lasertiles + 1);
					break;
				case LASER_DIRECTION_UP:
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1), lasertiles + 4);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 4);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 4);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 2, lasertiles + 4);
					break;
				case LASER_DIRECTION_DOWN:
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1), lasertiles + 4);
					//graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 4);
					level_mergelaser((mapx << 1) + 1, (mapy << 1) + 1, lasertiles + 4);
					graphics_tilemap_tilemap_settile(2, (mapx << 1) + 1, (mapy << 1) + 2, lasertiles + 4);
					break;
			}

	}

	*MapX = mapx;
	*MapY = mapy;
	return 1;
}

void level_rollbacklaser(u8 MapX, u8 MapY, u8 Direction)
{
	u16 checktile;
	u16 lasertile;

	u16 sector[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	u8 basex = (MapX << 1);
	u8 basey = (MapY << 1);
	for (u8 y = 0; y < 3; y++)
	{
		for (u8 x = 0; x < 3; x++)
		{
			sector[x][y] = graphics_tilemap_tilemap_gettile(2, basex + x, basey + y);
		}
	}
	checktile = sector[1][1];
	if(checktile != 0 )
	{
		lasertile = (checktile - 432) % 10;
		if( lasertile == 4 )
		{ 
			if (sector[1][2] == 0) { checktile--; }
			if (sector[1][0] == 0) { checktile++; }
		}
		if (lasertile == 1)
		{
			if (sector[0][1] == 0) { checktile--; }
			if (sector[2][1] == 0) { checktile++; }
		}

		graphics_tilemap_tilemap_settile(2, basex + 1, basey + 1, checktile);
	}
	else if(sector[1][0] != 0)
	{
		lasertile = (sector[1][0] - 432) % 10;
		if (lasertile == 4) { graphics_tilemap_tilemap_settile(2, basex + 1, basey, sector[1][0] - 1); }
	}
	else if(sector[1][2] != 0)
	{
		lasertile = (sector[1][2] - 432) % 10;
		if (lasertile == 4) { graphics_tilemap_tilemap_settile(2, basex + 1, basey + 2, sector[1][2] + 1); }
		//graphics_tilemap_tilemap_settile(2, basex + 1, basey + 2, sector[1][2] + 1);
	}
	else if (sector[0][1] != 0)
	{
		lasertile = (sector[0][1] - 432) % 10;
		if (lasertile == 1) { graphics_tilemap_tilemap_settile(2, basex, basey + 1, sector[0][1] + 1); }
		//graphics_tilemap_tilemap_settile(2, basex, basey + 1, sector[0][1] + 1);
	}
	else if (sector[2][1] != 0)
	{
		lasertile = (sector[2][1] - 432) % 10;
		if (lasertile == 1) { graphics_tilemap_tilemap_settile(2, basex + 2, basey + 1, sector[2][1] - 1); }
		//graphics_tilemap_tilemap_settile(2, basex + 2, basey + 1, sector[2][1] - 1);
	}
}

void level_scrolltext()
{
	spposx++;
	if (spposx == 8)
	{
		for (int x = 1; x < 30; x++)
		{
			graphics_tilemap_tilemap_settile(0, x - 1, 19, graphics_tilemap_tilemap_gettile(0, x, 19));
		}
		if (game_settings.game_practice_mode == 0)
		{
			graphics_tilemap_tilemap_settile(0, 29, 19, (u16)lvl_scrolltext[stposh]);
			stposh = (stposh + 1) % 158;
		}
		else
		{
			graphics_tilemap_tilemap_settile(0, 29, 19, (u16)lvl_scrolltextpractice[stposh]);
			stposh = (stposh + 1) % 191;
		}
		spposx = 0;
	}
	graphics_tilemap_tilemap_setposition(0, spposx, 4);
}

void level_mergelaser(u8 TileX, u8 TileY, u16 WantTile)
{
	// Green starts at 432
	// Blue starts at  442
	// Red starts at  452
	// Red Horz cross 462 (red), 463 (green), 464 (blue)
	// Gren Horz cross 465 (red), 466 (green), 467 (blue)
	// Blue Horz cross 468 (red), 469 (green), 470 (blue)
	u16 curtile = graphics_tilemap_tilemap_gettile(2, TileX, TileY);
	u16 dsttile = WantTile;
	u16 lower = (WantTile < curtile ? WantTile : curtile);
	u16 upper = (WantTile > curtile ? WantTile : curtile);

	if (curtile != 0)
	{
		switch (lower) 
		{
			case 433: // Green Horz
				if (upper == 436) { dsttile = 466; }
				if (upper == 446) { dsttile = 467; }
				if (upper == 456) { dsttile = 465; }
				break;
			case 436: // Green Vert
				if (upper == 443) { dsttile = 469; }
				if (upper == 453) { dsttile = 463; }
				break;
			case 443: // Blue Horz
				if (upper == 436) { dsttile = 469; }
				if (upper == 446) { dsttile = 470; }
				if (upper == 456) { dsttile = 468; }
				break;
			case 446: // Blue Vert
				if (upper == 453) { dsttile = 464; }
				break;
			case 453: // Green Horz
				if (upper == 436) { dsttile = 463; }
				if (upper == 446) { dsttile = 464; }
				if (upper == 456) { dsttile = 462; }
				break;

			case 438: // Green Bend 1
				if (upper == 441) { dsttile = 475; }
				if (upper == 451) { dsttile = 476; }
				if (upper == 461) { dsttile = 477; }
				break;
			case 439: // Green Bend 2
				if (upper == 440) { dsttile = 484; }
				if (upper == 450) { dsttile = 485; }
				if (upper == 460) { dsttile = 486; }
				break;
			case 440: // Green Bend 3
				if (upper == 449) { dsttile = 487; }
				if (upper == 459) { dsttile = 490; }
				break;
			case 441: // Green Bend 4
				if (upper == 448) { dsttile = 478; }
				if (upper == 458) { dsttile = 481; }
				break;

			case 448: // Blue Bend 1
				if (upper == 451) { dsttile = 479; }
				if (upper == 461) { dsttile = 480; }
				break;
			case 449: // Blue Bend 2
				if (upper == 450) { dsttile = 488; }
				if (upper == 460) { dsttile = 489; }
				break;
			case 450: // Blue Bend 3
				if (upper == 459) { dsttile = 491; }
				break;
			case 451: // Blue Bend 4
				if (upper == 458) { dsttile = 482; }
				break;

			case 458: // Red Bend 1
				if (upper == 461) { dsttile = 483; }
				break;
			case 459: // Red Bend 2
				if (upper == 460) { dsttile = 492; }
				break;

		}

	}

	graphics_tilemap_tilemap_settile(2, TileX, TileY, dsttile);
}

void level_swappasswordtext()
{
    password_displaytype = 1 - password_displaytype;
    if(password_displaytype == 1)
    {
        //graphics_tilemap_tilemap_settile(1, 21 + x, 10, level_author[x] );
        game_print( 1, 23, 9, " BY ", 4);
        for(int x = 0; x < 8; ++x )
        {
            graphics_tilemap_tilemap_settile(1, 21 + x, 10, level_author[x] );
        }
    }
    else
    {
        game_print( 1, 23, 9, "CODE", 4);
        game_print( 1, 21, 10, "        ", 8);
        game_print( 1, 23, 10, codeentry_levelpasswords[game_settings.game_current_level], 4);
    }
}
