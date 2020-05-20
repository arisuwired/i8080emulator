#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "_8080emulator.h"

int sprint_inst(uint8_t *file_memory, size_t i, char *dst) {
    // tmp variable for instruction arguments
    int arg;
    // length of a single instruction in bytes. can be between 1 and 3
    int inst_len = 1;
    // big ass switch generated with a python script,
    // if you have a slicker idea how to do something like this for every
    // instruction lemme know but I guess in c its nearly impossible
    switch (*(file_memory+i)) {
    case OPCODE_NOP:
        inst_fmt(dst, i, file_memory+i, inst_len, "NOP ");
        break;
    case OPCODE_LXI_B_D16:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "LXI B, $%x", arg);
        break;
    case OPCODE_STAX_B:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "STAX $%x", arg);
        break;
    case OPCODE_INX_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "INX B");
        break;
    case OPCODE_INR_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "INR B");
        break;
    case OPCODE_DCR_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCR B");
        break;
    case OPCODE_MVI_B_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "MVI B, $%x", arg);
        break;
    case OPCODE_RLC:
        inst_fmt(dst, i, file_memory+i, inst_len, "RLC ");
        break;
    case OPCODE_DAD_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "DAD B");
        break;
    case OPCODE_LDAX_B:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "LDAX $%x", arg);
        break;
    case OPCODE_DCX_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCX B");
        break;
    case OPCODE_INR_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "INR C");
        break;
    case OPCODE_DCR_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCR C");
        break;
    case OPCODE_MVI_C_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "MVI C, $%x", arg);
        break;
    case OPCODE_RRC:
        inst_fmt(dst, i, file_memory+i, inst_len, "RRC ");
        break;
    case OPCODE_LXI_D_D16:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "LXI D, $%x", arg);
        break;
    case OPCODE_STAX_D:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "STAX $%x", arg);
        break;
    case OPCODE_INX_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "INX D");
        break;
    case OPCODE_INR_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "INR D");
        break;
    case OPCODE_DCR_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCR D");
        break;
    case OPCODE_MVI_D_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "MVI D, $%x", arg);
        break;
    case OPCODE_RAL:
        inst_fmt(dst, i, file_memory+i, inst_len, "RAL ");
        break;
    case OPCODE_DAD_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "DAD D");
        break;
    case OPCODE_LDAX_D:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "LDAX $%x", arg);
        break;
    case OPCODE_DCX_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCX D");
        break;
    case OPCODE_INR_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "INR E");
        break;
    case OPCODE_DCR_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCR E");
        break;
    case OPCODE_MVI_E_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "MVI E, $%x", arg);
        break;
    case OPCODE_RAR:
        inst_fmt(dst, i, file_memory+i, inst_len, "RAR ");
        break;
    case OPCODE_LXI_H_D16:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "LXI H, $%x", arg);
        break;
    case OPCODE_SHLD:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "SHLD $%x", arg);
        break;
    case OPCODE_INX_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "INX H");
        break;
    case OPCODE_INR_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "INR H");
        break;
    case OPCODE_DCR_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCR H");
        break;
    case OPCODE_MVI_H_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "MVI H, $%x", arg);
        break;
    case OPCODE_DAA:
        inst_fmt(dst, i, file_memory+i, inst_len, "DAA ");
        break;
    case OPCODE_DAD_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "DAD H");
        break;
    case OPCODE_LHLD:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "LHLD $%x", arg);
        break;
    case OPCODE_DCX_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCX H");
        break;
    case OPCODE_INR_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "INR L");
        break;
    case OPCODE_DCR_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCR L");
        break;
    case OPCODE_MVI_L_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "MVI L, $%x", arg);
        break;
    case OPCODE_CMA:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CMA $%x", arg);
        break;
    case OPCODE_LXI_SP_D16:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "LXI SP, $%x", arg);
        break;
    case OPCODE_STA:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "STA $%x", arg);
        break;
    case OPCODE_INX_SP:
        inst_fmt(dst, i, file_memory+i, inst_len, "INX SP");
        break;
    case OPCODE_INR_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "INR M");
        break;
    case OPCODE_DCR_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCR M");
        break;
    case OPCODE_MVI_M_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "MVI M, $%x", arg);
        break;
    case OPCODE_STC:
        inst_fmt(dst, i, file_memory+i, inst_len, "STC ");
        break;
    case OPCODE_DAD_SP:
        inst_fmt(dst, i, file_memory+i, inst_len, "DAD SP");
        break;
    case OPCODE_LDA:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "LDA $%x", arg);
        break;
    case OPCODE_DCX_SP:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCX SP");
        break;
    case OPCODE_INR_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "INR A");
        break;
    case OPCODE_DCR_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "DCR A");
        break;
    case OPCODE_MVI_A_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "MVI A, $%x", arg);
        break;
    case OPCODE_CMC:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CMC $%x", arg);
        break;
    case OPCODE_MOV_B_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV B, B");
        break;
    case OPCODE_MOV_B_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV B, C");
        break;
    case OPCODE_MOV_B_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV B, D");
        break;
    case OPCODE_MOV_B_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV B, E");
        break;
    case OPCODE_MOV_B_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV B, H");
        break;
    case OPCODE_MOV_B_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV B, L");
        break;
    case OPCODE_MOV_B_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV B, M");
        break;
    case OPCODE_MOV_B_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV B, A");
        break;
    case OPCODE_MOV_C_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV C, B");
        break;
    case OPCODE_MOV_C_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV C, C");
        break;
    case OPCODE_MOV_C_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV C, D");
        break;
    case OPCODE_MOV_C_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV C, E");
        break;
    case OPCODE_MOV_C_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV C, H");
        break;
    case OPCODE_MOV_C_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV C, L");
        break;
    case OPCODE_MOV_C_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV C, M");
        break;
    case OPCODE_MOV_C_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV C, A");
        break;
    case OPCODE_MOV_D_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV D, B");
        break;
    case OPCODE_MOV_D_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV D, C");
        break;
    case OPCODE_MOV_D_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV D, D");
        break;
    case OPCODE_MOV_D_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV D, E");
        break;
    case OPCODE_MOV_D_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV D, H");
        break;
    case OPCODE_MOV_D_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV D, L");
        break;
    case OPCODE_MOV_D_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV D, M");
        break;
    case OPCODE_MOV_D_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV D, A");
        break;
    case OPCODE_MOV_E_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV E, B");
        break;
    case OPCODE_MOV_E_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV E, C");
        break;
    case OPCODE_MOV_E_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV E, D");
        break;
    case OPCODE_MOV_E_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV E, E");
        break;
    case OPCODE_MOV_E_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV E, H");
        break;
    case OPCODE_MOV_E_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV E, L");
        break;
    case OPCODE_MOV_E_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV E, M");
        break;
    case OPCODE_MOV_E_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV E, A");
        break;
    case OPCODE_MOV_H_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV H, B");
        break;
    case OPCODE_MOV_H_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV H, C");
        break;
    case OPCODE_MOV_H_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV H, D");
        break;
    case OPCODE_MOV_H_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV H, E");
        break;
    case OPCODE_MOV_H_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV H, H");
        break;
    case OPCODE_MOV_H_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV H, L");
        break;
    case OPCODE_MOV_H_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV H, M");
        break;
    case OPCODE_MOV_H_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV H, A");
        break;
    case OPCODE_MOV_L_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV L, B");
        break;
    case OPCODE_MOV_L_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV L, C");
        break;
    case OPCODE_MOV_L_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV L, D");
        break;
    case OPCODE_MOV_L_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV L, E");
        break;
    case OPCODE_MOV_L_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV L, H");
        break;
    case OPCODE_MOV_L_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV L, L");
        break;
    case OPCODE_MOV_L_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV L, M");
        break;
    case OPCODE_MOV_L_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV L, A");
        break;
    case OPCODE_MOV_M_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV M, B");
        break;
    case OPCODE_MOV_M_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV M, C");
        break;
    case OPCODE_MOV_M_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV M, D");
        break;
    case OPCODE_MOV_M_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV M, E");
        break;
    case OPCODE_MOV_M_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV M, H");
        break;
    case OPCODE_MOV_M_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV M, L");
        break;
    case OPCODE_HLT:
        inst_fmt(dst, i, file_memory+i, inst_len, "HLT ");
        break;
    case OPCODE_MOV_M_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV M, A");
        break;
    case OPCODE_MOV_A_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV A, B");
        break;
    case OPCODE_MOV_A_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV A, C");
        break;
    case OPCODE_MOV_A_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV A, D");
        break;
    case OPCODE_MOV_A_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV A, E");
        break;
    case OPCODE_MOV_A_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV A, H");
        break;
    case OPCODE_MOV_A_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV A, L");
        break;
    case OPCODE_MOV_A_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV A, M");
        break;
    case OPCODE_MOV_A_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "MOV A, A");
        break;
    case OPCODE_ADD_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADD B");
        break;
    case OPCODE_ADD_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADD C");
        break;
    case OPCODE_ADD_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADD D");
        break;
    case OPCODE_ADD_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADD E");
        break;
    case OPCODE_ADD_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADD H");
        break;
    case OPCODE_ADD_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADD L");
        break;
    case OPCODE_ADD_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADD M");
        break;
    case OPCODE_ADD_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADD A");
        break;
    case OPCODE_ADC_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADC B");
        break;
    case OPCODE_ADC_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADC C");
        break;
    case OPCODE_ADC_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADC D");
        break;
    case OPCODE_ADC_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADC E");
        break;
    case OPCODE_ADC_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADC H");
        break;
    case OPCODE_ADC_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADC L");
        break;
    case OPCODE_ADC_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADC M");
        break;
    case OPCODE_ADC_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "ADC A");
        break;
    case OPCODE_SUB_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "SUB B");
        break;
    case OPCODE_SUB_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "SUB C");
        break;
    case OPCODE_SUB_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "SUB D");
        break;
    case OPCODE_SUB_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "SUB E");
        break;
    case OPCODE_SUB_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "SUB H");
        break;
    case OPCODE_SUB_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "SUB L");
        break;
    case OPCODE_SUB_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "SUB M");
        break;
    case OPCODE_SUB_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "SUB A");
        break;
    case OPCODE_SBB_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "SBB B");
        break;
    case OPCODE_SBB_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "SBB C");
        break;
    case OPCODE_SBB_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "SBB D");
        break;
    case OPCODE_SBB_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "SBB E");
        break;
    case OPCODE_SBB_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "SBB H");
        break;
    case OPCODE_SBB_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "SBB L");
        break;
    case OPCODE_SBB_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "SBB M");
        break;
    case OPCODE_SBB_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "SBB A");
        break;
    case OPCODE_ANA_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "ANA B");
        break;
    case OPCODE_ANA_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "ANA C");
        break;
    case OPCODE_ANA_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "ANA D");
        break;
    case OPCODE_ANA_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "ANA E");
        break;
    case OPCODE_ANA_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "ANA H");
        break;
    case OPCODE_ANA_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "ANA L");
        break;
    case OPCODE_ANA_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "ANA M");
        break;
    case OPCODE_ANA_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "ANA A");
        break;
    case OPCODE_XRA_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "XRA B");
        break;
    case OPCODE_XRA_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "XRA C");
        break;
    case OPCODE_XRA_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "XRA D");
        break;
    case OPCODE_XRA_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "XRA E");
        break;
    case OPCODE_XRA_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "XRA H");
        break;
    case OPCODE_XRA_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "XRA L");
        break;
    case OPCODE_XRA_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "XRA M");
        break;
    case OPCODE_XRA_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "XRA A");
        break;
    case OPCODE_ORA_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "ORA B");
        break;
    case OPCODE_ORA_C:
        inst_fmt(dst, i, file_memory+i, inst_len, "ORA C");
        break;
    case OPCODE_ORA_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "ORA D");
        break;
    case OPCODE_ORA_E:
        inst_fmt(dst, i, file_memory+i, inst_len, "ORA E");
        break;
    case OPCODE_ORA_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "ORA H");
        break;
    case OPCODE_ORA_L:
        inst_fmt(dst, i, file_memory+i, inst_len, "ORA L");
        break;
    case OPCODE_ORA_M:
        inst_fmt(dst, i, file_memory+i, inst_len, "ORA M");
        break;
    case OPCODE_ORA_A:
        inst_fmt(dst, i, file_memory+i, inst_len, "ORA A");
        break;
    case OPCODE_CMP_B:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CMP $%x", arg);
        break;
    case OPCODE_CMP_C:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CMP $%x", arg);
        break;
    case OPCODE_CMP_D:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CMP $%x", arg);
        break;
    case OPCODE_CMP_E:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CMP $%x", arg);
        break;
    case OPCODE_CMP_H:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CMP $%x", arg);
        break;
    case OPCODE_CMP_L:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CMP $%x", arg);
        break;
    case OPCODE_CMP_M:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CMP $%x", arg);
        break;
    case OPCODE_CMP_A:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CMP $%x", arg);
        break;
    case OPCODE_RNZ:
        inst_fmt(dst, i, file_memory+i, inst_len, "RNZ ");
        break;
    case OPCODE_POP_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "POP B");
        break;
    case OPCODE_JNZ:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "JNZ $%x", arg);
        break;
    case OPCODE_JMP:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "JMP $%x", arg);
        break;
    case OPCODE_CNZ:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CNZ $%x", arg);
        break;
    case OPCODE_PUSH_B:
        inst_fmt(dst, i, file_memory+i, inst_len, "PUSH B");
        break;
    case OPCODE_ADI_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "ADI $%x", arg);
        break;
    case OPCODE_RST_0:
        inst_fmt(dst, i, file_memory+i, inst_len, "RST 0");
        break;
    case OPCODE_RZ:
        inst_fmt(dst, i, file_memory+i, inst_len, "RZ ");
        break;
    case OPCODE_RET:
        inst_fmt(dst, i, file_memory+i, inst_len, "RET ");
        break;
    case OPCODE_JZ:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "JZ $%x", arg);
        break;
    case OPCODE_CZ:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CZ $%x", arg);
        break;
    case OPCODE_CALL:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CALL $%x", arg);
        break;
    case OPCODE_ACI_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "ACI $%x", arg);
        break;
    case OPCODE_RST_1:
        inst_fmt(dst, i, file_memory+i, inst_len, "RST 1");
        break;
    case OPCODE_RNC:
        inst_fmt(dst, i, file_memory+i, inst_len, "RNC ");
        break;
    case OPCODE_POP_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "POP D");
        break;
    case OPCODE_JNC:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "JNC $%x", arg);
        break;
    case OPCODE_OUT_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "OUT $%x", arg);
        break;
    case OPCODE_CNC:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CNC $%x", arg);
        break;
    case OPCODE_PUSH_D:
        inst_fmt(dst, i, file_memory+i, inst_len, "PUSH D");
        break;
    case OPCODE_SUI_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "SUI $%x", arg);
        break;
    case OPCODE_RST_2:
        inst_fmt(dst, i, file_memory+i, inst_len, "RST 2");
        break;
    case OPCODE_RC:
        inst_fmt(dst, i, file_memory+i, inst_len, "RC ");
        break;
    case OPCODE_JC:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "JC $%x", arg);
        break;
    case OPCODE_IN_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "IN $%x", arg);
        break;
    case OPCODE_CC:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CC $%x", arg);
        break;
    case OPCODE_SBI_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "SBI $%x", arg);
        break;
    case OPCODE_RST_3:
        inst_fmt(dst, i, file_memory+i, inst_len, "RST 3");
        break;
    case OPCODE_RPO:
        inst_fmt(dst, i, file_memory+i, inst_len, "RPO ");
        break;
    case OPCODE_POP_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "POP H");
        break;
    case OPCODE_JPO:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "JPO $%x", arg);
        break;
    case OPCODE_XTHL:
        inst_fmt(dst, i, file_memory+i, inst_len, "XTHL ");
        break;
    case OPCODE_CPO:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CPO $%x", arg);
        break;
    case OPCODE_PUSH_H:
        inst_fmt(dst, i, file_memory+i, inst_len, "PUSH H");
        break;
    case OPCODE_ANI_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "ANI $%x", arg);
        break;
    case OPCODE_RST_4:
        inst_fmt(dst, i, file_memory+i, inst_len, "RST 4");
        break;
    case OPCODE_RPE:
        inst_fmt(dst, i, file_memory+i, inst_len, "RPE ");
        break;
    case OPCODE_PCHL:
        inst_fmt(dst, i, file_memory+i, inst_len, "PCHL ");
        break;
    case OPCODE_JPE:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "JPE $%x", arg);
        break;
    case OPCODE_XCHG:
        inst_fmt(dst, i, file_memory+i, inst_len, "XCHG ");
        break;
    case OPCODE_CPE:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CPE $%x", arg);
        break;
    case OPCODE_XRI_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "XRI $%x", arg);
        break;
    case OPCODE_RST_5:
        inst_fmt(dst, i, file_memory+i, inst_len, "RST 5");
        break;
    case OPCODE_RP:
        inst_fmt(dst, i, file_memory+i, inst_len, "RP ");
        break;
    case OPCODE_POP_PSW:
        inst_fmt(dst, i, file_memory+i, inst_len, "POP PSW");
        break;
    case OPCODE_JP:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "JP $%x", arg);
        break;
    case OPCODE_DI:
        inst_fmt(dst, i, file_memory+i, inst_len, "DI ");
        break;
    case OPCODE_CP:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CP $%x", arg);
        break;
    case OPCODE_PUSH_PSW:
        inst_fmt(dst, i, file_memory+i, inst_len, "PUSH PSW");
        break;
    case OPCODE_ORI_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "ORI $%x", arg);
        break;
    case OPCODE_RST_6:
        inst_fmt(dst, i, file_memory+i, inst_len, "RST 6");
        break;
    case OPCODE_RM:
        inst_fmt(dst, i, file_memory+i, inst_len, "RM ");
        break;
    case OPCODE_SPHL:
        inst_fmt(dst, i, file_memory+i, inst_len, "SPHL ");
        break;
    case OPCODE_JM:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "JM $%x", arg);
        break;
    case OPCODE_EI:
        inst_fmt(dst, i, file_memory+i, inst_len, "EI ");
        break;
    case OPCODE_CM:
        arg = 0;
        inst_len = 3;
        arg = (file_memory+i)[1];
        arg += (file_memory+i)[2] << 8;
        inst_fmt(dst, i, file_memory+i, inst_len, "CM $%x", arg);
        break;
    case OPCODE_CPI_D8:
        arg = 0;
        inst_len = 2;
        arg = (file_memory+i)[1];
        inst_fmt(dst, i, file_memory+i, inst_len, "CPI $%x", arg);
        break;
    case OPCODE_RST_7:
        inst_fmt(dst, i, file_memory+i, inst_len, "RST 7");
        break;
    default:
        inst_fmt(dst, i, file_memory+i, inst_len, "--");
        break;
    }
    return inst_len;
}

size_t inst_fmt(
        char *dst,
        size_t offset,
        uint8_t *inst,
        unsigned inst_siz,
        char *fmt,
        ...) {
    va_list ap;
    size_t written;
    unsigned c;

    va_start(ap, fmt);
    written = sprintf(dst, "%6lx: ", offset);
    while (inst_siz-- > 0) {
        c = (unsigned char)*inst++;
        written += sprintf(dst+written, "%02x", c);
        if (inst_siz > 0)
            written += sprintf(dst+written, " ");
    }
    if (written < 16)
        written += sprintf(dst+written, "\t");
    written += sprintf(dst+written, " |\t");
    written += vsprintf(dst+written, fmt, ap);
    va_end(ap);
    return written;
}
