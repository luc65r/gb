#ifndef GB_MBC_H
#define GB_MBC_H

#include <inttypes.h>

typedef struct {
    int a;
} GbMbc;

uint8_t gb_mbc_read8(GbMbc *mbc, uint16_t addr);
uint16_t gb_mbc_read16(GbMbc *mbc, uint16_t addr);

void gb_mbc_write8(GbMbc *mbc, uint16_t addr, uint8_t value);
void gb_mbc_write16(GbMbc *mbc, uint16_t addr, uint16_t value);

#endif
