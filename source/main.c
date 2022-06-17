
#include "../engine/engine.h"
#include "../resources/luma_font.h"
#include "stage_pmprog.h"

const Colour lumapalette[] = {
 { 0, 0, 0 }, //{ 255, 0, 255 },
{16, 77, 27},
{28, 166, 49},
{24, 134, 41},
{42, 54, 177},
{175, 191, 255},
{69, 94, 222},
{128, 7, 7},
{238, 98, 84},
{255, 21, 0},
{245, 127, 23},
{249, 168, 37},
{255, 235, 59},
{253, 216, 53},
{67, 144, 204},
{7, 7, 7},
{243, 108, 96},
{251, 192, 45},
{255, 238, 88},
{255, 241, 118},
{255, 247, 156},
{255, 255, 255},
{232, 78, 64},
{86, 119, 252},
{78, 108, 239},
{0, 2, 255},
{82, 75, 58},
{154, 154, 154},
{15, 68, 25},
{145, 167, 255},
{208, 208, 208},
{36, 36, 36},
{57, 49, 49},
{80, 51, 50},
{81, 81, 81},
{101, 53, 53},
{102, 82, 82},
{120, 120, 120},
{145, 145, 145},
{21, 21, 21},
{47, 47, 47},
{24, 63, 133},
{93, 143, 229},
{50, 112, 221},
{22, 56, 117},
{31, 88, 191},
{243, 243, 243},
{198, 198, 198},
{21, 108, 35},
{218, 50, 45},
{154, 65, 59},
{59, 80, 206},
{115, 143, 254},
{43, 38, 29},
{59, 49, 28},
{212, 212, 212},
{134, 134, 134},
{60, 60, 60},
{29, 29, 29},
{14, 14, 14},
{187, 187, 187},
{180, 180, 180},
{146, 132, 98},
{162, 141, 90},
{96, 96, 96},
{70, 70, 70},
{74, 74, 74},
{104, 73, 27},
{48, 48, 48},
{110, 110, 110},
{255, 239, 148},
{255, 231, 140},
{255, 222, 127},
{255, 214, 123},
{255, 202, 107},
{255, 189, 90},
{255, 181, 82},
{255, 165, 66},
{250, 156, 53},
{247, 142, 38},
{169, 169, 169},
{88, 88, 88},
{138, 138, 138},
{116, 116, 116},
{255, 231, 132},
{223, 223, 223},
{201, 201, 201},
{136, 122, 88},
{133, 102, 46},
{166, 166, 166},
{132, 118, 84},
{182, 158, 98},
{43, 40, 31},
{76, 45, 9},
{142, 125, 82},
{167, 143, 84},
{150, 149, 115},
{254, 223, 146},
{207, 182, 123},
{148, 127, 76},
{160, 143, 100},
{255, 214, 115},
{255, 173, 70},
{255, 181, 74},
{79, 24, 130},
{135, 62, 203},
{177, 97, 251},

};

int main(void)
{
	platform_init();

	graphics_palette_set( (Colour*)lumapalette, 0, 107 );
	graphics_mode_tilemap( 3, COLOURS_8BPP );	// Single plane
	graphics_sprites_clear();

    for(int y = 0; y < 20; y++)
    {
        for(int x = 0; x < 30; x++)
        {
            graphics_tilemap_tilemap_settile(0, x, y, 0);
            graphics_tilemap_tilemap_settile(1, x, y, 0);
            graphics_tilemap_tilemap_settile(2, x, y, 0);
        }
    }


	// Use code as a test character set
	graphics_tilemap_characterset_set((u8*)luma_font, 0, 493, COLOURS_8BPP);
	graphics_sprites_characterset_set((u8*)luma_font, 0, 493, COLOURS_8BPP);

    random_init( 44 );

	// Execute
	engine_execute((StageRecord *)&pmprog_stage);

	audio_music_stop();
	platform_shutdown();
}
