
#include "engine.h"

StageRecord* engine_stage_active = NULL;
u16 engine_stage_time = 0;

static EventRecord engine_event_queue[EVENT_QUEUE_LENGTH];


void engine_execute(StageRecord* BootStage)
{
    u8 shutdown = 0;

	for(int i = 0; i < EVENT_QUEUE_LENGTH; i++)
	{
		engine_event_queue[i].Callback = NULL;
		engine_event_queue[i].Argument = NULL;
	}

    engine_changestage(BootStage);

	while( shutdown == 0 )
	{
		platform_update();
		engine_eventupdate();
		if(engine_stage_active == NULL)
		{
			shutdown = 1;
		} else {
			u8 upd = platform_updateframes();
			while(upd > 0)
			{
				input_update();
				engine_stage_active->Update();
				upd--;
				engine_stage_time++;
			}
		}
		audio_update();
		graphics_flip();
	}
}

void engine_changestage(StageRecord* Next)
{
	if(engine_stage_active != NULL)
	{
		engine_stage_active->Finish();
	}
    engine_stage_time = 0;
	engine_stage_active = Next;
	if(engine_stage_active != NULL)
	{
		engine_stage_active->Start();
	}
}

u8 engine_queueevent(u8 FrameDelay, EventCallback CallbackFunction, void* Data, EventFlags Flags)
{
	for(int i = 0; i < EVENT_QUEUE_LENGTH; i++)
	{
		// Find empty event
		if( engine_event_queue[i].Callback == NULL )
		{
			engine_event_queue[i].FrameDelay = FrameDelay;
			engine_event_queue[i].Callback = CallbackFunction;
			engine_event_queue[i].Argument = Data;
			engine_event_queue[i].Flags = Flags;
			return i;
		}
	}
	platform_logtext("Queue Full");
	return 0xFF;
}

void engine_eventupdate()
{
	// Process event queue
	for(int i = 0; i < EVENT_QUEUE_LENGTH; i++)
	{
		if( engine_event_queue[i].Callback != NULL )
		{
			if( engine_event_queue[i].FrameDelay == 0 || (engine_event_queue[i].Flags & FLAGS_EXECUTE_EACH_FRAME) == FLAGS_EXECUTE_EACH_FRAME )
			{
				engine_event_queue[i].Callback(engine_event_queue[i].Argument);
				if( engine_event_queue[i].FrameDelay == 0 )
				{
					engine_event_queue[i].Callback = NULL;
					engine_event_queue[i].Argument = NULL;
				}
				else
				{
					engine_event_queue[i].FrameDelay--;
				}
			}
			else
			{
				engine_event_queue[i].FrameDelay--;
			}
		}
	}
}
