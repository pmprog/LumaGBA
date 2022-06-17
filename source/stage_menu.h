
#pragma once

#include "../engine/engine.h"

void mainmenu_start();
void mainmenu_finish();
void mainmenu_update();

static const StageRecord mainmenu_stage = { mainmenu_start, mainmenu_update, mainmenu_finish };
