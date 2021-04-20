#include "receiver.h"
#include "pico_servo.h"

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include <stdio.h>

static receiver rx;
static int dir = 1;
static int angle = 0;

int main()
{
    stdio_init_all();

    int err;

    servo_init();
    servo_clock_auto();
    //servo_attach(28);
    servo_attach(2);
    
    /*uint slice_num = pwm_gpio_to_slice_num(17);
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, 100);
    pwm_init(slice_num, &cfg, false);
    gpio_set_function(17, GPIO_FUNC_PWM);*/

    
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
        //servo_move_to(28, angle);
        angle += dir;
        if (angle <= 0 || angle >= 180)
        {
            dir *= -1;
        }
        
        printf("dc: %f\n", rx.duty_cycle[0] * 100.f);
        //printf("%f\n", measure_duty_cycle(17) * 100.f);
        sleep_ms(4);
    }
    
    return 0;
}
