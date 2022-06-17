
#pragma once

#include "../engine/engine.h"

void levelcomplete_start();
void levelcomplete_finish();
void levelcomplete_update();

static const StageRecord levelcomplete_stage = { levelcomplete_start, levelcomplete_update, levelcomplete_finish };

// For determining if we've successfully passed the level, or failed miserably
extern u8 target_count;
extern u8 target_hit;
