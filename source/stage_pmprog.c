
#include "stage_pmprog.h"
#include "stage_phoenix.h"
#include "../resources/titlescreen.h"

float easeoutback(float Time, float Begin, float Change, float Duration, float Swing);

float easeoutback(float Time, float Begin, float Change, float Duration, float Swing)
{
	float time = Time;
	if (Swing == 0)
	{
		Swing = 1.70158f;
	}
	return Change * ((time = time / Duration - 1) * time * ((Swing + 1) * time + Swing) + 1) + Begin;
}

void pmprog_start()
{
    audio_music_play(0);

	for(int s = 0; s < 25; s++)
	{
		graphics_sprites_configure(s, 576 + (s << 1), COLOURS_8BPP, 0, SIZE_8x8);
		graphics_sprites_position(s, 1, 1, 100 + ((s % 5) * 8), 150 + ((s / 5) * 8), MIRROR_NONE);
	}
}

void pmprog_finish()
{
    audio_music_stop();
	graphics_sprites_clear();
}

void pmprog_update()
{
	if(engine_stage_time >= 160)
	{
		engine_changestage((StageRecord*)&phoenix_stage);
		return;
	}

	if(engine_stage_time < 60)
	{
		for(int s = 0; s < 25; s++)
		{
			s32 starty = 150 + ((s / 5) * 8);
			s32 endy = 60 + ((s / 5) * 8);
			u16 cury = (u16)easeoutback((float)engine_stage_time, (float)starty, (float)(endy - starty), 60.0f, 2.0f);
			graphics_sprites_position(s, 1, 1, 100 + ((s % 5) * 8), cury, MIRROR_NONE);
		}
	}
	else if (engine_stage_time >= 100)
	{
		for(int s = 0; s < 25; s++)
		{
			s32 starty = 150 + ((s / 5) * 8);
			s32 endy = 60 + ((s / 5) * 8);
			u16 cury = (u16)easeoutback((float)engine_stage_time - 100, (float)endy, (float)(starty - endy + 20), 70.0f, 1.0f);
			graphics_sprites_position(s, 1, 1, 100 + ((s % 5) * 8), cury, MIRROR_NONE);
		}
	}
}
