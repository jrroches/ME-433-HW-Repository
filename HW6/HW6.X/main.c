#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "i2c_master_noint.h"
#include "ssd1306.h"
#include "imu.h"
#include "font.h"
#include <stdio.h>



// DEVCFG0
#pragma config DEBUG = OFF // disable debugging
#pragma config JTAGEN = OFF // disable jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // disable flash write protect
#pragma config BWP = OFF // disable boot write protect
#pragma config CP = OFF // disable code protect

// DEVCFG1
#pragma config FNOSC = PRIPLL // use primary oscillator with pll
#pragma config FSOSCEN = OFF // disable secondary oscillator
#pragma config IESO = OFF // disable switching clocks
#pragma config POSCMOD = HS // high speed crystal mode
#pragma config OSCIOFNC = OFF // disable clock output
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // disable clock switch and FSCM
#pragma config WDTPS = PS1048576 // use largest wdt
#pragma config WINDIS = OFF // use non-window mode wdt
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations


int main() {
    
    

    __builtin_disable_interrupts(); // disable interrupts while initializing things

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    // do your TRIS and LAT commands here
    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 0;
    
    //Init 12C
    i2c_master_setup();
    
    //Init ssd1306
    ssd1306_setup();
    ssd1306_clear();
    ssd1306_update();
    
    //Init imu
    imu_setup();
    
    signed short imu_vals[7];
    signed short t = 0;
    signed short g_x = 0;
    signed short g_y = 0;
    signed short g_z = 0;
    signed short xl_x = 0;
    signed short xl_y = 0;
    signed short xl_z = 0;
    
    char accel_str[50];
    char gyro_str[50];
    char temp_str[50];
    
    //Init Extra Variables

        
    char str4[50];
    sprintf(str4,"IMU Project");
    drawString(0,0,str4);
    ssd1306_update();
    
    
    
    


    __builtin_enable_interrupts();

    while (1) {
        // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
        // remember the core timer runs at half the sysclk
        
        //Heartbeat
        LATAbits.LATA4 = !LATAbits.LATA4;
        _CP0_SET_COUNT(0);
        
        imu_read(IMU_OUT_TEMP_L, imu_vals, 7);
        t = imu_vals[0];
        g_x = imu_vals[1];
        g_y = imu_vals[2];
        g_z = imu_vals[3];
        xl_x = imu_vals[4];
        xl_y = imu_vals[5];
        xl_z = imu_vals[6];
        
        
        if (0){
            ssd1306_update();
            sprintf(accel_str, "a:%6.0d %6.0d %6.0d", xl_x,xl_y,xl_z);
            drawString( 0 , 8, accel_str);
            ssd1306_update();
            sprintf(gyro_str, "g:%6.0d %6.0d %6.0d", g_x,g_y,g_z);
            drawString(0 , 16, gyro_str);
            ssd1306_update();
            sprintf(temp_str, "t:%6.0d", t);
            drawString( 0 , 24,temp_str);
            ssd1306_update();
        } else {
            drawInclinometer(xl_x, xl_y);
            ssd1306_update();
            
            
        }
        
        
        
        while(_CP0_GET_COUNT()<(48000000 / 2 / 20)){}
        ssd1306_clear();
        
          
        

    }
}
