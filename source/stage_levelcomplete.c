
#include "stage_levelcomplete.h"
#include "stage_complete.h"
#include "stage_level.h"
#include "game.h"

u8 spritescreated;

void levelcomplete_start()
{
    if( target_count == target_hit )
    {
        spritescreated = game_dialoguebox_sprited(2, 5, 7, "* CONGRATULATIONS *", 19, 4);
    }
    else
    {
        spritescreated = game_dialoguebox_sprited(2, 5, 7, "+ OUT OF SHIFTS +", 17, 4);
    }
    audio_music_play(2);
}

void levelcomplete_finish()
{
    audio_music_stop();
    for (u8 sprite = 4; sprite < 4 + spritescreated; sprite++)
    {
        graphics_sprites_position(sprite, 0, 0, 0, 0, MIRROR_NONE);
    }
}

void levelcomplete_update()
{
    if( input_button_pressed( BUTTON_A ) || input_button_pressed( BUTTON_B ) )
    {
        if( target_count == target_hit )
        {
            if (game_settings.game_current_level == 127)
            {
                engine_changestage((StageRecord*)&gamecomplete_stage);
                return;
            }
            else
            {
                game_settings.game_current_level++;
                // Don't save level limit if in practice mode
                if (game_settings.game_practice_mode == 0)
                {
                    if (game_settings.game_current_level > game_settings.game_maximum_level)
                    {
                        game_settings.game_maximum_level = game_settings.game_current_level;
                    }
                    SaveSRAMData(); // Save current level, if SRAM is available
                }
            }
        }
        target_hit = 0;
        target_count = 99;
        engine_changestage((StageRecord*)&level_stage);
    }
}

