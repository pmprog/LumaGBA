
#pragma once

#include "platform.h"

typedef struct randomconfig
{
    vu8 a;
    vu8 b;
    vu8 c;
    vu8 d;
} randomconfig;
extern randomconfig randomsource;

// Fixed Point (8.8) maths in s16
int sini(int degrees);
int cosi(int degrees);

// Random Number generation
void random_init( u8 seed );
u8 random_next();
