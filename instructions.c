#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "instructions.h"
#include "_8080emulator.h"

// copied from https://github.com/kpmiller/emulator101
uint8_t cycles8080[] = {
	4, 10, 7, 5, 5, 5, 7, 4, 4, 10, 7, 5, 5, 5, 7, 4, //0x00..0x0f
	4, 10, 7, 5, 5, 5, 7, 4, 4, 10, 7, 5, 5, 5, 7, 4, //0x10..0x1f
	4, 10, 16, 5, 5, 5, 7, 4, 4, 10, 16, 5, 5, 5, 7, 4, //etc
	4, 10, 13, 5, 10, 10, 10, 4, 4, 10, 13, 5, 5, 5, 7, 4,
	
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5, //0x40..0x4f
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 5,
	
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4, //0x80..8x4f
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	
	11, 10, 10, 10, 17, 11, 7, 11, 11, 10, 10, 10, 10, 17, 7, 11, //0xc0..0xcf
	11, 10, 10, 10, 17, 11, 7, 11, 11, 10, 10, 10, 10, 17, 7, 11, 
	11, 10, 10, 18, 17, 11, 7, 11, 11, 5, 10, 5, 17, 17, 7, 11, 
	11, 10, 10, 4, 17, 11, 7, 11, 11, 5, 10, 4, 17, 17, 7, 11, 
};

size_t emulate8080_inst(state8080 *state) {
    // the size of an instruction that increments the pc register after
    // each instruction
    size_t inst_siz = 1;
    // current processor instruction
    uint8_t inst = state->memory[state->pc];

    // yet another big ass switchcase generated with a python script
    switch (inst) {
    case OPCODE_NOP:
        break;
    case OPCODE_LXI_B_D16:
        inst_siz = lxi(state, &state->b, &state->c);
        break;
    case OPCODE_STAX_B:
        inst_siz = stax(state, state->b, state->c);
        break;
    case OPCODE_INX_B:
        inst_siz = inx(&state->b, &state->c);
        break;
    case OPCODE_INR_B:
        inst_siz = inr(state, &state->b);
        break;
    case OPCODE_DCR_B:
        inst_siz = dcr(state, &state->b);
        break;
    case OPCODE_MVI_B_D8:
        inst_siz = mvi(state, &state->b);
        break;
    case OPCODE_RLC:
        inst_siz = rlc(state);
        break;
    case OPCODE_DAD_B:
        inst_siz = dad(state, state->b, state->c);
        break;
    case OPCODE_LDAX_B:
        inst_siz = ldax(state, state->b, state->c);
        break;
    case OPCODE_DCX_B:
        inst_siz = dcx(&state->b, &state->c);
        break;
    case OPCODE_INR_C:
        inst_siz = inr(state, &state->c);
        break;
    case OPCODE_DCR_C:
        inst_siz = dcr(state, &state->c);
        break;
    case OPCODE_MVI_C_D8:
        inst_siz = mvi(state, &state->c);
        break;
    case OPCODE_RRC:
        inst_siz = rrc(state);
        break;
    case OPCODE_LXI_D_D16:
        inst_siz = lxi(state, &state->d, &state->e);
        break;
    case OPCODE_STAX_D:
        inst_siz = stax(state, state->d, state->e);
        break;
    case OPCODE_INX_D:
        inst_siz = inx(&state->d, &state->e);
        break;
    case OPCODE_INR_D:
        inst_siz = inr(state, &state->d);
        break;
    case OPCODE_DCR_D:
        inst_siz = dcr(state, &state->d);
        break;
    case OPCODE_MVI_D_D8:
        inst_siz = mvi(state, &state->d);
        break;
    case OPCODE_RAL:
        inst_siz = ral(state);
        break;
    case OPCODE_DAD_D:
        inst_siz = dad(state, state->d, state->e);
        break;
    case OPCODE_LDAX_D:
        inst_siz = ldax(state, state->d, state->e);
        break;
    case OPCODE_DCX_D:
        inst_siz = dcx(&state->d, &state->e);
        break;
    case OPCODE_INR_E:
        inst_siz = inr(state, &state->e);
        break;
    case OPCODE_DCR_E:
        inst_siz = dcr(state, &state->e);
        break;
    case OPCODE_MVI_E_D8:
        inst_siz = mvi(state, &state->e);
        break;
    case OPCODE_RAR:
        inst_siz = rar(state);
        break;
    case OPCODE_LXI_H_D16:
        inst_siz = lxi(state, &state->h, &state->l);
        break;
    case OPCODE_SHLD:
        inst_siz = shld(state);
        break;
    case OPCODE_INX_H:
        inst_siz = inx(&state->h, &state->l);
        break;
    case OPCODE_INR_H:
        inst_siz = inr(state, &state->h);
        break;
    case OPCODE_DCR_H:
        inst_siz = dcr(state, &state->h);
        break;
    case OPCODE_MVI_H_D8:
        inst_siz = mvi(state, &state->h);
        break;
    case OPCODE_DAA:
        inst_siz = daa(state);
        break;
    case OPCODE_DAD_H:
        inst_siz = dad(state, state->h, state->l);
        break;
    case OPCODE_LHLD:
        inst_siz = lhld(state);
        break;
    case OPCODE_DCX_H:
        inst_siz = dcx(&state->h, &state->l);
        break;
    case OPCODE_INR_L:
        inst_siz = inr(state, &state->l);
        break;
    case OPCODE_DCR_L:
        inst_siz = dcr(state, &state->l);
        break;
    case OPCODE_MVI_L_D8:
        inst_siz = mvi(state, &state->l);
        break;
    case OPCODE_CMA:
        inst_siz = cma(state);
        break;
    case OPCODE_LXI_SP_D16:
        inst_siz = lxi(state, ((uint8_t *)&state->sp)+1,
                       (uint8_t *)&state->sp);
        break;
    case OPCODE_STA:
        inst_siz = sta(state);
        break;
    case OPCODE_INX_SP:
        inst_siz = inx(((uint8_t *)&state->sp)+1, (uint8_t *)&state->sp);
        break;
    case OPCODE_INR_M:
        inst_siz = inr(state, &state->memory[(state->h << 8) + state->l]);
        break;
    case OPCODE_DCR_M:
        inst_siz = dcr(state, &state->memory[(state->h << 8) + state->l]);
        break;
    case OPCODE_MVI_M_D8:
        inst_siz = mvi(state, &state->memory[(state->h << 8) + state->l]);
        break;
    case OPCODE_STC:
        inst_siz = stc(state);
        break;
    case OPCODE_DAD_SP:
        inst_siz = dad(state, *(((uint8_t *)&state->sp)+1),
                       *(uint8_t *)&state->sp);
        break;
    case OPCODE_LDA:
        inst_siz = lda(state);
        break;
    case OPCODE_DCX_SP:
        inst_siz = dcx(((uint8_t *)&state->sp)+1, (uint8_t *)&state->sp);
        break;
    case OPCODE_INR_A:
        inst_siz = inr(state, &state->a);
        break;
    case OPCODE_DCR_A:
        inst_siz = dcr(state, &state->a);
        break;
    case OPCODE_MVI_A_D8:
        inst_siz = mvi(state, &state->a);
        break;
    case OPCODE_CMC:
        inst_siz = cmc(state);
        break;
    case OPCODE_MOV_B_B:
        inst_siz = mov(&state->b, state->b);
        break;
    case OPCODE_MOV_B_C:
        inst_siz = mov(&state->b, state->c);
        break;
    case OPCODE_MOV_B_D:
        inst_siz = mov(&state->b, state->d);
        break;
    case OPCODE_MOV_B_E:
        inst_siz = mov(&state->b, state->e);
        break;
    case OPCODE_MOV_B_H:
        inst_siz = mov(&state->b, state->h);
        break;
    case OPCODE_MOV_B_L:
        inst_siz = mov(&state->b, state->l);
        break;
    case OPCODE_MOV_B_M:
        inst_siz = mov(&state->b, 
                       state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_MOV_B_A:
        inst_siz = mov(&state->b, state->a);
        break;
    case OPCODE_MOV_C_B:
        inst_siz = mov(&state->c, state->b);
        break;
    case OPCODE_MOV_C_C:
        inst_siz = mov(&state->c, state->c);
        break;
    case OPCODE_MOV_C_D:
        inst_siz = mov(&state->c, state->d);
        break;
    case OPCODE_MOV_C_E:
        inst_siz = mov(&state->c, state->e);
        break;
    case OPCODE_MOV_C_H:
        inst_siz = mov(&state->c, state->h);
        break;
    case OPCODE_MOV_C_L:
        inst_siz = mov(&state->c, state->l);
        break;
    case OPCODE_MOV_C_M:
        inst_siz = mov(&state->c, 
                       state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_MOV_C_A:
        inst_siz = mov(&state->c, state->a);
        break;
    case OPCODE_MOV_D_B:
        inst_siz = mov(&state->d, state->b);
        break;
    case OPCODE_MOV_D_C:
        inst_siz = mov(&state->d, state->c);
        break;
    case OPCODE_MOV_D_D:
        inst_siz = mov(&state->d, state->d);
        break;
    case OPCODE_MOV_D_E:
        inst_siz = mov(&state->d, state->e);
        break;
    case OPCODE_MOV_D_H:
        inst_siz = mov(&state->d, state->h);
        break;
    case OPCODE_MOV_D_L:
        inst_siz = mov(&state->d, state->l);
        break;
    case OPCODE_MOV_D_M:
        inst_siz = mov(&state->d, 
                       state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_MOV_D_A:
        inst_siz = mov(&state->d, state->a);
        break;
    case OPCODE_MOV_E_B:
        inst_siz = mov(&state->e, state->b);
        break;
    case OPCODE_MOV_E_C:
        inst_siz = mov(&state->e, state->c);
        break;
    case OPCODE_MOV_E_D:
        inst_siz = mov(&state->e, state->d);
        break;
    case OPCODE_MOV_E_E:
        inst_siz = mov(&state->e, state->e);
        break;
    case OPCODE_MOV_E_H:
        inst_siz = mov(&state->e, state->h);
        break;
    case OPCODE_MOV_E_L:
        inst_siz = mov(&state->e, state->l);
        break;
    case OPCODE_MOV_E_M:
        inst_siz = mov(&state->e, 
                       state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_MOV_E_A:
        inst_siz = mov(&state->e, state->a);
        break;
    case OPCODE_MOV_H_B:
        inst_siz = mov(&state->h, state->b);
        break;
    case OPCODE_MOV_H_C:
        inst_siz = mov(&state->h, state->c);
        break;
    case OPCODE_MOV_H_D:
        inst_siz = mov(&state->h, state->d);
        break;
    case OPCODE_MOV_H_E:
        inst_siz = mov(&state->h, state->e);
        break;
    case OPCODE_MOV_H_H:
        inst_siz = mov(&state->h, state->h);
        break;
    case OPCODE_MOV_H_L:
        inst_siz = mov(&state->h, state->l);
        break;
    case OPCODE_MOV_H_M:
        inst_siz = mov(&state->h, 
                       state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_MOV_H_A:
        inst_siz = mov(&state->h, state->a);
        break;
    case OPCODE_MOV_L_B:
        inst_siz = mov(&state->l, state->b);
        break;
    case OPCODE_MOV_L_C:
        inst_siz = mov(&state->l, state->c);
        break;
    case OPCODE_MOV_L_D:
        inst_siz = mov(&state->l, state->d);
        break;
    case OPCODE_MOV_L_E:
        inst_siz = mov(&state->l, state->e);
        break;
    case OPCODE_MOV_L_H:
        inst_siz = mov(&state->l, state->h);
        break;
    case OPCODE_MOV_L_L:
        inst_siz = mov(&state->l, state->l);
        break;
    case OPCODE_MOV_L_M:
        inst_siz = mov(&state->l, 
                       state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_MOV_L_A:
        inst_siz = mov(&state->l, state->a);
        break;
    case OPCODE_MOV_M_B:
        inst_siz = mov(&state->memory[state->h << 8 | state->l],
                       state->b);
        break;
    case OPCODE_MOV_M_C:
        inst_siz = mov(&state->memory[state->h << 8 | state->l],
                       state->c);
        break;
    case OPCODE_MOV_M_D:
        inst_siz = mov(&state->memory[state->h << 8 | state->l],
                       state->d);
        break;
    case OPCODE_MOV_M_E:
        inst_siz = mov(&state->memory[state->h << 8 | state->l],
                       state->e);
        break;
    case OPCODE_MOV_M_H:
        inst_siz = mov(&state->memory[state->h << 8 | state->l],
                       state->h);
        break;
    case OPCODE_MOV_M_L:
        inst_siz = mov(&state->memory[state->h << 8 | state->l],
                       state->l);
        break;
    case OPCODE_HLT:
        inst_siz = hlt(state);
        break;
    case OPCODE_MOV_M_A:
        inst_siz = mov(&state->memory[state->h << 8 | state->l],
                       state->a);
        break;
    case OPCODE_MOV_A_B:
        inst_siz = mov(&state->a, state->b);
        break;
    case OPCODE_MOV_A_C:
        inst_siz = mov(&state->a, state->c);
        break;
    case OPCODE_MOV_A_D:
        inst_siz = mov(&state->a, state->d);
        break;
    case OPCODE_MOV_A_E:
        inst_siz = mov(&state->a, state->e);
        break;
    case OPCODE_MOV_A_H:
        inst_siz = mov(&state->a, state->h);
        break;
    case OPCODE_MOV_A_L:
        inst_siz = mov(&state->a, state->l);
        break;
    case OPCODE_MOV_A_M:
        inst_siz = mov(&state->a, 
                       state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_MOV_A_A:
        inst_siz = mov(&state->a, state->a);
        break;
    case OPCODE_ADD_B:
        inst_siz = add(state, state->b);
        break;
    case OPCODE_ADD_C:
        inst_siz = add(state, state->c);
        break;
    case OPCODE_ADD_D:
        inst_siz = add(state, state->d);
        break;
    case OPCODE_ADD_E:
        inst_siz = add(state, state->e);
        break;
    case OPCODE_ADD_H:
        inst_siz = add(state, state->h);
        break;
    case OPCODE_ADD_L:
        inst_siz = add(state, state->l);
        break;
    case OPCODE_ADD_M:
        inst_siz = add(state, state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_ADD_A:
        inst_siz = add(state, state->a);
        break;
    case OPCODE_ADC_B:
        inst_siz = adc(state, state->b);
        break;
    case OPCODE_ADC_C:
        inst_siz = adc(state, state->c);
        break;
    case OPCODE_ADC_D:
        inst_siz = adc(state, state->d);
        break;
    case OPCODE_ADC_E:
        inst_siz = adc(state, state->e);
        break;
    case OPCODE_ADC_H:
        inst_siz = adc(state, state->h);
        break;
    case OPCODE_ADC_L:
        inst_siz = adc(state, state->l);
        break;
    case OPCODE_ADC_M:
        inst_siz = adc(state, state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_ADC_A:
        inst_siz = adc(state, state->a);
        break;
    case OPCODE_SUB_B:
        inst_siz = sub(state, state->b);
        break;
    case OPCODE_SUB_C:
        inst_siz = sub(state, state->c);
        break;
    case OPCODE_SUB_D:
        inst_siz = sub(state, state->d);
        break;
    case OPCODE_SUB_E:
        inst_siz = sub(state, state->e);
        break;
    case OPCODE_SUB_H:
        inst_siz = sub(state, state->h);
        break;
    case OPCODE_SUB_L:
        inst_siz = sub(state, state->l);
        break;
    case OPCODE_SUB_M:
        inst_siz = sub(state, state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_SUB_A:
        inst_siz = sub(state, state->a);
        break;
    case OPCODE_SBB_B:
        inst_siz = sbb(state, state->b);
        break;
    case OPCODE_SBB_C:
        inst_siz = sbb(state, state->c);
        break;
    case OPCODE_SBB_D:
        inst_siz = sbb(state, state->d);
        break;
    case OPCODE_SBB_E:
        inst_siz = sbb(state, state->e);
        break;
    case OPCODE_SBB_H:
        inst_siz = sbb(state, state->h);
        break;
    case OPCODE_SBB_L:
        inst_siz = sbb(state, state->l);
        break;
    case OPCODE_SBB_M:
        inst_siz = sbb(state, state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_SBB_A:
        inst_siz = sbb(state, state->a);
        break;
    case OPCODE_ANA_B:
        inst_siz = ana(state, state->b);
        break;
    case OPCODE_ANA_C:
        inst_siz = ana(state, state->c);
        break;
    case OPCODE_ANA_D:
        inst_siz = ana(state, state->d);
        break;
    case OPCODE_ANA_E:
        inst_siz = ana(state, state->e);
        break;
    case OPCODE_ANA_H:
        inst_siz = ana(state, state->h);
        break;
    case OPCODE_ANA_L:
        inst_siz = ana(state, state->l);
        break;
    case OPCODE_ANA_M:
        inst_siz = ana(state, state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_ANA_A:
        inst_siz = ana(state, state->a);
        break;
    case OPCODE_XRA_B:
        inst_siz = xra(state, state->b);
        break;
    case OPCODE_XRA_C:
        inst_siz = xra(state, state->c);
        break;
    case OPCODE_XRA_D:
        inst_siz = xra(state, state->d);
        break;
    case OPCODE_XRA_E:
        inst_siz = xra(state, state->e);
        break;
    case OPCODE_XRA_H:
        inst_siz = xra(state, state->h);
        break;
    case OPCODE_XRA_L:
        inst_siz = xra(state, state->l);
        break;
    case OPCODE_XRA_M:
        inst_siz = xra(state, state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_XRA_A:
        inst_siz = xra(state, state->a);
        break;
    case OPCODE_ORA_B:
        inst_siz = ora(state, state->b);
        break;
    case OPCODE_ORA_C:
        inst_siz = ora(state, state->c);
        break;
    case OPCODE_ORA_D:
        inst_siz = ora(state, state->d);
        break;
    case OPCODE_ORA_E:
        inst_siz = ora(state, state->e);
        break;
    case OPCODE_ORA_H:
        inst_siz = ora(state, state->h);
        break;
    case OPCODE_ORA_L:
        inst_siz = ora(state, state->l);
        break;
    case OPCODE_ORA_M:
        inst_siz = ora(state, state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_ORA_A:
        inst_siz = ora(state, state->a);
        break;
    case OPCODE_CMP_B:
        inst_siz = cmp(state, state->b);
        break;
    case OPCODE_CMP_C:
        inst_siz = cmp(state, state->c);
        break;
    case OPCODE_CMP_D:
        inst_siz = cmp(state, state->d);
        break;
    case OPCODE_CMP_E:
        inst_siz = cmp(state, state->e);
        break;
    case OPCODE_CMP_H:
        inst_siz = cmp(state, state->h);
        break;
    case OPCODE_CMP_L:
        inst_siz = cmp(state, state->l);
        break;
    case OPCODE_CMP_M:
        inst_siz = cmp(state, state->memory[state->h << 8 | state->l]);
        break;
    case OPCODE_CMP_A:
        inst_siz = cmp(state, state->a);
        break;
    case OPCODE_RNZ:
        inst_siz = rnz(state);
        break;
    case OPCODE_POP_B:
        inst_siz = pop(state, &state->b, &state->c);
        break;
    case OPCODE_JNZ:
        inst_siz = jnz(state);
        break;
    case OPCODE_JMP:
        inst_siz = jmp(state);
        break;
    case OPCODE_CNZ:
        inst_siz = cnz(state);
        break;
    case OPCODE_PUSH_B:
        inst_siz = push(state, state->b, state->c);
        break;
    case OPCODE_ADI_D8:
        inst_siz = adi(state);
        break;
    case OPCODE_RST_0:
        inst_siz = rst(state, 0);
        break;
    case OPCODE_RZ:
        inst_siz = rz(state);
        break;
    case OPCODE_RET:
        inst_siz = ret(state);
        break;
    case OPCODE_JZ:
        inst_siz = jz(state);
        break;
    case OPCODE_CZ:
        inst_siz = cz(state);
        break;
    case OPCODE_CALL:
        inst_siz = call(state);
        break;
    case OPCODE_ACI_D8:
        inst_siz = aci(state);
        break;
    case OPCODE_RST_1:
        inst_siz = rst(state, 1);
        break;
    case OPCODE_RNC:
        inst_siz = rnc(state);
        break;
    case OPCODE_POP_D:
        inst_siz = pop(state, &state->d, &state->e);
        break;
    case OPCODE_JNC:
        inst_siz = jnc(state);
        break;
    case OPCODE_OUT_D8:
        inst_siz = out(state);
        break;
    case OPCODE_CNC:
        inst_siz = cnc(state);
        break;
    case OPCODE_PUSH_D:
        inst_siz = push(state, state->d, state->e);
        break;
    case OPCODE_SUI_D8:
        inst_siz = sui(state);
        break;
    case OPCODE_RST_2:
        inst_siz = rst(state, 2);
        break;
    case OPCODE_RC:
        inst_siz = rc(state);
        break;
    case OPCODE_JC:
        inst_siz = jc(state);
        break;
    case OPCODE_IN_D8:
        inst_siz = in(state);
        break;
    case OPCODE_CC:
        inst_siz = cc(state);
        break;
    case OPCODE_SBI_D8:
        inst_siz = sbi(state);
        break;
    case OPCODE_RST_3:
        inst_siz = rst(state, 3);
        break;
    case OPCODE_RPO:
        inst_siz = rpo(state);
        break;
    case OPCODE_POP_H:
        inst_siz = pop(state, &state->h, &state->l);
        break;
    case OPCODE_JPO:
        inst_siz = jpo(state);
        break;
    case OPCODE_XTHL:
        inst_siz = xthl(state);
        break;
    case OPCODE_CPO:
        inst_siz = cpo(state);
        break;
    case OPCODE_PUSH_H:
        inst_siz = push(state, state->h, state->l);
        break;
    case OPCODE_ANI_D8:
        inst_siz = ani(state);
        break;
    case OPCODE_RST_4:
        inst_siz = rst(state, 4);
        break;
    case OPCODE_RPE:
        inst_siz = rpe(state);
        break;
    case OPCODE_PCHL:
        inst_siz = pchl(state);
        break;
    case OPCODE_JPE:
        inst_siz = jpe(state);
        break;
    case OPCODE_XCHG:
        inst_siz = xchg(state);
        break;
    case OPCODE_CPE:
        inst_siz = cpe(state);
        break;
    case OPCODE_XRI_D8:
        inst_siz = xri(state);
        break;
    case OPCODE_RST_5:
        inst_siz = rst(state, 5);
        break;
    case OPCODE_RP:
        inst_siz = rp(state);
        break;
    case OPCODE_POP_PSW:
        inst_siz = pop(state, (uint8_t *)&state->flags, &state->a);
        break;
    case OPCODE_JP:
        inst_siz = jp(state);
        break;
    case OPCODE_DI:
        inst_siz = di(state);
        break;
    case OPCODE_CP:
        inst_siz = cp(state);
        break;
    case OPCODE_PUSH_PSW:
        inst_siz = push(state, *(uint8_t *)&state->flags, state->a);
        break;
    case OPCODE_ORI_D8:
        inst_siz = ori(state);
        break;
    case OPCODE_RST_6:
        inst_siz = rst(state, 6);
        break;
    case OPCODE_RM:
        inst_siz = rm(state);
        break;
    case OPCODE_SPHL:
        inst_siz = sphl(state);
        break;
    case OPCODE_JM:
        inst_siz = jm(state);
        break;
    case OPCODE_EI:
        inst_siz = ei(state);
        break;
    case OPCODE_CM:
        inst_siz = cm(state);
        break;
    case OPCODE_CPI_D8:
        inst_siz = cpi(state);
        break;
    case OPCODE_RST_7:
        inst_siz = rst(state, 7);
        break;
    default:
        unimplemented_inst(state);
        break;
    }
    state->pc += inst_siz;
    return cycles8080[inst];
}

static unsigned lxi(state8080 *state, uint8_t *reg0, uint8_t *reg1) {
    *reg0 = state->memory[state->pc+2];
    *reg1 = state->memory[state->pc+1];
    return 3;
}

static unsigned stax(state8080 *state, uint8_t reg0, uint8_t reg1) {
    state->memory[reg1 + (reg0 << 8)] = state->a;
    return 1;
}

static unsigned inx(uint8_t *reg0, uint8_t *reg1) {
    if (!++*reg1)
        ++*reg0;
    return 1;
}

static unsigned inr(state8080 *state, uint8_t *reg) {
    uint16_t n = *reg + 1;

    check_auxillary(state, *reg, 1);
    *reg = n & 0xff;
    set_arthmetic_flags(state, *reg);
    return 1;
}

static unsigned dcr(state8080 *state, uint8_t *reg) {
    uint16_t n = *reg - 1;

    check_auxillary(state, *reg, -1);
    *reg = n & 0xff;
    set_arthmetic_flags(state, *reg);
    return 1;
}

static unsigned mvi(state8080 *state, uint8_t *reg) {
    *reg = state->memory[state->pc+1];
    return 2;
}

static unsigned rlc(state8080 *state) {
    int8_t bit7 = (state->a & 0x80) > 0;

    state->a = (state->a << 1) | bit7;
    state->flags.cy = bit7;
    return 1;
}

static unsigned dad(state8080 *state, uint8_t reg0, uint8_t reg1) {
    uint32_t n, tmp, hl;

    tmp = (reg0 << 8) | reg1;
    hl = (state->h << 8) | state->l;
    n = tmp + hl;

    state->h = (n & 0xff00) >> 8;
    state->l = n & 0x00ff;
    state->flags.cy = n > (n & 0xffff);
    return 1;
}

static unsigned ldax(state8080 *state, uint8_t reg0, uint8_t reg1) {
    state->a = state->memory[(reg0 << 8) | reg1];
    return 1;
}

static unsigned dcx(uint8_t *reg0, uint8_t *reg1) {
    if (--*reg1 == 0xff)
        --*reg0;
    return 1;
}

static unsigned rrc(state8080 *state) {
    uint8_t bit0 = state->a & 0x01;

    state->a = (state->a >> 1) | (bit0 << 7);
    state->flags.cy = bit0;
    return 1;
}

static unsigned ral(state8080 *state) {
    uint8_t bit7 = (state->a & 0x80) > 0;

    state->a = (state->a << 1) | state->flags.cy;
    state->flags.cy = bit7;
    return 1;
}

static unsigned rar(state8080 *state) {
    uint8_t bit0 = state->a & 0x01;
    uint8_t bit7 = (state->a & 0x80) > 0;

    state->a = (state->a >> 1) | (state->flags.cy << 7);
    state->flags.cy = bit0;
    return 1;
}

static unsigned shld(state8080 *state) {
    uint16_t addr = state->memory[state->pc+1] |
                    state->memory[state->pc+2] << 8;

    state->memory[addr] = state->l;
    state->memory[addr+1] = state->h;
    return 3;
}

static unsigned daa(state8080 *state) {
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    if ((state->a & 0x0f) > 9 || state->flags.ac) {
        state->a += 6;
        check_auxillary(state, state->a, 6);
    }
    if ((state->a & 0xf0) > 0x90 || state->flags.ac) {
        uint16_t n = state->a + 6;
        if (n > 0xff)
            state->flags.cy = true;
        state->a = n & 0xff;
    }
    set_arthmetic_flags(state, state->a);
    return 1;
}

static unsigned lhld(state8080 *state) {
    uint16_t addr = state->memory[state->pc+1] |
                    state->memory[state->pc+2] << 8;

    state->l = state->memory[addr];
    state->h = state->memory[addr+1];
    return 3;
}

static unsigned cma(state8080 *state) {
    state->a = ~state->a;
    return 1;
}

static unsigned sta(state8080 *state) {
    uint16_t addr = state->memory[state->pc+1] |
                    state->memory[state->pc+2] << 8;

    state->memory[addr] = state->a;
    return 3;
}

static unsigned stc(state8080 *state) {
    state->flags.cy = 1;
    return 1;
}

static unsigned lda(state8080 *state) {
    uint16_t addr = state->memory[state->pc+1] |
                    state->memory[state->pc+2] << 8;

    state->a = state->memory[addr];
    return 3;
}

static unsigned cmc(state8080 *state) {
    state->flags.cy = !state->flags.cy;
    return 1;
}

static unsigned mov(uint8_t *reg0, uint8_t reg1) {
    *reg0 = reg1;
    return 1;
}

static unsigned hlt(state8080 *state) {
    // TODO
    printf("TODOHLT\n");
    return 1;
}

static unsigned add(state8080 *state, uint8_t reg) {
    uint16_t n = (uint16_t)state->a + reg;

    
    check_auxillary(state, reg, state->a);
    state->a = n & 0xff;
    set_arthmetic_flags(state, n);
    return 1;
}

static unsigned adc(state8080 *state, uint8_t reg) {
    uint16_t n = (uint16_t)state->a + reg + state->flags.cy;

    check_auxillary(state, reg, state->a + state->flags.cy);
    state->a = n & 0xff;
    set_arthmetic_flags(state, n);
    return 1;
}

static unsigned sub(state8080 *state, uint8_t reg) {
    uint16_t n = (uint16_t)state->a - reg;

    check_auxillary(state, state->a, -reg);
    state->a = n & 0xff;
    set_arthmetic_flags(state, n);
    return 1;
}

static unsigned sbb(state8080 *state, uint8_t reg) {
    uint16_t n = (uint16_t)state->a - reg - state->flags.cy;
 
    check_auxillary(state, state->a, -reg - state->flags.cy);
    state->a = n & 0xff;
    set_arthmetic_flags(state, n);
    return 1;
}

static unsigned ana(state8080 *state, uint8_t reg) {
    state->a &= reg;
    set_arthmetic_flags(state, (uint16_t)state->a);
    return 1;
}

static unsigned xra(state8080 *state, uint8_t reg) {
    state->a ^= reg;
    set_arthmetic_flags(state, (uint16_t)state->a);
    return 1;
}

static unsigned ora(state8080 *state, uint8_t reg) {
    state->a |= reg;
    set_arthmetic_flags(state, (uint16_t)state->a);
    return 1;
}

static unsigned cmp(state8080 *state, uint8_t reg) {
    uint16_t n = state->a - reg;

    set_arthmetic_flags(state, n);
    return 1;
}

static unsigned rnz(state8080 *state) {
    if (!state->flags.z)
        return ret(state);
    return 1;
}

static unsigned pop(state8080 *state, uint8_t *reg0, uint8_t *reg1) {
    *reg1 = state->memory[state->sp];
    *reg0 = state->memory[state->sp+1];
    state->sp += 2;
    return 1;
}

static unsigned jnz(state8080 *state) {
    if (!state->flags.z)
        return jmp(state);
    return 3;
}

static unsigned jmp(state8080 *state) {
    state->pc = state->memory[state->pc+1] | (state->memory[state->pc+2] << 8);
    return 0;
}

static unsigned cnz(state8080 *state) {
    if (!state->flags.z)
        return call(state);
    return 3;
}

static unsigned push(state8080 *state, uint8_t reg0, uint8_t reg1) {
    state->memory[state->sp-2] = reg1;
    state->memory[state->sp-1] = reg0;
    state->sp -= 2;
    return 1;
}

static unsigned adi(state8080 *state) {
    uint16_t n = state->a + state->memory[state->pc+1];

    check_auxillary(state, state->a, state->memory[state->pc+1]);
    state->a = n & 0xff;
    set_arthmetic_flags(state, n);
    return 2;
}

static unsigned rst(state8080 *state, unsigned n) {
    printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
    push(state, ((state->pc+3) & 0xff00) >> 8, (state->pc+3) & 0x00ff);
    state->pc = 8 * n;
    return 0;
}

static unsigned rz(state8080 *state) {
    if (state->flags.z)
        return ret(state);
    return 1;
}

static unsigned ret(state8080 *state) {
    state->pc = state->memory[state->sp];
    state->pc |= state->memory[state->sp+1] << 8;
    state->sp += 2;
    return 0;
}

static unsigned jz(state8080 *state) {
    if (state->flags.z)
        return jmp(state);
    return 3;
}

static unsigned cz(state8080 *state) {
    if (state->flags.z)
        return call(state);
    return 3;
}

static unsigned call(state8080 *state) {
    uint16_t addr;

    addr = state->memory[state->pc+1] | (state->memory[state->pc+2] << 8);
    // special case for cpudiag.
    // cpudiag is made for a system where the first 100 bytes in memory are 
    // for system stuff (probably CP/M or MSDOS),
    // ie calling the address $5 prints stuff to the console.
    // maybe I should remove those lines but I believe that they may be useful
    // for some people following the emulator101 tutorial and are stuck
#ifdef CPUDIAG
    if (addr == 0x0005) {
        puts("---------------------------------");
        if (state->c == 9) {
            uint16_t offset = (state->d << 8) | state->e;
            // skip the prefix bytes
            char *str = (char *)&state->memory[offset+3];
            printf("[prefix] 0x%02x%02x%02x\n",
                    (uint8_t)str[-3],
                    (uint8_t)str[-2],
                    (uint8_t)str[-1]
                  );
            while (*str != '$')
                putchar(*str++);
            putchar('\n');
        }
        puts("---------------------------------\n");
        return 3;
    } else if (addr == 0x0008) {
        exit(0);
    }
#endif
    push(state, ((state->pc+3) & 0xff00) >> 8, (state->pc+3) & 0x00ff);
    state->pc = addr;
    return 0;
}

static unsigned aci(state8080 *state) {
    uint16_t n = state->a + state->memory[state->pc+1] + state->flags.cy;

    check_auxillary(state,
            state->a, state->memory[state->pc+1]+state->flags.cy);
    state->a = n & 0xff;
    set_arthmetic_flags(state, n);
    return 2;
}

static unsigned rnc(state8080 *state) {
    if (!state->flags.cy)
        return ret(state);
    return 1;
}

static unsigned jnc(state8080 *state) {
    if (!state->flags.cy)
        return jmp(state);
    return 3;
}

static unsigned out(state8080 *state) {
    // TODO
    printf("OUT TODO\n");
    return 2;
}

static unsigned cnc(state8080 *state) {
    if (!state->flags.cy)
        return call(state);
    return 3;
}

static unsigned sui(state8080 *state) {
    uint16_t n = state->a - state->memory[state->pc+1];

    check_auxillary(state, state->a, -state->memory[state->pc+1]);
    state->a = n & 0xff;
    set_arthmetic_flags(state, n);
    return 2;
}

static unsigned rc(state8080 *state) {
    if (state->flags.cy)
        return ret(state);
    return 1;
}

static unsigned jc(state8080 *state) {
    if (state->flags.cy)
        return jmp(state);
    return 3;
}

static unsigned in(state8080 *state) {
    // TODO
    printf("IN TODO\n");
    return 2;
}

static unsigned cc(state8080 *state) {
    if (state->flags.cy)
        return call(state);
    return 3;
}

static unsigned sbi(state8080 *state) {
    uint16_t n = state->a - state->memory[state->pc+1] - state->flags.cy;

    check_auxillary(state,
            state->a, -state->memory[state->pc+1]-state->flags.cy);
    state->a = n & 0xff;
    set_arthmetic_flags(state, n);
    return 2;
}

static unsigned rpo(state8080 *state) {
    if (!state->flags.p)
        return ret(state);
    return 1;
}

static unsigned jpo(state8080 *state) {
    if (!state->flags.p)
        return jmp(state);
    return 3;
}

static unsigned xthl(state8080 *state) {
    uint8_t tmp;

    tmp = state->l;
    state->l = state->memory[state->sp];
    state->memory[state->sp] = tmp;
    tmp = state->h;
    state->h = state->memory[state->sp+1];
    state->memory[state->sp+1] = tmp;
    return 1;
}

static unsigned cpo(state8080 *state) {
    if (!state->flags.p)
        return call(state);
    return 3;
}

static unsigned ani(state8080 *state) {
    state->a &= state->memory[state->pc+1];
    set_arthmetic_flags(state, state->a);
    return 2;
}

static unsigned rpe(state8080 *state) {
    if (state->flags.p)
        return ret(state);
    return 1;
}

static unsigned pchl(state8080 *state) {
    state->pc = state->l | (state->h << 8);
    return 0;
}

static unsigned jpe(state8080 *state) {
    if (state->flags.p)
        return jmp(state);
    return 3;
}

static unsigned xchg(state8080 *state) {
    uint8_t tmp;

    tmp = state->h;
    state->h = state->d;
    state->d = tmp;
    tmp = state->l;
    state->l = state->e;
    state->e = tmp;
    return 1;
}

static unsigned cpe(state8080 *state) {
    if (state->flags.p)
        return call(state);
    return 3;
}

static unsigned xri(state8080 *state) {
    state->a ^= state->memory[state->pc+1];
    set_arthmetic_flags(state, state->a);
    return 2;
}

static unsigned rp(state8080 *state) {
    if (!state->flags.s)
        return ret(state);
    return 1;
}

static unsigned jp(state8080 *state) {
    if (!state->flags.s)
        return jmp(state);
    return 3;
}

static unsigned di(state8080 *state) {
    state->int_enable = false;
    return 1;
}

static unsigned cp(state8080 *state) {
    if (!state->flags.s)
        return call(state);
    return 3;
}

static unsigned ori(state8080 *state) {
    uint16_t n = (uint16_t)state->a | (uint16_t)state->memory[state->pc+1];

    state->a = n & 0xff;
    set_arthmetic_flags(state, n);
    return 2;
}

static unsigned rm(state8080 *state) {
    if (state->flags.s)
        return ret(state);
    return 1;
}

static unsigned sphl(state8080 *state) {
    state->sp = state->l | (state->h << 8);
    return 1;
}

static unsigned jm(state8080 *state) {
    if (state->flags.s)
        return jmp(state);
    return 3;
}

static unsigned ei(state8080 *state) {
    state->int_enable = true;
    return 1;
}

static unsigned cm(state8080 *state) {
    if (state->flags.s)
        return call(state);
    return 3;
}

static unsigned cpi(state8080 *state) {
    uint16_t n;

    check_auxillary(state, state->a, -state->memory[state->pc+1]);
    n = (uint16_t)state->a - (uint16_t)state->memory[state->pc+1];
    set_arthmetic_flags(state, n);
    return 2;
}

static void set_arthmetic_flags(state8080 *state, uint16_t n) {
    state->flags.z = (n & 0xff) == 0;
    state->flags.s = (n & 0x80) != 0;
    state->flags.p = check_parity((uint8_t)(n & 0xff));
    state->flags.cy = n > (n & 0xff);
}

static bool check_parity(uint8_t n) {
    int parity = 0;

    while (n) {
        if (n & 0x1)
            ++parity;
        n >>= 1;
    }
    return parity % 2 == 0;
}

static bool check_auxillary(state8080 *state, uint8_t reg0, uint8_t reg1) {
    state->flags.ac = ((reg0 & 0xf) + (reg1 & 0xf)) > 0xf;
    return true;
}

static void unimplemented_inst(state8080 *state) {
    char buf[1024];

    sprint_inst(state->memory, state->pc, buf);
    fprintf(stderr, "unimplemented instruction:\n%s\n", buf);
    exit(1);
}
