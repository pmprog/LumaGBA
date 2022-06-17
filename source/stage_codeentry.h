
#pragma once

#include "../engine/engine.h"

void codeentry_start();
void codeentry_finish();
void codeentry_update();

static const StageRecord codeentry_stage = { codeentry_start, codeentry_update, codeentry_finish };

