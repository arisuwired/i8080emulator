#ifndef _8080EMULATOR
#define _8080EMULATOR

#include <stdbool.h>
#include <stdint.h>
#include "opcodes.h"
#include "_8080state.h"

void emulate8080_inst(state8080 *state);
int sprint_inst(uint8_t *file_memory, size_t i, char *dst);
size_t inst_fmt(
        char *dst,
        size_t offset,
        uint8_t *inst,
        unsigned inst_siz,
        char *fmt,
        ...);

#endif
