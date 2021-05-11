#include "msp.h"
#include <math.h>

uint8_t w=0;
uint8_t x=0;
uint8_t y=0;
uint8_t z=0;
extern uint16_t sin_table[200];//w
extern uint16_t sawtooth_table[200];//x
extern uint16_t triangle_table[200];//y
extern uint16_t square_table[200];//z

void make_sine_table(void){
    for (w=0; w<=200; w++){
    sin_table[w]= 2000*sin(2*3.14*w/50)+2000;
    }
}

void make_sawtooth_table(void){
    for(x =0; x<=200; x++){
    sawtooth_table[x]=20.4*x;
    }
}
void make_triangle_table(void){
    for(y=0; y<200; y++){
        if(y<=100){
            triangle_table[y] = y*40.95;
        }
        if(y>100){
            triangle_table[y] = y*(-40.95) +4095;
        }
    }
}

void make_square_table(signed int duty_cycle){
    for(z=0; z<=200; z++){
        if(z<100+duty_cycle){
            square_table[z] =0;
        }
        else{
        square_table[z] = 4095;
        }
    }
}

void make_arrays(void){
    make_sine_table();
    make_triangle_table();
    make_sawtooth_table();
    make_square_table(0);

}



