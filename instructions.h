#ifndef INSTRUCTIONS
#define INSTRUCTIONS

#include <stdio.h>
#include "_8080emulator.h"

void emulate8080_inst(state8080 *state);

static unsigned lxi(state8080 *state, uint8_t *reg0, uint8_t *reg1);
static unsigned stax(state8080 *state, uint8_t reg0, uint8_t reg1);
static unsigned inx(uint8_t *reg0, uint8_t *reg1);
static unsigned inr(state8080 *state, uint8_t *reg);
static unsigned dcr(state8080 *state, uint8_t *reg);
static unsigned mvi(state8080 *state, uint8_t *reg);
static unsigned rlc(state8080 *state);
static unsigned dad(state8080 *state, uint8_t reg0, uint8_t reg1);
static unsigned ldax(state8080 *state, uint8_t reg0, uint8_t reg1);
static unsigned dcx(uint8_t *reg0, uint8_t *reg1);
static unsigned rrc(state8080 *state);
static unsigned ral(state8080 *state);
static unsigned rar(state8080 *state);
static unsigned shld(state8080 *state);
static unsigned daa(state8080 *state);
static unsigned lhld(state8080 *state);
static unsigned cma(state8080 *state);
static unsigned sta(state8080 *state);
static unsigned stc(state8080 *state);
static unsigned lda(state8080 *state);
static unsigned cmc(state8080 *state);
static unsigned mov(uint8_t *reg0, uint8_t reg1);
static unsigned hlt(state8080 *state);
static unsigned add(state8080 *state, uint8_t reg);
static unsigned adc(state8080 *state, uint8_t reg);
static unsigned sub(state8080 *state, uint8_t reg);
static unsigned sbb(state8080 *state, uint8_t reg);
static unsigned ana(state8080 *state, uint8_t reg);
static unsigned xra(state8080 *state, uint8_t reg);
static unsigned ora(state8080 *state, uint8_t reg);
static unsigned cmp(state8080 *state, uint8_t reg);
static unsigned rnz(state8080 *state);
static unsigned pop(state8080 *state, uint8_t *reg0, uint8_t *reg1);
static unsigned jnz(state8080 *state);
static unsigned jmp(state8080 *state);
static unsigned cnz(state8080 *state);
static unsigned push(state8080 *state, uint8_t reg0, uint8_t reg1);
static unsigned adi(state8080 *state);
static unsigned rst(state8080 *state, unsigned n);
static unsigned rz(state8080 *state);
static unsigned ret(state8080 *state);
static unsigned jz(state8080 *state);
static unsigned cz(state8080 *state);
static unsigned call(state8080 *state);
static unsigned aci(state8080 *state);
static unsigned rnc(state8080 *state);
static unsigned jnc(state8080 *state);
static unsigned out(state8080 *state);
static unsigned cnc(state8080 *state);
static unsigned sui(state8080 *state);
static unsigned rc(state8080 *state);
static unsigned jc(state8080 *state);
static unsigned in(state8080 *state);
static unsigned cc(state8080 *state);
static unsigned sbi(state8080 *state);
static unsigned rpo(state8080 *state);
static unsigned jpo(state8080 *state);
static unsigned xthl(state8080 *state);
static unsigned cpo(state8080 *state);
static unsigned ani(state8080 *state);
static unsigned rpe(state8080 *state);
static unsigned pchl(state8080 *state);
static unsigned jpe(state8080 *state);
static unsigned xchg(state8080 *state);
static unsigned cpe(state8080 *state);
static unsigned xri(state8080 *state);
static unsigned cpe(state8080 *state);
static unsigned rp(state8080 *state);
static unsigned jp(state8080 *state);
static unsigned di(state8080 *state);
static unsigned cp(state8080 *state);
static unsigned ori(state8080 *state);
static unsigned rm(state8080 *state);
static unsigned sphl(state8080 *state);
static unsigned jm(state8080 *state);
static unsigned ei(state8080 *state);
static unsigned cm(state8080 *state);
static unsigned cpi(state8080 *state);
static void unimplemented_inst(state8080 *state);

static void set_arthmetic_flags(state8080 *state, uint16_t n);
static bool check_auxillary(uint16_t n);
static bool check_parity(uint8_t n);

#endif
