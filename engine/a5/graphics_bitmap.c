
#include "allegro5.h"

void graphics_bitmap_setpixel(s16 X, s16 Y, u8 PaletteIndex)
{
	char* p = (char*)bufferlock->data;
	int b = (bufferlock->pitch * Y) + (bufferlock->pixel_size * X);
	p[b + 0] = canvas_palette[PaletteIndex].R;
	p[b + 1] = canvas_palette[PaletteIndex].G;
	p[b + 2] = canvas_palette[PaletteIndex].B;
	p[b + 3] = (PaletteIndex == 0 ? 0 : 255);
}

void graphics_bitmap_line_horizontal(s16 X1, s16 Y, s16 X2, u8 PaletteIndex)
{
	// Clamp to screen bounds
	s16 lx = (X1 < X2 ? X1 : X2);
	s16 rx = (X1 > X2 ? X1 : X2);
	lx = (lx < 0 ? 0 : lx);
	rx = (rx >= 240 ? 239 : rx);

	// TODO: Speed this up with double-set-pixel when implemented
	for (s16 x = lx; x <= rx; x++)
	{
		graphics_bitmap_setpixel(x, Y, PaletteIndex);
	}
}

void graphics_bitmap_line(s16 X1, s16 Y1, s16 X2, s16 Y2, u8 PaletteIndex)
{
	if (Y1 == Y2)
	{
		graphics_bitmap_line_horizontal(X1, Y1, X2, PaletteIndex);
		return;
	}
	if (X1 == X2)
	{
		for (s16 y = (Y1 < Y2 ? Y1 : Y2); y < (Y1 > Y2 ? Y1 : Y2); y++)
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

void graphics_bitmap_rectangle(s16 X, s16 Y, s16 Width, s16 Height, u8 PaletteIndex)
{
	graphics_bitmap_line_horizontal(X, Y, X + Width, PaletteIndex);
	graphics_bitmap_line_horizontal(X, Y + Height, X + Width, PaletteIndex);
	graphics_bitmap_line(X, Y, X, Y + Height, PaletteIndex);
	graphics_bitmap_line(X + Width, Y, X + Width, Y + Height, PaletteIndex);
}

void graphics_bitmap_triangle(s16 X1, s16 Y1, s16 X2, s16 Y2, s16 X3, s16 Y3, u8 PaletteIndex)
{
	graphics_bitmap_line(X1, Y1, X2, Y2, PaletteIndex);
	graphics_bitmap_line(X1, Y1, X3, Y3, PaletteIndex);
	graphics_bitmap_line(X3, Y3, X2, Y2, PaletteIndex);
}

void graphics_bitmap_circle(s16 X, s16 Y, u8 Radius, u8 PaletteIndex)
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