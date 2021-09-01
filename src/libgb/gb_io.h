#ifndef GB_IO_H
#define GB_IO_H

#include <inttypes.h>
#include <stdbool.h>

enum GbButtonsSelect {
    GB_BUTTONS_ACTION,
    GB_BUTTONS_DIRECTION,
};

typedef struct {
    bool right, left, up, down;
    bool a, b;
    bool select, start;
} GbJoypad;

typedef struct {
    GbJoypad joypad;
    enum GbButtonsSelect select;
} GbIo;

uint8_t gb_io_read8(GbIo *io, uint16_t addr);
uint16_t gb_io_read16(GbIo *io, uint16_t addr);

void gb_io_write8(GbIo *io, uint16_t addr, uint8_t value);
void gb_io_write16(GbIo *io, uint16_t addr, uint16_t value);

#endif
