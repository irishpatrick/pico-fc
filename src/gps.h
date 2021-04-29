#ifndef GPS_H
#define GPS_H

#include <stdint.h>

typedef struct _gps
{
    float lon;
    float lat;
    float alt;
    float spd;
    float head;

    uint8_t n_sats;

    uint8_t hr;
    uint8_t min;
    uint8_t sec;
    uint16_t ms;
    uint8_t year;
    uint8_t month;
    uint8_t day;
} gps;

int gps_init(gps*);

#endif /* GPS_H */