
#pragma once

#include "../engine/engine.h"

extern u16 tutorial_level;
extern u8 tutorial_step;

u8 tutorial_doeslevelhavetutorial(u16 level);

void tutorial_start();
void tutorial_finish();
void tutorial_update();

static const StageRecord tutorial_stage = { tutorial_start, tutorial_update, tutorial_finish };
