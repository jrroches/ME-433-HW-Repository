#ifndef IMU_H__
#define IMU_H__

#include<xc.h> // processor SFR definitions

#define IMU_WHOAMI 0x0F
#define IMU_ADDR 0b11010110
#define IMU_CTRL1_XL 0x10
#define IMU_CTRL2_G 0x11
#define IMU_CTRL3_C 0x12
#define IMU_OUT_TEMP_L 0x20

void imu_setup();
void imu_read(unsigned char, signed short *, int);

//For reading and writing to one memory byte at a time
unsigned char imu_read_single(unsigned char address, unsigned char reg);
void imu_write_single(unsigned char address, unsigned char reg, unsigned char value);

#endif