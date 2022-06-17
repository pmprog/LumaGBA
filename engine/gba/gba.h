
#pragma once

#include "../typedefs.h"
#include <tonc.h>
#include <stdio.h>
#include <stdlib.h>
#include <maxmod.h>

#include "soundbank.h"
#include "soundbank_bin.h"

#include "../platform.h"

#define RGB8macro(r,g,b)        ( ((r)>>3) | (((g)>>3)<<5) | (((b)>>3)<<10) )
#define MAP_BASE_ADR(m)         (void*)(se_mem[m])
#define OAM                     ((OBJ_ATTR*)MEM_OAM)
#define MEM_OVRAM               ((u16*)MEM_VRAM_OBJ)