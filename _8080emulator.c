#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "_8080emulator.h"
#include "_8080state.h"
#include "parts.h"
#include "timer.h"
#include "interrupts.h"

#define WIDTH 224
#define HEIGHT 256

int main(int argc, char *argv[]) {
    SDL_Event *e;
    state8080 *state;
    size_t current_addr = 0;
    size_t file_size;
    uint8_t opcode, port;
    int steps = 0;
    char buf[1024];
    char c;
    char *debug = getenv("DEBUG");
    int cycles = 0, cycles_before = 0;
    int interrupt = 1;
    long double current_time;
    long double time_after;
    bool quit = false;


    if (!(state = init_8080state(atoi(*++argv)))) {
        exit(-1);
    }
    --argc;
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
    state->sp = 0x2400;
    state->int_enable = 1;

    e = malloc(sizeof(SDL_Event));
    screen_init(WIDTH, HEIGHT);
    while (!quit) {
        cycles_before = cycles;
        if (debug) {
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
        }
        current_time = time_us();

        opcode = state->memory[state->pc];
        if (opcode == OPCODE_IN_D8) {
            port = state->memory[state->pc+1]; state->a = machine_in(state, port); state->pc += 2;
            cycles += 3;
        } else if (opcode == OPCODE_OUT_D8) {
            port = state->memory[state->pc+1];
            machine_out(port, state->a);
            state->pc += 2;
            cycles += 3;
        } else {
            cycles += emulate8080_inst(state);
        }

        time_after = current_time + cycles2us(2, cycles-(cycles_before*1.5));
        while (current_time < time_after) {
            current_time = time_us();
        }

#ifndef CPUDIAG
        if (debug) {
            printf("cycles: %d / %d\n", cycles, (int)us2cycles(2, 8000));
        }
        if ((cycles > us2cycles(2, 8000)) && state->int_enable) {
            state->int_enable = 0;
            if (interrupt == 1) {
                //printf("ISR 1 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                generate_interrupt(state, 1);
                interrupt = 2;
            } else {
                //printf("ISR 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                generate_interrupt(state, 2);
                interrupt = 1;
                screen_draw(&state->memory[0x2400]);
            }
            cycles = 0;
        }

        if (state->pc == 0x87) {
            //printf("ISR Q !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
        if ((state->sp < 0x2000) || state->sp > 0x4000)    
               printf("rip stack %04x\n", state->sp);    
#endif
        if (debug) {
            continue;
        }
        while (SDL_PollEvent(e)) {
            if (e->type == SDL_QUIT) {
                quit = true;
            } else {
                buttons(e);
            }
        }
    }
    screen_exit();
    return 0;
}
