#ifndef GB_PPU_H
#define GB_PPU_H

#include <inttypes.h>

typedef struct {
    uint8_t vram[8 * 1024];
    uint8_t oam[160];
} GbPpu;

uint8_t gb_ppu_read8(GbPpu *ppu, uint16_t addr);
uint16_t gb_ppu_read16(GbPpu *ppu, uint16_t addr);

void gb_ppu_write8(GbPpu *ppu, uint16_t addr, uint8_t value);
void gb_ppu_write16(GbPpu *ppu, uint16_t addr, uint16_t value);

#endif
