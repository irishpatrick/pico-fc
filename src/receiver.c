#include "receiver.h"

#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include <stdio.h>

#define COUNT_INTERVAL 20
#define COUNT_CLKDIV 1000

static struct repeating_timer measure_timer;

static bool measure_callback(repeating_timer_t* rt)
{
    receiver* rx = (receiver*)rt->user_data;

    float counting_rate = clock_get_hz(clk_sys) / COUNT_CLKDIV;
    float max_possible_count = counting_rate * COUNT_INTERVAL / 1000.0;

    for (int i = 0; i < rx->n_channels; ++i)
    {
        pwm_set_enabled(pwm_gpio_to_slice_num(rx->pin_map[i]), false);
        rx->duty_cycle[i] = pwm_get_counter(pwm_gpio_to_slice_num(rx->pin_map[i])) / max_possible_count;
        pwm_set_counter(pwm_gpio_to_slice_num(rx->pin_map[i]), 0);
    }

    for (int i = 0; i < rx->n_channels; ++i)
    {
        pwm_set_enabled(pwm_gpio_to_slice_num(rx->pin_map[i]), true);
    }

    return true;    
}

void receiver_init(receiver* rx)
{
    for (int i = 0; i < MAX_N_INPUTS; ++i)
    {
        rx->pin_map[i] = -1;
        rx->duty_cycle[i] = 0.f;
    }

    rx->n_channels = 0;
}

int receiver_map_input(receiver* rx, uint chan_num, uint pin)
{
    if (rx->n_channels >= MAX_N_INPUTS)
    {
        return 1;
    }

    if (rx->pin_map[rx->n_channels] > -1)
    {
        return 1;
    }

    if (pwm_gpio_to_channel(pin) != PWM_CHAN_B)
    {
        return 1;
    }

    uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, COUNT_CLKDIV);
    pwm_init(slice_num, &cfg, false);
    gpio_set_function(pin, GPIO_FUNC_PWM);

    rx->pin_map[chan_num] = pin;

    ++rx->n_channels;

    return 0;
}

int receiver_start(receiver* rx)
{
    for (int i = 0; i < rx->n_channels; ++i)
    {
        pwm_set_enabled(pwm_gpio_to_slice_num(rx->pin_map[i]), true);
    }
    
    add_repeating_timer_ms(-COUNT_INTERVAL, measure_callback, (void*)rx, &measure_timer);

    return 0;
}
