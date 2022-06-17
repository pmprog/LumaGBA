
#pragma once

#include "../engine/engine.h"

void pmprog_start();
void pmprog_finish();
void pmprog_update();

static const StageRecord pmprog_stage = { pmprog_start, pmprog_update, pmprog_finish };
