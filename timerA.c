/*
 * timerA.c
 *
 *  Created on: May 4, 2021
 *      Author: William
 */


#include "msp.h"

void timerA_init(void){

    P1->DIR |= BIT0;    // setup P1.0 and P2.0 LEDs
    P2->DIR |= BIT0;

    P1->OUT &= ~BIT0;   // turn LEDs off
    P2->OUT &= ~BIT0;

    // setup TIMER_A0
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear interrupt
    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG; // clear interrupt

    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_CCIE; // TACCR1 interrupt enabled

    TIMER_A0->CCR[0] = 5;   // set CCR0 count
    TIMER_A0->CCR[1] = 16384;   // set CCR1 count

    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_1 | TIMER_A_CTL_MC_1; // SMCLK, UP mode

    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);   // set NVIC interrupt
    NVIC->ISER[0] = 1 << ((TA0_N_IRQn) & 31);   // TA0_0 and TA0_N

    __enable_irq();     // Enable global interrupt

}
