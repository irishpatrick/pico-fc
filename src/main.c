#include "receiver.h"

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include <stdio.h>

static receiver rx;

int main()
{
    stdio_init_all();

    int err;

    receiver_init(&rx);
    err = receiver_map_input(&rx, 0, 15);
    if (err > 0)
    {
        panic("BAD INPUT MAPPING");
    }

    receiver_start(&rx);
 
    for (;;)
    {
        printf("%f\n", rx.duty_cycle[0] * 100.f);
        has_timer_fired();
        sleep_ms(20);
    }
    
    return 0;
}
