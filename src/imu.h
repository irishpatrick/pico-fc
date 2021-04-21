#ifndef IMU_H
#define IMU_H

typedef struct _imu
{
    float accel[3];
    float omega[3];
    float quat[4];
    float compass[3];
} imu;

int imu_init(imu*);
int imu_poll(imu*);

#endif /* IMU_h */
