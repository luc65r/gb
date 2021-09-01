#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#include "gb_cpu.h"

#define REG8(name, n)                                       \
    uint8_t gb_cpu_get_reg_##name(GbCpu *cpu) {             \
        assert(cpu != NULL);                                \
        return cpu->reg[n];                                 \
    }                                                       \
    void gb_cpu_set_reg_##name(GbCpu *cpu, uint8_t value) { \
        assert(cpu != NULL);                                \
        cpu->reg[n] = value;                                \
    }

REG8(a, 0)
REG8(b, 2)
REG8(c, 3)
REG8(d, 4)
REG8(e, 5)
REG8(h, 6)
REG8(l, 7)

#undef REG8

#pragma GCC diagnostic ignored "-Wconversion"

#define REG16(name, n)                                                  \
    uint16_t gb_cpu_get_reg_##name(GbCpu *cpu) {                        \
        assert(cpu != NULL);                                            \
        return ((uint16_t)cpu->reg[n * 2] << 8)                         \
            | cpu->reg[n * 2 + 1];                                      \
    }                                                                   \
    void gb_cpu_set_reg_##name(GbCpu *cpu, uint16_t value) {            \
        assert(cpu != NULL);                                            \
        cpu->reg[n * 2] = (uint8_t)(value >> 8);                        \
        cpu->reg[n * 2 + 1] = (uint8_t)value;                           \
    }

REG16(af, 0)
REG16(bc, 1)
REG16(de, 2)
REG16(hl, 3)
REG16(sp, 4)
REG16(pc, 5)

#undef REG16

#define FLAG(name, n)                                       \
    bool gb_cpu_get_flag_##name(GbCpu *cpu) {               \
        assert(cpu != NULL);                                \
        return (bool)(cpu->reg[1] >> n);                    \
    }                                                       \
    void gb_cpu_set_flag_##name(GbCpu *cpu, bool value) {   \
        assert(cpu != NULL);                                \
        cpu->reg[1] = cpu->reg[1]                           \
            ^ ((-(uint8_t)value ^ cpu->reg[1])              \
               & (uint8_t)(1U << n));                       \
    }

FLAG(z, 7)
FLAG(n, 6)
FLAG(h, 5)
FLAG(c, 4)

#undef FLAG
