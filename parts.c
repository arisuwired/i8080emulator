#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "parts.h"
#include "_8080state.h"
#include <SDL2/SDL.h>

static uint8_t in1 = 0, in2 = 0;

/*
 *   Ports:    
 *   Read 1
 *   BIT 0  1  coin (0 when active)
 *       1  2  P2 start button
 *       2  4  P1 start button
 *       3  8  ?    
 *       4 10  P1 shoot button
 *       5 20  P1 joystick left
 *       6 40  P1 joystick right
 *       7 80  ?
 *
 *   Read 2
 *   BIT 0,1 1,2 dipswitch number of lives (0:3,1:4,2:5,3:6)
 *       2     4 tilt 'button'
 *       3     8 dipswitch bonus life at 1:1000,0:1500
 *       4    10 P2 shoot button
 *       5    20 P2 joystick left
 *       6    40 P2 joystick right
 *       7    80 dipswitch coin info 1:off,0:on
 */

void buttons(SDL_Event *e) {
    //printf("%x %x\n", in1, in2);
    uint8_t (*action)(uint8_t cur_state, uint8_t bit);

    if (e->type == SDL_KEYDOWN) {
        action = press_button;
    } else if (e->type == SDL_KEYUP) {
        action = unpress_button;
    } else {
        return;
    }

    switch (e->key.keysym.sym) {
        case SDLK_LEFT:
            in1 = action(in1, 0x20);
            break;
        case SDLK_RIGHT:
            in1 = action(in1, 0x40);
            break;
        case SDLK_UP:
            in1 = action(in1, 0x10);
            break;
        case SDLK_DOWN:
            in1 = action(in1, 0x04);
            break;

        case SDLK_a:
            in2 = action(in2, 0x20);
            break;
        case SDLK_d:
            in2 = action(in2, 0x40);
            break;
        case SDLK_w:
            in2 = action(in2, 0x10);
            break;
        case SDLK_s:
            in1 = action(in1, 0x02);
            break;

        // coin
        case SDLK_1:
            in1 = action(in1, 0x01);
            break;
        // dipswitch number 1
        case SDLK_2:
            in2 = action(in2, 0x01);
            break;
        // dipswitch number 2
        case SDLK_3:
            in2 = action(in2, 0x02);
            break;
        // tilt
        case SDLK_4:
            in2 = action(in2, 0x04);
            break;
        // dipswitch bonus
        case SDLK_5:
            in2 = action(in2, 0x08);
            break;
        // dipswitch coin
        case SDLK_6:
            in2 = action(in2, 0x80);
            break;

        default:
            break;
    }
}

uint8_t press_button(uint8_t cur_state, uint8_t bit) {
    return cur_state | bit;
}

uint8_t unpress_button(uint8_t cur_state, uint8_t bit) {
    return cur_state & (~0 ^ bit);
}

static uint16_t shift_register = 0;
static uint8_t shift_offset = 0;

uint8_t machine_in(state8080 *state, uint8_t port) {
    //printf("in %d\n", port);
    uint8_t ret;

    switch (port) {
        case 1:
            ret = in1;
            break;
        case 2:
            ret = in2;
            break;
        case 3:
            //printf("before: %x >> %x\t", shift_register, (8-shift_offset));
            ret = (shift_register >> (8-shift_offset)) & 0xff;       
            //printf("after: %x\n", ret);
            break;
        default:
            ret = state->a;
            printf("%d ??????????????????????????????????????????\n", port);
            break;
    }
    return ret;
}

void machine_out(uint8_t port, uint8_t value) {
    //printf("out %d\n", port);
    switch (port) {
        case 2:
            shift_offset = value & 0x7;
            break;
        case 4:
            shift_register = (value << 8) | (shift_register >> 8);
            break;
        default:
            break;
    }
}

static SDL_Window *window;
static SDL_Renderer *renderer;
static int w, h;

void screen_init(int width, int height) {
    w = width;
    h = height;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
            "title",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            0
            );
    if (window == NULL) {
        fprintf(stderr, "couldn't create window. SDL error: %s\n",
                SDL_GetError());
        exit(-1);
    }
    renderer = SDL_CreateRenderer(
            window,
            -1,
            0
            );
    if (renderer == NULL) {
        fprintf(stderr, "couldn't create renderer. SDL error: %s\n",
                SDL_GetError());
        screen_exit();
        exit(-2);
    }
}

void screen_draw(uint8_t *src) {
    uint8_t byte;
    int y, x;
    x = y = 0;

    for (int i = 0; i < w*h/8; ++i) {
        byte = *(src++);
        for (int j = 0; j < 8; ++j) {
            if (byte & 1)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            else
                SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
            byte >>= 1;
            SDL_RenderDrawPoint(renderer, x, h-y);
            if (++y >= h) {
                y = 0;
                x++;
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void screen_exit(void) {
    if (window != NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
}
