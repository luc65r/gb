#ifndef GB_H
#define GB_H

#include "gb_cpu.h"
#include "gb_mmu.h"
#include "gb_mbc.h"
#include "gb_ppu.h"

typedef struct {
    GbCpu cpu;
    GbMmu mmu;
    GbMbc mbc;
    GbPpu ppu;
} Gb;

Gb *gb_init(void);

#endif
