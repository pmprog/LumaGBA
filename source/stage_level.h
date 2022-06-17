
#pragma once

#include "../engine/engine.h"

void level_start();
void level_finish();
void level_update();

void level_rollbacklaser(u8 MapX, u8 MapY, u8 Direction);
void level_resetlevel();

static const StageRecord level_stage = { level_start, level_update, level_finish };
