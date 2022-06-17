
#pragma once

#include "../engine/engine.h"

void gamecomplete_start();
void gamecomplete_finish();
void gamecomplete_update();

static const StageRecord gamecomplete_stage = { gamecomplete_start, gamecomplete_update, gamecomplete_finish };

