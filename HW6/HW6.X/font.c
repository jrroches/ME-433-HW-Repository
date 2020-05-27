#include "font.h"
#include "ssd1306.h"


void drawChar(unsigned char x, unsigned char y, char ascii){// x,y specify top left corner
    int index = ascii - 0x20;
    int x_rel;
    int y_rel;
    int i=0;
    int j=0;
    
    for (i=0; i<5 ;i++){
        for (j=0; j<8 ;j++){
            unsigned char data = ASCII[index][i];
            x_rel= x + i;
            y_rel= y+j;
            int val = ((data & (1<<j)) >> j);
            ssd1306_drawPixel(x_rel,y_rel,val);
        }  
    }   
}

void drawString(unsigned char s_x, unsigned char s_y, char* str){
    int x_pos=s_x;
    int y_pos=s_y;
    int counter=0;
    
    while(str[counter]!=0){
        drawChar(x_pos,y_pos,str[counter]);
        x_pos+=5;
        counter++;
    
    }
    



}

void drawInclinometer(signed short x, signed short y) {
    signed short x_norm = y/250;
    signed short y_norm = x/1063;
    unsigned char counter = 0;
    if (x_norm < 0) {
        x_norm = -x_norm;
        for (counter; counter < x_norm; counter++) {
            drawChar(counter + 64, 16, '.');
        }
    }
    else {
        for (counter; counter < x_norm; counter++) {
            drawChar(64 - counter, 16, '.');
        }
    }
    if (y_norm < 0) {
        counter = 0;
        y_norm = -y_norm;
        for (counter; counter < y_norm; counter++) {
            drawChar(64, 16 - counter, '.');
        }
    }
    else {
        counter = 0;
        for (counter; counter < y_norm; counter++) {
            drawChar(64, counter + 16, '.');
        }
    }
}