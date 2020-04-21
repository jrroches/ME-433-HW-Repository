#include <proc/p32mx170f256b.h>

#include "waveform.h"
#include<xc.h> 
#include <math.h>

void test_waveform () {
    char msb = 0b01111000;
    char lsb = 0b00000000;
    LATAbits.LATA0 = 0; // Bring CS low
    spi_io(msb); // Send msb
    spi_io(lsb); // Send lsb
    LATAbits.LATA0 = 1; // Bring CS high
}

void output_waveform (char channel, unsigned short waveform_value) {
    char lsb = waveform_value;
    char msb = waveform_value >> 8;
    msb = msb | 0b11110000;
    if (channel == 'A') {
        msb = msb & 0b01111111;
    }
    LATAbits.LATA0 = 0; // Bring CS low
    spi_io(msb); // Send msb
    spi_io(lsb); // Send lsb
    LATAbits.LATA0 = 1; // Bring CS high   
}

void generate_triangle_wave (unsigned short arr[]) {
    int i = 0;
    double increment = 4096/500;
    double voltage_scaler = 0;
    for (i; i < 500; i++) {
        arr[i] = (unsigned int)voltage_scaler;
        voltage_scaler += increment;
    }
    for (i; i < 1000; i++) {
        voltage_scaler -= increment;
        arr[i] = (unsigned int)voltage_scaler;
    }
}

void generate_sine_wave (unsigned short arr[]) {
    int i = 0;
    unsigned short voltage_scaler = 0;
    double increment = 2*M_PI/500;
    for (i; i < 500; i++) {
        voltage_scaler = (unsigned int)(((sin(increment*i)*.5) + .5)*4095);
        arr[i] = voltage_scaler;
    }
}

void delay_ms (unsigned int t) {
     _CP0_SET_COUNT(0);
     while (_CP0_GET_COUNT() < (24000*t)) {
            
        }
}