
#include "gba.h"

void platform_init()
{
	irq_init(NULL);
	irq_set(II_VBLANK, mmVBlank, ISR_DEF);
	irq_enable(II_VBLANK);
	mmInitDefault( (mm_addr)soundbank_bin, 8 );
	oam_init(OAM, 128);
}

void platform_update()
{
    
}

void platform_shutdown()
{

}

u8 platform_updateframes()
{
	return 1;
}

void platform_logtext(const char* message)
{

}

IWRAM_CODE
static void sram_memcpy(vu8 *dst, const vu8 *src, size_t size)
{
    for(size_t s = size; s > 0; s--)
    {
        *dst++ = *src++;
    }
}

void savegame_read(void* Buffer, u16 BufferLength)
{
	sram_memcpy(Buffer, MEM_SRAM, BufferLength);
}

void savegame_write(void* Buffer, u16 BufferLength)
{
	sram_memcpy(MEM_SRAM, Buffer, BufferLength);
}
