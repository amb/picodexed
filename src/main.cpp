#include <stdio.h>

#include <cstdio>

#include "arm_math.h"
#include "pico/stdlib.h"
#include "picodexed.h"

#define POLYPHONY 8

CPicoDexed picoDexed;

int main(void) {
    // Overclock the Pico to 250MHz instead of the default 133MHz.
    // I have it on good authority (read, my Mastodon follows)
    // that this is an ok thing to do.  So there.
#if DEXED_OVERCLOCK == 1
    set_sys_clock_khz(250000, false);
#endif

    stdio_init_all();
    fprintf(stderr, "PicoDexed %s ...\n", PICODEXED_VERSION);
    fprintf(stderr, "\nConfiguration:\n");
    fprintf(stderr, "  Sample Rate:  %d\n", DEXED_SAMPLE_RATE);
    fprintf(stderr, "  Polyphony:    %d\n", DEXED_POLYPHONY);
#if DEXED_OVERCLOCK == 1
    fprintf(stderr, "  Overclocking: On\n");
#else
    fprintf(stderr, "  Overclocking: Off\n");
#endif

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    sleep_ms(500);

    picoDexed.Init();

    gpio_put(PICO_DEFAULT_LED_PIN, 0);

    while(1) {
        picoDexed.Process();
    }

    return 0;
}
