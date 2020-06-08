#ifndef TIMER_H
#define TIMER_H

long double time_us(void);
long double us2cycles(long double mhz, long double us);
long double cycles2us(long double mhz, long double cycles);

#endif
