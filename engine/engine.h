
#pragma once

#include "platform.h"
#include "maths.h"
#include "mapex.h"

#define EVENT_QUEUE_LENGTH    10

extern StageRecord* engine_stage_active;
extern u16 engine_stage_time;           // 16 bit counter on how many frames the stage has been running

// Start the game engine, and go into the BootStage
void engine_execute(StageRecord* BootStage);
// Change the current stage
void engine_changestage(StageRecord* Next);

// Returns 0xFF if did not get added to queue
u8 engine_queueevent(u8 FrameDelay, EventCallback CallbackFunction, void* Data, EventFlags Flags);
// Process event queue (this is called internally, so you don't need to)
void engine_eventupdate();
