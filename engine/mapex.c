
#include "mapex.h"

static MapExConfiguration planemaps[4];  // Engine only supports up to 4 planes

static const u32 mapex_submasks[] = { 0x00, 0x01, 0x03 };
static const u8 mapex_subadvance[] = { 0x00, 0x02, 0x04 };
static const u8 mapex_subtiles[] = { 0x01, 0x04, 0x10 };

void mapex_fillrow(u8 Plane, u8 RenderRow, u16 MapRow, u8 MapSubRow);
void mapex_fillcol(u8 Plane, u8 RenderCol, u16 MapCol, u8 MapSubCol);

static void mapex_reversetile(u8 Plane, u32* Tile, u32* SubTile, int MaxTile)
{
    u32 t = *Tile;
    u32 st = *SubTile;
    if (st == 0)
    {
        t = ((t + MaxTile - 1) % MaxTile);
        st = mapex_submasks[planemaps[Plane].MapTileSize];
    }
    else
    {
        st--;
    }
    *Tile = t;
    *SubTile = st;
}

static void mapex_advancetile(u8 Plane, u32* Tile, u32* SubTile, int MaxTile)
{
    u32 t = *Tile;
    u32 st = *SubTile;
    st = ((st + 1) & mapex_submasks[planemaps[Plane].MapTileSize]);
    if (st == 0)
    {
        t = ((t + 1) % MaxTile);
    }
    *Tile = t;
    *SubTile = st;
}

void mapex_configure(u8 Plane, u16 MapWidth, u16 MapHeight, u8 MapTileSize, const u16* MapData)
{
    planemaps[Plane].MapWidth = MapWidth;
    planemaps[Plane].MapHeight = MapHeight;
    planemaps[Plane].MapTileSize = MapTileSize;
    planemaps[Plane].MapData = MapData;
    planemaps[Plane].MapWidthPixels = (u32)MapWidth << (3 + MapTileSize);
    planemaps[Plane].MapHeightPixels = (u32)MapHeight << (3 + MapTileSize);
    mapex_setviewport(Plane, 0, 0);
}

void mapex_setviewport(u8 Plane, u32 CameraX, u32 CameraY)
{
    // ViewXY points to the camera pixel position
    planemaps[Plane].ViewX = CameraX % planemaps[Plane].MapWidthPixels;
    planemaps[Plane].ViewY = CameraY % planemaps[Plane].MapHeightPixels;
    // PlaneXY as the scroll position
    planemaps[Plane].PlaneX = (u8)(CameraX & 0x00FF);
    planemaps[Plane].PlaneY = (u8)(CameraY & 0x00FF);

    u8 currentcol_render = planemaps[Plane].PlaneX >> 3;
    currentcol_render = (currentcol_render == 0 ? 31 : currentcol_render - 1);
    u32 currentcol_map = planemaps[Plane].ViewX >> (3 + planemaps[Plane].MapTileSize);
    u32 currentcol_mapsub = (planemaps[Plane].ViewX >> 3) & mapex_submasks[planemaps[Plane].MapTileSize];
    mapex_reversetile(Plane, &currentcol_map, &currentcol_mapsub, planemaps[Plane].MapWidth);
    for (u8 x = 0; x < 32; x++)
    {
        planemaps[Plane].PlaneColumnTile[currentcol_render] = currentcol_map;
        planemaps[Plane].PlaneColumnSubTile[currentcol_render] = currentcol_mapsub;
        currentcol_render = (u8)((currentcol_render + 1) % 32);
        mapex_advancetile(Plane, &currentcol_map, &currentcol_mapsub, planemaps[Plane].MapWidth);
    }

    // Subtracting a row first rotates through the u8 to start at the bottom row
    u8 currentrow_render = planemaps[Plane].PlaneY >> 3;
    currentrow_render = (currentrow_render == 0 ? 31 : currentrow_render - 1);
    u32 currentrow_map = planemaps[Plane].ViewY >> (3 + planemaps[Plane].MapTileSize);
    u32 currentrow_mapsub = (planemaps[Plane].ViewY >> 3) & mapex_submasks[planemaps[Plane].MapTileSize];
    mapex_reversetile(Plane, &currentrow_map, &currentrow_mapsub, planemaps[Plane].MapHeight);


    for (u8 y = 0; y < 32; y++)
    {
        mapex_fillrow(Plane, currentrow_render, currentrow_map, currentrow_mapsub);
        currentrow_render = ((currentrow_render + 1) % 32);
        mapex_advancetile(Plane, &currentrow_map, &currentrow_mapsub, planemaps[Plane].MapHeight);
    }
    graphics_tilemap_tilemap_setposition(Plane, planemaps[Plane].PlaneX, planemaps[Plane].PlaneY);
}

void mapex_scrollviewport(u8 Plane, s32 DeltaX, s32 DeltaY)
{
    if (abs(DeltaX) > 240 || abs(DeltaY) > 160)
    {
        s32 newx = ((s32)planemaps[Plane].ViewX + DeltaX);
        if (newx < 0) { newx += planemaps[Plane].MapWidthPixels; }
        newx = newx % planemaps[Plane].MapWidthPixels;
        s32 newy = ((s32)planemaps[Plane].ViewY + DeltaY);
        if (newy < 0) { newy += planemaps[Plane].MapHeightPixels; }
        newy = newy % planemaps[Plane].MapHeightPixels;
        mapex_setviewport(Plane, (u32)newx, (u32)newy);
        return;
    }

    if (DeltaY != 0)
    {
        u8 row_current = ((planemaps[Plane].PlaneY + (DeltaY < 0 ? 0 : 160)) >> 3) % 32;
        s32 plane_target = (s32)planemaps[Plane].PlaneY + (DeltaY < 0 ? 0 : 160) + DeltaY;
        if (plane_target < 0) { plane_target += 256; }
        u8 row_target = (u8)(plane_target >> 3) % 32;

        u32 row_map = planemaps[Plane].PlaneRowTile[row_current];
        u32 row_mapsub = planemaps[Plane].PlaneRowSubTile[row_current];
        if (DeltaY < 0)
        {
            // Cycle backwards to fill in the new rows
            while(row_current != row_target)
            {
                row_current = (row_current + 31) % 32;
                mapex_reversetile(Plane, &row_map, &row_mapsub, planemaps[Plane].MapHeight);
                mapex_fillrow(Plane, row_current, row_map, row_mapsub);
            }
        }
        else
        {
            // Cycle forwards to fill in the new rows
            while(row_current != row_target)
            {
                row_current = (row_current + 1) % 32;
                mapex_advancetile(Plane, &row_map, &row_mapsub, planemaps[Plane].MapHeight);
                mapex_fillrow(Plane, row_current, row_map, row_mapsub);
            }
        }
        planemaps[Plane].PlaneY = (u8)plane_target - (DeltaY < 0 ? 0 : 160);
        graphics_tilemap_tilemap_setposition(Plane, planemaps[Plane].PlaneX, planemaps[Plane].PlaneY);
    }

    if (DeltaX != 0)
    {
        u8 col_current = ((planemaps[Plane].PlaneX + (DeltaX < 0 ? 0 : 240)) >> 3) % 32;
        s32 plane_target = (s32)planemaps[Plane].PlaneX + (DeltaX < 0 ? 0 : 240) + DeltaX;
        if (plane_target < 0) { plane_target += 256; }
        u8 col_target = (u8)(plane_target >> 3) % 32;

        u32 col_map = planemaps[Plane].PlaneColumnTile[col_current];
        u32 col_mapsub = planemaps[Plane].PlaneColumnSubTile[col_current];
        if (DeltaX < 0)
        {
            // CXcle backwards to fill in the new cols
            while(col_current != col_target)
            {
                col_current = (col_current + 31) % 32;
                mapex_reversetile(Plane, &col_map, &col_mapsub, planemaps[Plane].MapHeight);
                mapex_fillcol(Plane, col_current, col_map, col_mapsub);
            }
        }
        else
        {
            // CXcle forwards to fill in the new cols
            while(col_current != col_target)
            {
                col_current = (col_current + 1) % 32;
                mapex_advancetile(Plane, &col_map, &col_mapsub, planemaps[Plane].MapHeight);
                mapex_fillcol(Plane, col_current, col_map, col_mapsub);
            }
        }
        planemaps[Plane].PlaneX = (u8)plane_target - (DeltaX < 0 ? 0 : 240);
        graphics_tilemap_tilemap_setposition(Plane, planemaps[Plane].PlaneX, planemaps[Plane].PlaneY);
    }

}

void mapex_fillrow(u8 Plane, u8 RenderRow, u16 MapRow, u8 MapSubRow)
{
    planemaps[Plane].PlaneRowTile[RenderRow] = MapRow;
    planemaps[Plane].PlaneRowSubTile[RenderRow] = MapSubRow;

    for (u8 x = 0; x < 32; x++)
    {
        u32 tileoffset = ((MapRow * planemaps[Plane].MapWidth) + planemaps[Plane].PlaneColumnTile[x]);
        u16 tileindex = planemaps[Plane].MapData[tileoffset] * mapex_subtiles[planemaps[Plane].MapTileSize];
        tileindex += (mapex_subadvance[planemaps[Plane].MapTileSize] * MapSubRow) + planemaps[Plane].PlaneColumnSubTile[x];
        graphics_tilemap_tilemap_settile(Plane, x, RenderRow, tileindex);
    }
}

void mapex_fillcol(u8 Plane, u8 RenderCol, u16 MapCol, u8 MapSubCol)
{
    planemaps[Plane].PlaneColumnTile[RenderCol] = MapCol;
    planemaps[Plane].PlaneColumnSubTile[RenderCol] = MapSubCol;

    for (u8 x = 0; x < 32; x++)
    {
        u32 tileoffset = ((planemaps[Plane].PlaneRowTile[x] * planemaps[Plane].MapWidth) + MapCol);
        u16 tileindex = planemaps[Plane].MapData[tileoffset] * mapex_subtiles[planemaps[Plane].MapTileSize];
        tileindex += (mapex_subadvance[planemaps[Plane].MapTileSize] * planemaps[Plane].PlaneRowSubTile[x]) + MapSubCol;
        graphics_tilemap_tilemap_settile(Plane, RenderCol, x, tileindex);
    }
}

void mapex_currentview(u8 Plane, u32* ViewX, u32* ViewY)
{
    ViewX[0] = planemaps[Plane].ViewX;
    ViewY[0] = planemaps[Plane].ViewY;
}
