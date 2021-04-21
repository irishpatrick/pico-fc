#include "receiver.h"
#include "imu.h"
#include "bar.h"
#include "pico_servo.h"

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include <stdio.h>

static receiver rx;
static imu agm;
static barometer alt;
static int dir = 1;
static int angle = 0;

int main()
{
    stdio_init_all();

    int err;

    servo_init();
    servo_clock_auto();
    servo_attach(2);
    
        receiver_init(&rx);
    err = receiver_map_input(&rx, 0, 17);
    if (err > 0)
    {
        panic("BAD INPUT MAPPING");
    }

    receiver_start(&rx);
 
    for (;;)
    {
        servo_move_to(2, angle);
        angle += dir;
        if (angle <= 0 || angle >= 180)
        {
            dir *= -1;
        }
        
        printf("dc: %f\n", rx.duty_cycle[0] * 100.f);
        sleep_ms(4);
    }
    
    return 0;
}
