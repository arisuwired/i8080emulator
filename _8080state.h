#ifndef _8080STATE
#define _8080STATE

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t z:1;
    uint8_t s:1;
    uint8_t p:1;
    uint8_t cy:1;
    uint8_t ac:1;
    uint8_t pad[3];
} condition_flags;

typedef struct {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    uint8_t *memory;
    condition_flags flags;
    bool int_enable;
} state8080;

state8080 *init_8080state(size_t starting_addr);

void print_state(state8080 *state);
size_t map_file(state8080 *state, size_t begin_addr, char *filename);

#endif
