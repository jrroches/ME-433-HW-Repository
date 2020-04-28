
#include "mcp23017.h"

void mcp23017Init(void){
    
    //Set A Bank to all outputs
    writeMCP23017(MCP23017_ADDRESS,IODIRA,0x00);
    //Set A Bank level to low
    writeMCP23017(MCP23017_ADDRESS,OLATA,0x00);
    
    //Set B Bank to all outputs
    writeMCP23017(MCP23017_ADDRESS,IODIRB,0xFF);
}

void writeMCP23017(unsigned char address, unsigned char reg, unsigned char value){
    unsigned char write_address= (address | 0x00);
    i2c_master_start();
    i2c_master_send(write_address);
    i2c_master_send(reg);
    i2c_master_send(value);
    i2c_master_stop();
    
}

unsigned char readMCP23017(unsigned char address, unsigned char reg){
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

int readGPIO(int gpio, int bank){
    unsigned char reg;
    unsigned char reg_data;
    
    if (bank==0){
        reg = GPIOA;
    } else if (bank==1){
        reg = GPIOB;
    }
    
    reg_data = readMCP23017(MCP23017_ADDRESS, reg);
    int value = (reg_data & (1<<gpio))>>gpio;
    return value;   
}

void writeGPIO(int gpio, int bank, int level){
    unsigned char reg;
    unsigned char reg_data;
    
    if (bank==0){
        reg = OLATA;
    } else if (bank==1){
        reg = OLATB;
    }
    
    reg_data = (0x00 | level<<gpio);
    writeMCP23017(MCP23017_ADDRESS,reg,reg_data);
}

