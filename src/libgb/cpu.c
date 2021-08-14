#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cpu.h"

#define REG(name, n)                                        \
    uint8_t gb_cpu_get_reg_##name(GbCpu *cpu) {             \
        assert(cpu != NULL);                                \
        return cpu->reg[n];                                 \
    }                                                       \
    void gb_cpu_set_reg_##name(GbCpu *cpu, uint8_t value) { \
        assert(cpu != NULL);                                \
        cpu->reg[n] = value;                                \
    }

REG(a, 0)
REG(b, 2)
REG(c, 3)
REG(d, 4)
REG(e, 5)
REG(h, 6)
REG(l, 7)

#undef REG
#define REG(name, n)                                                    \
    uint16_t gb_cpu_get_reg_##name(GbCpu *cpu) {                        \
        assert(cpu != NULL);                                            \
        return (uint16_t)((uint16_t)cpu->reg[n * 2] << 8)               \
            + cpu->reg[n * 2 + 1];                                      \
    }                                                                   \
    void gb_cpu_set_reg_##name(GbCpu *cpu, uint16_t value) {            \
        assert(cpu != NULL);                                            \
        cpu->reg[n * 2] = (uint8_t)(value >> 8);                        \
        cpu->reg[n * 2 + 1] = (uint8_t)value;                           \
    }

REG(af, 0)
REG(bc, 1)
REG(de, 2)
REG(hl, 3)
REG(sp, 4)
REG(pc, 5)

#undef REG

#define FLAG(name, n)                                       \
    bool gb_cpu_get_flag_##name(GbCpu *cpu) {               \
        assert(cpu != NULL);                                \
        return (bool)(cpu->reg[1] >> n);                    \
    }                                                       \
    void gb_cpu_set_flag_##name(GbCpu *cpu, bool value) {   \
        assert(cpu != NULL);                                \
        cpu->reg[1] = (uint8_t)(cpu->reg[1]                 \
                                ^ ((-(uint8_t)value         \
                                    ^ cpu->reg[1])          \
                                   & (uint8_t)(1U << n)));  \
    }

FLAG(z, 7)
FLAG(n, 6)
FLAG(h, 5)
FLAG(c, 4)

#undef FLAG
