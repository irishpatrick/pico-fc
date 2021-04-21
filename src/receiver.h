#ifndef RECEIVER_H
#define RECEIVER_H

#include "pico/stdlib.h"

#define MAX_N_INPUTS 8

typedef struct _receiver
{
    uint n_channels;
    int pin_map[MAX_N_INPUTS];
    volatile float duty_cycle[MAX_N_INPUTS];
} receiver;

void receiver_init(receiver*);
int receiver_map_input(receiver*, uint, uint);
int receiver_start(receiver*);

#endif /* RECEIVER_H */
