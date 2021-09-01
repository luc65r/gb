#ifndef GB_INSTRS_H
#define GB_INSTRS_H

#include "gb_cpu.h"

typedef void (*GbInstructionFn)(GbCpu *cpu);

typedef struct {
    GbInstructionFn fn;
} GbInstruction;

extern const GbInstruction gb_instruction_table[256];

#endif
