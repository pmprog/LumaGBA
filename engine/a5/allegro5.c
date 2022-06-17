
#include "allegro5.h"
#include "../platform.h"
#include "../engine.h"
#include <stdio.h>

ALLEGRO_EVENT_QUEUE* eventqueue;
ALLEGRO_DISPLAY* screen = NULL;
ALLEGRO_BITMAP* canvas_internal;
ALLEGRO_LOCKED_REGION* bufferlock;
int screen_bestscale;
char* game_name;
int video_width;
int video_height;
ALLEGRO_TIMER* update_timer;
ALLEGRO_MUTEX* update_mutex;
u8 update_required = 0;

void platform_initdisplay();

void platform_init()
{
	al_init();
	al_install_keyboard();
	al_install_joystick();
	al_install_audio();
	al_init_acodec_addon();
	al_init_primitives_addon();
	al_init_image_addon();

	eventqueue = al_create_event_queue();
	al_register_event_source(eventqueue, al_get_keyboard_event_source());
	al_register_event_source(eventqueue, al_get_joystick_event_source());

	al_reserve_samples(20);
	audiovoice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	if (audiovoice != NULL)
	{
		audiomixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
		if(audiomixer == NULL)
		{
			al_destroy_voice(audiovoice);
			audiovoice = NULL;
		}
		else
		{
			if (!al_attach_mixer_to_voice(audiomixer, audiovoice))
			{
				al_destroy_mixer(audiomixer);
				audiomixer = NULL;
				al_destroy_voice(audiovoice);
				audiovoice = NULL;
			}
		}
	}

	platform_initdisplay();

	update_mutex = al_create_mutex();

	update_timer = al_create_timer(1.0 / 60.0);
	al_register_event_source( eventqueue, al_get_timer_event_source(update_timer));
	al_start_timer(update_timer);

}

void platform_update()
{
	ALLEGRO_EVENT ae;

	while (al_get_next_event(eventqueue, &ae))
	{
		switch (ae.type)
		{
		case ALLEGRO_EVENT_TIMER:
			if( ae.timer.source == update_timer )
			{
				al_lock_mutex(update_mutex);
				update_required++;
				al_unlock_mutex(update_mutex);
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			engine_changestage(NULL);
			return;
			break;
		default:
			break;
		}
	}
}

u8 platform_updateframes()
{
	al_lock_mutex(update_mutex);
	u8 retval = update_required;
	update_required = 0;
	al_unlock_mutex(update_mutex);
	return retval;
}

void platform_shutdown()
{
	al_stop_timer(update_timer);
	al_unregister_event_source(eventqueue, al_get_timer_event_source(update_timer));
	al_destroy_timer(update_timer);
	al_destroy_mutex(update_mutex);

	if (audiovoice != NULL)
	{
		al_detach_voice(audiovoice);
		al_destroy_mixer(audiomixer);
		audiomixer = NULL;
		al_destroy_voice(audiovoice);
		audiovoice = NULL;
	}
	al_destroy_bitmap(canvas_internal);
	al_unregister_event_source(eventqueue, al_get_display_event_source(screen));
	al_destroy_display(screen);

	al_destroy_event_queue(eventqueue);

	al_uninstall_audio();
	al_uninstall_joystick();
	al_uninstall_keyboard();
	al_uninstall_system();
}

void platform_initdisplay()
{
	int monitorw;
	int monitorh;
	ALLEGRO_MONITOR_INFO moninfo;
	if (al_get_monitor_info(0, &moninfo))
	{
		monitorw = moninfo.x2 - moninfo.x1;
		monitorh = moninfo.y2 - moninfo.y1;
	}
	screen_bestscale = 1;
	while (240 * screen_bestscale < monitorw && 160 * screen_bestscale < monitorh)
	{
		screen_bestscale++;
	}

	screen_bestscale--;
	video_width = 240 * screen_bestscale;
	video_height = 160 * screen_bestscale;

	screen = al_create_display(video_width, video_height);
	al_set_window_title(screen, "JamFox");
	al_register_event_source(eventqueue, al_get_display_event_source(screen));
	canvas_internal = al_create_bitmap(240, 160);
	for(int i = 0; i < 4; i++)
	{
		canvas_planes[i] = NULL;
		plane_scrollx[i] = 0;
		plane_scrolly[i] = 0;
	}
}

void platform_logtext(const char* message)
{
	printf(message);
	printf("\n");
}

void savegame_read(void* Buffer, u16 BufferLength)
{
	ALLEGRO_FILE* f = al_fopen("savegame.dat", "rb");
	if (f == NULL)
	{
		memset(Buffer, 0, BufferLength);
	}
	else
	{
		al_fread(f, Buffer, BufferLength);
		al_fclose(f);
	}
}

void savegame_write(void* Buffer, u16 BufferLength)
{
	ALLEGRO_FILE* f = al_fopen("savegame.dat", "wb");
	al_fwrite(f, Buffer, BufferLength);
	al_fclose(f);
}
