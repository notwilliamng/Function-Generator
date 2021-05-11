/*
 * delay.c
 *
 *  Created on: Apr 12, 2021
 *      Author: William
 */
#include "msp.h"
#include "delay.h"
void delay_ms(uint32_t delay){
    uint32_t i; //counter
    for(i=0; i<(delay << 6); i++);
}

void delay_us(uint32_t delay){
    uint32_t i; //counter
    for(i=0; i<(delay << 3); i++);
}


