#ifndef GB_MMU_H
#define GB_MMU_H

#include <inttypes.h>

#include "gb_io.h"
#include "gb_mbc.h"
#include "gb_ppu.h"

typedef struct {
    GbMbc *mbc;
    GbPpu *ppu;
    GbIo *io;
    uint8_t ram[8 * 1024];
    uint8_t hram[127];
    uint8_t ie;
} GbMmu;

uint8_t gb_mmu_read8(GbMmu *mmu, uint16_t addr);
uint16_t gb_mmu_read16(GbMmu *mmu, uint16_t addr);

void gb_mmu_write8(GbMmu *mmu, uint16_t addr, uint8_t value);
void gb_mmu_write16(GbMmu *mmu, uint16_t addr, uint16_t value);

#endif
