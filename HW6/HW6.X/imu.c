#include "imu.h"

void imu_setup(){
    unsigned char who = 0;
    
    //Setup necessary parameters
    unsigned char data_CTRL1_XL = 0b10000010;
    unsigned char data_CTRL2_G = 0b10001000;
    unsigned char data_CTRL3_C = 0b00000100;

    // read from IMU_WHOAMI
    who = imu_read_single(IMU_ADDR , IMU_WHOAMI);
    
    if (who != 0b01101001){
        while(1){}
        //Indicate Power Reset
        LATASET = 0x10;
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT()<(12000000)){}
        LATACLR = 0x10;
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT()<(12000000)){}
    }

    // init IMU_CTRL1_XL
    imu_write_single(IMU_ADDR,IMU_CTRL1_XL,data_CTRL1_XL);
    // init IMU_CTRL2_G
    imu_write_single(IMU_ADDR,IMU_CTRL2_G,data_CTRL2_G);
    // init IMU_CTRL3_C
    imu_write_single(IMU_ADDR,IMU_CTRL3_C,data_CTRL3_C);
}

void imu_read(unsigned char reg, signed short * data, int len){
    
    // read multiple from the imu, each data takes 2 reads so you need len*2 chars
    int byte_num = 2 * len; //calculate size needed for unsigned char array
    unsigned char data_array[byte_num];
    int i;
    
    i2c_read_multiple(IMU_ADDR,reg, data_array, byte_num);
    
    // turn the chars into the shorts
    for (i=0; i < len; i++){
        signed short low_byte = data_array[(i*2)];
        signed short high_byte = data_array[(i*2)+1];
        signed short dummy = (high_byte<<8)|low_byte;
        data[i] = dummy;
    }
}

unsigned char imu_read_single(unsigned char address, unsigned char reg){
    unsigned char write_address= (address | 0x00);
    unsigned char read_address= (address | 0x01);
    unsigned char response;
    i2c_master_start();
    i2c_master_send(write_address);
    i2c_master_send(reg);
    i2c_master_restart();
    i2c_master_send(read_address);
    response = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    
    return response;    
}

void imu_write_single(unsigned char address, unsigned char reg, unsigned char value){
    unsigned char write_address= (address | 0x00);
    i2c_master_start();
    i2c_master_send(write_address);
    i2c_master_send(reg);
    i2c_master_send(value);
    i2c_master_stop();
    
}