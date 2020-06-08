#ifndef PARTS_H
#define PARTS_H

#include <SDL2/SDL.h>
#include <stdint.h>
#include "_8080state.h"

uint8_t machine_in(state8080 *state, uint8_t port);
void machine_out(uint8_t port, uint8_t value);
void screen_init(int width, int height);
void screen_draw(uint8_t *src);
void screen_exit(void);
void buttons(SDL_Event *e);
uint8_t press_button(uint8_t cur_state, uint8_t bit);
uint8_t unpress_button(uint8_t cur_state, uint8_t bit);

#endif
