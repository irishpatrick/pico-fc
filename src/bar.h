#ifndef BAR_H
#define BAR_H

typedef struct _barometer
{
    float alt;
    float pres;
    float temp;
} barometer;

int bar_init(barometer*);
int bar_reset(barometer*);
int bar_poll(barometer*);

#endif /* BAR_H */
