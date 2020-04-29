#include "utilities.h"

void delay_millis(int time){
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<((24000000*time)/1000)){}
}
void delay_s(int time){ 
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<(24000000*time)){}
}