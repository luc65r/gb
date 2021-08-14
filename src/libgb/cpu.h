#ifndef CPU_H
#define CPU_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct {
    /* Avoid union to not rely on endianness */
    uint8_t reg[12];
} GbCpu;

#define REG(name, size)                                             \
    uint##size##_t gb_cpu_get_reg_##name(GbCpu *cpu);               \
    void gb_cpu_set_reg_##name(GbCpu *cpu, uint##size##_t value);

REG(a, 8)
REG(b, 8)
REG(c, 8)
REG(d, 8)
REG(e, 8)
REG(h, 8)
REG(l, 8)

REG(af, 16)
REG(bc, 16)
REG(de, 16)
REG(hl, 16)
REG(sp, 16)
REG(pc, 16)

#undef REG

#define FLAG(name)                                          \
    bool gb_cpu_get_flag_##name(GbCpu *cpu);                \
    void gb_cpu_set_flag_##name(GbCpu *cpu, bool value);

FLAG(z) /* Zero flag */
FLAG(n) /* Substraction flag */
FLAG(h) /* Half carry flag */
FLAG(c) /* Carry flag */

#undef FLAG

#endif
