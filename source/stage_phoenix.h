
#pragma once

#include "../engine/engine.h"

void phoenix_start();
void phoenix_finish();
void phoenix_update();

static const StageRecord phoenix_stage = { phoenix_start, phoenix_update, phoenix_finish };
