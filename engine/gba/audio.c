
#include "gba.h"

void audio_music_play(u16 track_index)
{
    mmStart( track_index, MM_PLAY_LOOP );
}

void audio_music_stop()
{
    mmStop();
}

void audio_music_seek(u32 position)
{
    mmPosition((mm_word)position);
}

void audio_update()
{
    //mmFrame();
}
