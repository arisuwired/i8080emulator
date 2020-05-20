#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "_8080emulator.h"
#include "_8080state.h"

int main(int argc, char *argv[]) {
    state8080 *state;
    size_t current_addr = 0;
    size_t file_size;
#ifdef DEBUG
    char buf[1024];
    char c;
    int steps = 0;
#endif

    if (!(state = init_8080state(0x100))) {
        exit(-1);
    }
    while (--argc) {
        if (!(file_size = map_file(state, current_addr, *++argv))) {
            exit(-1);
        }
        current_addr += file_size;
        //printf("%x\n", current_addr);
    }
#if defined(CPUDIAG) && defined(SKIP_SPECIAL)
    // skip DAA tests
    state->memory[0x59c] = 0xc3;
    state->memory[0x59d] = 0xc2;
    state->memory[0x59e] = 0x05;
#endif

    for (;;) {
#ifdef DEBUG
        if (--steps <= 0) {
            print_state(state);
            printf("next instruction: ");
            sprint_inst(state->memory, state->pc, buf);
            printf("%s\n", buf);
            if ((c = getchar()) == '\n') {
                steps = 1;
            } else {
                ungetc(c, stdin);
                if (!scanf("%d", &steps)) {
                    steps = 0;
                }
                // flush buffer
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }
        }
#endif
        emulate8080_inst(state);
    }
    return 0;
} 
