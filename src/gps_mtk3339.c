#include "gps.h"
#include "pico/stdlib.h"
#include "hardware/clocks.h"

static struct repeating_timer poll_timer;

static bool poll_callback(repeating_timer_t* rt)
{

    return true;    
}

int gps_init(gps* g)
{

    add_repeating_timer_ms(-1, poll_callback, (void*)g, &poll_timer);
    return 0;
}