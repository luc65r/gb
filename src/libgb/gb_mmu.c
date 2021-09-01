#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>

#include "gb_io.h"
#include "gb_mbc.h"
#include "gb_mmu.h"
#include "gb_ppu.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

static uint8_t gb_ram_read8(GbMmu *mmu, uint16_t addr) {
    return 0;
}

static uint16_t gb_ram_read16(GbMmu *mmu, uint16_t addr) {
    return 0;
}

static void gb_ram_write8(GbMmu *mmu, uint16_t addr, uint8_t value) {
}

static void gb_ram_write16(GbMmu *mmu, uint16_t addr, uint16_t value) {
}

static uint8_t gb_hram_read8(GbMmu *mmu, uint16_t addr) {
    return 0;
}

static uint16_t gb_hram_read16(GbMmu *mmu, uint16_t addr) {
    return 0;
}

static void gb_hram_write8(GbMmu *mmu, uint16_t addr, uint8_t value) {
}

static void gb_hram_write16(GbMmu *mmu, uint16_t addr, uint16_t value) {
}

static uint8_t gb_prohibited_read8(GbMmu *mmu, uint16_t addr) {
    return 0;
}

static uint16_t gb_prohibited_read16(GbMmu *mmu, uint16_t addr) {
    return 0;
}

static void gb_prohibited_write8(GbMmu *mmu, uint16_t addr, uint8_t value) {
}

static void gb_prohibited_write16(GbMmu *mmu, uint16_t addr, uint16_t value) {
}

static uint8_t gb_ie_read8(GbMmu *mmu, uint16_t addr) {
    return 0;
}

static uint16_t gb_ie_read16(GbMmu *mmu, uint16_t addr) {
    return 0;
}

static void gb_ie_write8(GbMmu *mmu, uint16_t addr, uint8_t value) {
}

static void gb_ie_write16(GbMmu *mmu, uint16_t addr, uint16_t value) {
}

#pragma GCC diagnostic pop

#define REDIRECT_READ(size)                                         \
    uint##size##_t gb_mmu_read##size(GbMmu *mmu, uint16_t addr) {   \
        assert(mmu != NULL);                                        \
        if (addr < 0x8000) /* ROM bank */                           \
            return gb_mbc_read##size(mmu->mbc, addr);               \
        if (addr < 0xa000) /* Video RAM */                          \
            return gb_ppu_read##size(mmu->ppu, addr);               \
        if (addr < 0xc000) /* External RAM */                       \
            return gb_mbc_read##size(mmu->mbc, addr);               \
        if (addr < 0xfe00) /* RAM */                                \
            return gb_ram_read##size(mmu, addr);                    \
        if (addr < 0xfea0) /* Sprite attribute table */             \
            return gb_ppu_read##size(mmu->ppu, addr);               \
        if (addr < 0xff00) /* Prohibited */                         \
            return gb_prohibited_read##size(mmu, addr);             \
        if (addr < 0xff80) /* I/O registers */                      \
            return gb_io_read##size(mmu->io, addr);                 \
        if (addr < 0xffff) /* High RAM */                           \
            return gb_hram_read##size(mmu, addr);                   \
        /* Interrupt enable register */                             \
        return gb_ie_read##size(mmu, addr);                         \
    }

#define REDIRECT_WRITE(size)                                            \
    void gb_mmu_write##size(GbMmu *mmu, uint16_t addr, uint##size##_t value) { \
        assert(mmu != NULL);                                            \
        if (addr < 0x8000) { /* ROM bank */                             \
            gb_mbc_write##size(mmu->mbc, addr, value);                  \
        } else if (addr < 0xa000) { /* Video RAM */                     \
            gb_ppu_write##size(mmu->ppu, addr, value);                  \
        } else if (addr < 0xc000) { /* External RAM */                  \
            gb_mbc_write##size(mmu->mbc, addr, value);                  \
        } else if (addr < 0xfe00) { /* RAM */                           \
            gb_ram_write##size(mmu, addr, value);                       \
        } else if (addr < 0xfea0) { /* Sprite attribute table */        \
            gb_ppu_write##size(mmu->ppu, addr, value);                  \
        } else if (addr < 0xff00) { /* Prohibited */                    \
            gb_prohibited_write##size(mmu, addr, value);                \
        } else if (addr < 0xff80) { /* I/O registers */                 \
            gb_io_write##size(mmu->io, addr, value);                    \
        } else if (addr < 0xffff) { /* High RAM */                      \
            gb_hram_write##size(mmu, addr, value);                      \
        } else { /* Interrupt enable register */                        \
            gb_ie_write##size(mmu, addr, value);                        \
        }                                                               \
    }

REDIRECT_READ(8)
REDIRECT_READ(16)
REDIRECT_WRITE(8)
REDIRECT_WRITE(16)
