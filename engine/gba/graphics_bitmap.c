
#include "gba.h"

void graphics_bitmap_setpixel(s16 X, s16 Y, u8 PaletteIndex )
{
    if( X < 0 || X >= 240 || Y < 0 || Y >= 160)
    {
        return;
    }
    u16* ptr = (u16*)&vid_page[ ( (Y * 240) + X) >> 1 ];  // Division by 2 due to s16/u16 pos16er mismatch!
    if( X & 1 )
    {
        *ptr = (*ptr & 0x00FF) | (PaletteIndex<<8);    // Right pixel
    }
    else
    {
        *ptr = (*ptr & 0xFF00) | PaletteIndex;        // Left pixel
    }
}

void graphics_bitmap_line_horizontal(s16 X1, s16 Y, s16 X2, u8 PaletteIndex )
{
    // Clamp to screen bounds
    s16 lx = ( X1 < X2 ? X1 : X2 );
    s16 rx = ( X1 > X2 ? X1 : X2 );
    lx = ( lx < 0 ? 0 : lx );
    rx = ( rx >= 240 ? 239 : rx );

    // TODO: Speed this up with double-set-pixel when implemented
    for(s16 x = lx; x <= rx; x++)
    {
        graphics_bitmap_setpixel( x, Y, PaletteIndex );
    }
}

void graphics_bitmap_line(s16 X1, s16 Y1, s16 X2, s16 Y2, u8 PaletteIndex )
{
    if(Y1 == Y2)
    {
        graphics_bitmap_line_horizontal(X1, Y1, X2, PaletteIndex);
        return;
    }
	if( X1 == X2 )
	{
		for(s16 y = (Y1 < Y2 ? Y1 : Y2); y < (Y1 > Y2 ? Y1 : Y2); y++)
		{
			graphics_bitmap_setpixel(X1, y, PaletteIndex);
		}
		return;
	}

	s16 steep = 0;
	if (abs(X2 - X1) < abs(Y2 - Y1))
	{
		s16 t;
		t = X1; X1 = Y1; Y1 = t;
		t = X2; X2 = Y2; Y2 = t;
		steep = 1;
	}
	if (X1 > X2)
	{
		s16 t;
		t = X1; X1 = X2; X2 = t;
		t = Y1; Y1 = Y2; Y2 = t;
	}
	s16 dx = X2 - X1;
	s16 dy = Y2 - Y1;
	s16 derror2 = abs(dy) * 2;
	s16 error2 = 0;
	s16 y = Y1;
	for (s16 x = X1; x <= X2; x++)
	{
		if (steep == 1)
		{
			graphics_bitmap_setpixel(y, x, PaletteIndex);
		}
		else
		{
			graphics_bitmap_setpixel(x, y, PaletteIndex);
		}
		error2 += derror2;
		if (error2 > dx)
		{
			y += (Y2 > Y1 ? 1 : -1);
			error2 -= dx * 2;
		}
	}

}

void graphics_bitmap_rectangle(s16 X, s16 Y, s16 Width, s16 Height, u8 PaletteIndex )
{
    graphics_bitmap_line_horizontal(X, Y, X + Width, PaletteIndex);
    graphics_bitmap_line_horizontal(X, Y + Height, X + Width, PaletteIndex);
    graphics_bitmap_line(X, Y, X, Y + Height, PaletteIndex);
    graphics_bitmap_line(X + Width, Y, X + Width, Y + Height, PaletteIndex);
}

void graphics_bitmap_triangle(s16 X1, s16 Y1, s16 X2, s16 Y2, s16 X3, s16 Y3, u8 PaletteIndex )
{
	graphics_bitmap_line(X1, Y1, X2, Y2, PaletteIndex);
	graphics_bitmap_line(X1, Y1, X3, Y3, PaletteIndex);
	graphics_bitmap_line(X3, Y3, X2, Y2, PaletteIndex);
}

void graphics_bitmap_circle(s16 X, s16 Y, u8 Radius, u8 PaletteIndex )
{
	s16 u = 1, v = 2 * Radius - 1, E = 0;
	s16 x = 0;
	s16 y = Radius;

	while (x < y)
	{
		graphics_bitmap_setpixel(X + x, Y + y, PaletteIndex);
		graphics_bitmap_setpixel(X + x, Y - y, PaletteIndex);
		graphics_bitmap_setpixel(X - x, Y - y, PaletteIndex);
		graphics_bitmap_setpixel(X - x, Y + y, PaletteIndex);
		graphics_bitmap_setpixel(X + y, Y + x, PaletteIndex);
		graphics_bitmap_setpixel(X + y, Y - x, PaletteIndex);
		graphics_bitmap_setpixel(X - y, Y - x, PaletteIndex);
		graphics_bitmap_setpixel(X - y, Y + x, PaletteIndex);
		x++; E += u; u += 2;
		if (v < 2 * E)
		{
			y--;
			E -= v;
			v -= 2;
		}
		if (x > y) break;
		graphics_bitmap_setpixel(X + x, Y + y, PaletteIndex);
		graphics_bitmap_setpixel(X + x, Y - y, PaletteIndex);
		graphics_bitmap_setpixel(X - x, Y - y, PaletteIndex);
		graphics_bitmap_setpixel(X - x, Y + y, PaletteIndex);
		graphics_bitmap_setpixel(X + y, Y + x, PaletteIndex);
		graphics_bitmap_setpixel(X + y, Y - x, PaletteIndex);
		graphics_bitmap_setpixel(X - y, Y - x, PaletteIndex);
		graphics_bitmap_setpixel(X - y, Y + x, PaletteIndex);
	}
}

void graphics_bitmap_polygon(s16* X, s16* Y, s16 PointCount, u8 PaletteIndex)
{
	for (s16 current = 0; current < PointCount; current++)
	{
		s16 next = (current + 1) % PointCount;
		graphics_bitmap_line(X[current], Y[current], X[next], Y[next], PaletteIndex);
	}
}

void graphics_bitmap_blit256(u8* ImageData, u16 ImageWidth, u16 ImageHeight, u16 DestinationX, u16 DestinationY)
{
	for(u16 y = 0; y < ImageHeight; y++)
	{
		s16 ty = DestinationY + y;
		if( ty >= 0 && ty < 160 )
		{
			for(u16 x = 0; x < ImageWidth; x++)
			{
				s16 tx = DestinationX + x;
				if( tx >= 0 && tx < 240 )
				{
					u8 col = ImageData[(y * ImageWidth) + x];
					if(col != 0)
					{
						graphics_bitmap_setpixel(tx, ty, col);
					}
				}
			}
		}
	}
}

void graphics_bitmap_blit256sub(u8* ImageData, u16 ImageWidth, u16 ImageHeight, u16 DestinationX, u16 DestinationY, u16 SourceX, u16 SourceY, u16 SourceWidth, u16 SourceHeight)
{
	for(u16 y = 0; y < SourceHeight; y++)
	{
		s16 ty = DestinationY + y;
		if( ty >= 0 && ty < 160 )
		{
			for(u16 x = 0; x < SourceWidth; x++)
			{
				s16 tx = DestinationX + x;
				if( tx >= 0 && tx < 240 )
				{
					u8 col = ImageData[((SourceY + y) * ImageWidth) + SourceX + x];
					if(col != 0)
					{
						graphics_bitmap_setpixel(tx, ty, col);
					}
				}
			}
		}
	}
}

