#ifndef INTERRUPTS
#define INTERRUPTS

void generate_interrupt(state8080 *state, int interrupt_num);
long long time_ms(void);

#endif
