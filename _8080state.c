#include <stdlib.h>
#include <stdio.h>
#include "_8080state.h"

state8080 *init_8080state(size_t starting_addr) {
    state8080 *state;

    if (!(state = malloc(sizeof(state8080)))) {
        printf("couldn't allocate memory\n");
        return NULL;
    }
    state->sp = state->a = state->b = state->c = state->d =
        state->e = state->h = state->l = 0;
    state->pc = starting_addr;
    state->int_enable = 1;
    if (!(state->memory = malloc(sizeof(uint8_t) * 0x10000))) {
        fprintf(stderr, "couldn't allocate memory\n");
        return NULL;
    }
    return state;
}

void print_state(state8080 *state) {
    printf("current state:\n");
    printf("regs:\n");
    printf("\ta: 0x%1$x\t%1$d\n", (int)state->a);
    printf("\tb: 0x%1$x\t%1$d\n", (int)state->b);
    printf("\tc: 0x%1$x\t%1$d\n", (int)state->c);
    printf("\td: 0x%1$x\t%1$d\n", (int)state->d);
    printf("\te: 0x%1$x\t%1$d\n", (int)state->e);
    printf("\th: 0x%1$x\t%1$d\n", (int)state->h);
    printf("\tl: 0x%1$x\t%1$d\n", (int)state->l);
    printf("\tsp: 0x%1$x\t%1$d\n", (int)state->sp);
    printf("\tpc: 0x%1$x\t%1$d\n", (int)state->pc);
    printf("memory: %p\n", state->memory);
    printf("flags:\n");
    printf("\tz: %d\n", (int)state->flags.z);
    printf("\ts: %d\n", (int)state->flags.s);
    printf("\tp: %d\n", (int)state->flags.p);
    printf("\tcy: %d\n", (int)state->flags.cy);
    printf("\tac: %d\n", (int)state->flags.ac);
    printf("interrupts: %d\n", (int)state->int_enable);
}

size_t map_file(state8080 *state, size_t begin_addr, char *filename) {
    FILE *fp;
    size_t file_size;

    if (!(fp = fopen(filename, "r"))) {
        fprintf(stderr, "couldn't open file\n");
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (file_size + begin_addr > 0xffff) {
        fprintf(stderr, "file is too big\n");
        fclose(fp);
        return 0;
    } 
    if (!fread(&state->memory[begin_addr], file_size, 1, fp)) {
        fprintf(stderr, "couldn't read file\n");
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return file_size;
}
