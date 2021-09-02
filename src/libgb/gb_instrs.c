#include <assert.h>
#include <inttypes.h>

#include "gb_instrs.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#define INSTR(name) static void name(GbCpu *cpu)

#define ALL_REGS8(X) \
    X(a) X(b) X(c) X(d) X(e) X(h) X(l)

#define __ALL_REGS8_CROSS(X, r) \
    X(r, a) X(r, b) X(r, c) X(r, d) X(r, e) X(r, h) X(r, l)

#define ALL_REGS8_CROSS(X) \
    __ALL_REGS8_CROSS(X, a) \
    __ALL_REGS8_CROSS(X, b) \
    __ALL_REGS8_CROSS(X, c) \
    __ALL_REGS8_CROSS(X, d) \
    __ALL_REGS8_CROSS(X, e) \
    __ALL_REGS8_CROSS(X, h) \
    __ALL_REGS8_CROSS(X, l)

#define ALL_REGS16(X) \
    X(bc) X(de) X(hl) X(sp)

INSTR(nop) {
    /* TODO */
}

INSTR(stop) {
    /* TODO */
}

#define INC8(r)                                                 \
    INSTR(inc_##r) {                                            \
        gb_cpu_set_reg_##r(cpu, gb_cpu_get_reg_##r(cpu) + 1);   \
        /* TODO: flags */                                       \
    }
ALL_REGS8(INC8)
#undef INC8

#define INC16(r)                                                \
    INSTR(inc_##r) {                                            \
        gb_cpu_set_reg_##r(cpu, gb_cpu_get_reg_##r(cpu) + 1);   \
        /* TODO: wrapping */                                    \
    }
ALL_REGS16(INC16)
#undef INC16

INSTR(inc_phl) {
    /* TODO */
}

#define DEC8(r)                                                 \
    INSTR(dec_##r) {                                            \
        gb_cpu_set_reg_##r(cpu, gb_cpu_get_reg_##r(cpu) - 1);   \
        /* TODO: flags */                                       \
    }
ALL_REGS8(DEC8)
#undef DEC8

#define DEC16(r)                                                \
    INSTR(dec_##r) {                                            \
        gb_cpu_set_reg_##r(cpu, gb_cpu_get_reg_##r(cpu) - 1);   \
        /* TODO: wrapping */                                    \
    }
ALL_REGS16(DEC16)
#undef DEC16

INSTR(dec_phl) {
    /* TODO */
}

#define LD(r1, r2)                                          \
    INSTR(ld_##r1##_##r2) {                                 \
        gb_cpu_set_reg_##r1(cpu, gb_cpu_get_reg_##r2(cpu)); \
        gb_cpu_set_reg_pc(cpu, gb_cpu_get_reg_pc(cpu) + 1); \
    }
ALL_REGS8_CROSS(LD)
#undef LD

#define LD(r1, r2)                                                      \
    INSTR(ld_p##r1##_##r2) {                                            \
        gb_mmu_write8(cpu->mmu, gb_cpu_get_reg_##r1(cpu), gb_cpu_get_reg_##r2(cpu)); \
        gb_cpu_set_reg_pc(cpu, gb_cpu_get_reg_pc(cpu) + 1);             \
    }                                                                   \
    INSTR(ld_##r2##_p##r1) {                                            \
        gb_cpu_set_reg_##r2(cpu, gb_mmu_read8(cpu->mmu, gb_cpu_get_reg_##r1(cpu))); \
        gb_cpu_set_reg_pc(cpu, gb_cpu_get_reg_pc(cpu) + 1);             \
    }
LD(bc, a) LD(de, a)
#define LDHL(r) LD(hl, r)
ALL_REGS8(LDHL)
#undef LDHL
#undef LD

INSTR(ld_phli_a) {
    uint16_t hl = gb_cpu_get_reg_hl(cpu);
    gb_mmu_write8(cpu->mmu, hl, gb_cpu_get_reg_a(cpu));
    gb_cpu_set_reg_hl(cpu, hl + 1);
    gb_cpu_set_reg_pc(cpu, gb_cpu_get_reg_pc(cpu) + 1);
}

INSTR(ld_phld_a) {
    uint16_t hl = gb_cpu_get_reg_hl(cpu);
    gb_mmu_write8(cpu->mmu, hl, gb_cpu_get_reg_a(cpu));
    gb_cpu_set_reg_hl(cpu, hl - 1);
    gb_cpu_set_reg_pc(cpu, gb_cpu_get_reg_pc(cpu) + 1);
}

INSTR(ld_a_phli) {
    uint16_t hl = gb_cpu_get_reg_hl(cpu);
    gb_cpu_set_reg_a(cpu, gb_mmu_read8(cpu->mmu, hl));
    gb_cpu_set_reg_hl(cpu, hl + 1);
    gb_cpu_set_reg_pc(cpu, gb_cpu_get_reg_pc(cpu) + 1);
}

INSTR(ld_a_phld) {
    uint16_t hl = gb_cpu_get_reg_hl(cpu);
    gb_cpu_set_reg_a(cpu, gb_mmu_read8(cpu->mmu, hl));
    gb_cpu_set_reg_hl(cpu, hl - 1);
    gb_cpu_set_reg_pc(cpu, gb_cpu_get_reg_pc(cpu) + 1);
}

#define LD(r)                                                       \
    INSTR(ld_##r##_u8) {                                            \
        uint16_t pc = gb_cpu_get_reg_pc(cpu);                       \
        gb_cpu_set_reg_##r(cpu, gb_mmu_read8(cpu->mmu, pc + 1));    \
        gb_cpu_set_reg_pc(cpu, pc + 2);                             \
    }
ALL_REGS8(LD)
#undef LD

INSTR(ld_phl_u8) {
    uint16_t pc = gb_cpu_get_reg_pc(cpu);
    gb_mmu_write8(cpu->mmu, gb_cpu_get_reg_hl(cpu), gb_mmu_read8(cpu->mmu, pc + 1));
    gb_cpu_set_reg_bc(cpu, pc + 2);
}
    
#define LD(r)                                   \
    INSTR(ld_##r##_u16) {                       \
        /* TODO */                              \
    }
ALL_REGS16(LD)
#undef LD

INSTR(ld_pu16_sp) {
    /* TODO */
}

INSTR(rlca) {
    /* TODO */
}

INSTR(rla) {
    /* TODO */
}

INSTR(rrca) {
    /* TODO */
}

INSTR(rra) {
    /* TODO */
}

INSTR(daa) {
    /* TODO */
}

INSTR(cpl) {
    /* TODO */
}

INSTR(scf) {
    /* TODO */
}

INSTR(ccf) {
    /* TODO */
}

INSTR(halt) {
    /* TODO */
}

#define ADD(r)                                  \
    INSTR(add_hl_##r) {                         \
        /* TODO */                              \
    }
ALL_REGS16(ADD)
#undef ADD

INSTR(jr_i8) {
    /* TODO */
}

#define JR(r)                                   \
    INSTR(jr_##r##_i8) {                        \
        /* TODO */                              \
    }                                           \
    INSTR(jr_n##r##_i8) {                       \
        /* TODO */                              \
    }
JR(z) JR(c)
#undef JR

const GbInstruction gb_instruction_table[256] = {
    [0x00] = { &nop },
    [0x01] = { &ld_bc_u16 },
    [0x02] = { &ld_pbc_a },
    [0x03] = { &inc_bc },
    [0x04] = { &inc_b },
    [0x05] = { &dec_b },
    [0x06] = { &ld_b_u8 },
    [0x07] = { &rlca },
    [0x08] = { &ld_pu16_sp },
    [0x09] = { &add_hl_bc },
    [0x0A] = { &ld_a_pbc },
    [0x0B] = { &dec_bc },
    [0x0C] = { &inc_c },
    [0x0D] = { &dec_c },
    [0x0E] = { &ld_c_u8 },
    [0x0F] = { &rrca },

    [0x10] = { &stop },
    [0x11] = { &ld_de_u16 },
    [0x12] = { &ld_pde_a },
    [0x13] = { &inc_de },
    [0x14] = { &inc_d },
    [0x15] = { &dec_d },
    [0x16] = { &ld_d_u8 },
    [0x17] = { &rla },
    [0x18] = { &jr_i8 },
    [0x19] = { &add_hl_de },
    [0x1A] = { &ld_a_pde },
    [0x1B] = { &dec_de },
    [0x1C] = { &inc_e },
    [0x1D] = { &dec_e },
    [0x1E] = { &ld_e_u8 },
    [0x1F] = { &rra },

    [0x20] = { &jr_nz_i8 },
    [0x21] = { &ld_hl_u16 },
    [0x22] = { &ld_phli_a },
    [0x23] = { &inc_hl },
    [0x24] = { &inc_h },
    [0x25] = { &dec_h },
    [0x26] = { &ld_h_u8 },
    [0x27] = { &daa },
    [0x28] = { &jr_z_i8 },
    [0x29] = { &add_hl_hl },
    [0x2A] = { &ld_a_phli },
    [0x2B] = { &dec_hl },
    [0x2C] = { &inc_l },
    [0x2D] = { &dec_l },
    [0x2E] = { &ld_l_u8 },
    [0x2F] = { &cpl },

    [0x30] = { &jr_nc_i8 },
    [0x31] = { &ld_sp_u16 },
    [0x32] = { &ld_phld_a },
    [0x33] = { &inc_sp },
    [0x34] = { &inc_phl },
    [0x35] = { &dec_phl },
    [0x36] = { &ld_phl_u8 },
    [0x37] = { &scf },
    [0x38] = { &jr_c_i8 },
    [0x39] = { &add_hl_sp },
    [0x3A] = { &ld_a_phld },
    [0x3B] = { &dec_sp },
    [0x3C] = { &inc_a },
    [0x3D] = { &dec_a },
    [0x3E] = { &ld_a_u8 },
    [0x3F] = { &ccf },

    [0x40] = { &ld_b_b },
    [0x41] = { &ld_b_c },
    [0x42] = { &ld_b_d },
    [0x43] = { &ld_b_e },
    [0x44] = { &ld_b_h },
    [0x45] = { &ld_b_l },
    [0x46] = { &ld_b_phl },
    [0x47] = { &ld_b_a },
    [0x48] = { &ld_c_b },
    [0x49] = { &ld_c_c },
    [0x4A] = { &ld_c_d },
    [0x4B] = { &ld_c_e },
    [0x4C] = { &ld_c_h },
    [0x4D] = { &ld_c_l },
    [0x4E] = { &ld_c_phl },
    [0x4F] = { &ld_c_a },

    [0x50] = { &ld_d_b },
    [0x51] = { &ld_d_c },
    [0x52] = { &ld_d_d },
    [0x53] = { &ld_d_e },
    [0x54] = { &ld_d_h },
    [0x55] = { &ld_d_l },
    [0x56] = { &ld_d_phl },
    [0x57] = { &ld_d_a },
    [0x58] = { &ld_e_b },
    [0x59] = { &ld_e_c },
    [0x5A] = { &ld_e_d },
    [0x5B] = { &ld_e_e },
    [0x5C] = { &ld_e_h },
    [0x5D] = { &ld_e_l },
    [0x5E] = { &ld_e_phl },
    [0x5F] = { &ld_e_a },

    [0x60] = { &ld_h_b },
    [0x61] = { &ld_h_c },
    [0x62] = { &ld_h_d },
    [0x63] = { &ld_h_e },
    [0x64] = { &ld_h_h },
    [0x65] = { &ld_h_l },
    [0x66] = { &ld_h_phl },
    [0x67] = { &ld_h_a },
    [0x68] = { &ld_l_b },
    [0x69] = { &ld_l_c },
    [0x6A] = { &ld_l_d },
    [0x6B] = { &ld_l_e },
    [0x6C] = { &ld_l_h },
    [0x6D] = { &ld_l_l },
    [0x6E] = { &ld_l_phl },
    [0x6F] = { &ld_l_a },

    [0x70] = { &ld_phl_b },
    [0x71] = { &ld_phl_c },
    [0x72] = { &ld_phl_d },
    [0x73] = { &ld_phl_e },
    [0x74] = { &ld_phl_h },
    [0x75] = { &ld_phl_l },
    [0x76] = { &halt },
    [0x77] = { &ld_phl_a },
    [0x78] = { &ld_a_b },
    [0x79] = { &ld_a_c },
    [0x7A] = { &ld_a_d },
    [0x7B] = { &ld_a_e },
    [0x7C] = { &ld_a_h },
    [0x7D] = { &ld_a_l },
    [0x7E] = { &ld_a_phl },
    [0x7F] = { &ld_a_a },
};
