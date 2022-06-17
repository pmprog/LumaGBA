
#include "allegro5.h"
#include <stdio.h>

ALLEGRO_VOICE* audiovoice = NULL;
ALLEGRO_MIXER* audiomixer = NULL;
ALLEGRO_AUDIO_STREAM* audiostream = NULL;

void audio_music_play(u16 track_index)
{
    char filename[200];
    sprintf((char*)&filename, "track_%d.mod", track_index);
    audiostream = al_load_audio_stream(&filename, 4, 2048);
    if (audiostream == NULL)
    {
        sprintf((char*)&filename, "music/track_%d.mod", track_index);
        audiostream = al_load_audio_stream(&filename, 4, 2048);
    }
    if (audiostream == NULL)
    {
        sprintf((char*)&filename, "resource/track_%d.mod", track_index);
        audiostream = al_load_audio_stream(&filename, 4, 2048);
    }
    if (audiostream == NULL)
    {
        sprintf((char*)&filename, "resources/track_%d.mod", track_index);
        audiostream = al_load_audio_stream(&filename, 4, 2048);
    }
    if (audiostream == NULL)
    {
        return;
    }
    al_attach_audio_stream_to_mixer(audiostream, audiomixer);
    al_set_audio_stream_playmode(audiostream, ALLEGRO_PLAYMODE_LOOP);
}

void audio_music_stop()
{
    if (audiostream == NULL)
    {
        return;
    }
    al_set_audio_stream_playing(audiostream, false);
    al_detach_audio_stream(audiostream);
    al_destroy_audio_stream(audiostream);
    audiostream = NULL;
}

void audio_music_seek(u32 position)
{
    if (audiostream == NULL)
    {
        return;
    }
}

void audio_update()
{
    
}
