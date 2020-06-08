#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "_8080emulator.h"

#define MAX_SIZE 128

static unsigned push(state8080 *state, uint8_t reg0, uint8_t reg1) {
    // copy pasted push instruction code
    // this is ad hoc need to rewrite much
    state->memory[state->sp-2] = reg1;
    state->memory[state->sp-1] = reg0;
    state->sp -= 2;
    return 1;
}

void generate_interrupt(state8080 *state, int interrupt_num) {
    // copy pasted rst instruction code
    // this is ad hoc need to rewrite much
    push(state, ((state->pc) & 0xff00) >> 8, (state->pc) & 0x00ff);
    state->pc = 8 * interrupt_num;
    state->int_enable = 0;
}

long long time_ms(void) {
    struct timespec t;

    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_nsec / 1000000 + t.tv_sec * 1000;
}
