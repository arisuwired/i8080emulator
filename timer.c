#include <time.h>

long double time_us(void) {
    struct timespec t;

    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_nsec / 1000 + t.tv_sec * 1000000;
}

long double us2cycles(long double mhz, long double us) {
    return us / mhz;
}

long double cycles2us(long double mhz, long double cycles) {
    return mhz * cycles;
}

// for testing

/*
#include <stdio.h>
int main() {
    long double cur = time_us();
    printf("%llf\n", cur);
    printf("%llf\n", us2cycles(2, 8000));
    printf("%llf\n", cycles2us(2, 1));
    return 0;
}
*/
