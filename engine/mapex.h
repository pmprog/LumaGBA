
#pragma once

#include "platform.h"

typedef struct MapExConfiguration
{
    u16 MapWidth;
    u16 MapHeight;
    u8  MapTileSize;             // 0 = 8x8, 1 = 16x16, 2 = 32x32?
    const u16* MapData;         // Array[height * width]; Left to Right, Top to Bottom

    u32 MapWidthPixels;
    u32 MapHeightPixels;

    u8  PlaneX;                  // Plane X/Y scroll (pixels)
    u8  PlaneY;
    u32 PlaneRowTile[32];
    u8  PlaneRowSubTile[32];
    u32 PlaneColumnTile[32];
    u8  PlaneColumnSubTile[32];
    u32 ViewX;                  // View offset (pixels)
    u32 ViewY;

} MapExConfiguration;

// Configure a larger map to be rendered within one of the planes
void mapex_configure(u8 Plane, u16 MapWidth, u16 MapHeight, u8 MapTileSize, const u16* MapData);

// Force a full redraw of a plane's map at a new position
void mapex_setviewport(u8 Plane, u32 CameraX, u32 CameraY);

// Scroll a plane's map by an X/Y amount. Anything greater than 8 pixel shift will cause a full screen redraw
void mapex_scrollviewport(u8 Plane, s32 DeltaX, s32 DeltaY);

void mapex_currentview(u8 Plane, u32* ViewX, u32* ViewY);
