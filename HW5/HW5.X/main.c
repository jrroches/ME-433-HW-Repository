#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "i2c_master_noint.h"
#include "ssd1306.h"
#include "ws2812b.h"
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
    
    char str[50];
    sprintf(str,"NeoPixels Project");
    drawString(0,8,str);
    ssd1306_update();
    
    //Init ws2812b
    ws2812b_setup();
    
    wsColor colorArray[4];
    colorArray[0]=HSBtoRGB(0,1,1);
    colorArray[1]=HSBtoRGB(60,1,1);
    colorArray[2]=HSBtoRGB(120,1,1);
    colorArray[3]=HSBtoRGB(240,1,1);
    ws2812b_setColor(colorArray,4);
    
    int LED1 = 0;
    int LED2 = 1;
    int LED3 = 2;
    int LED4 = 3;
    
    wsColor waveformArray[4];
    
    


    __builtin_enable_interrupts();

    while (1) {
        // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
        // remember the core timer runs at half the sysclk
        
//        //Heartbeat
//        LATASET = 0x10;
//        _CP0_SET_COUNT(0);
//        while(_CP0_GET_COUNT()<(12000000)){}
//        LATACLR = 0x10;
//        _CP0_SET_COUNT(0);
//        while(_CP0_GET_COUNT()<(12000000)){}
          
        //Waveforms
        if (LED1 == 4){
            LED1 = 0;
        }
        if (LED2 == 4){
            LED2=0;
        }
        if (LED3 == 4){
            LED3=0;
        }
        if (LED4 == 4){
            LED4=0;
        }
        
        waveformArray[0] = colorArray[LED1];
        waveformArray[1] = colorArray[LED2];
        waveformArray[2] = colorArray[LED3];
        waveformArray[3] = colorArray[LED4];
        ws2812b_setColor(waveformArray,4);
        
        LED1++;
        LED2++;
        LED3++;
        LED4++;
        
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT()<(1500000)){}

    }
}
