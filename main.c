#include "msp.h"
#include "keypad.h"
#include "delay.h"
#include "timerA.h"
#include "array.h"
#include "spi_DAC.h"

/**
 * main.c
 */
uint8_t freq = 1;// to change freq
signed int duty = 0;
uint16_t sin_table[200];//w
uint16_t sawtooth_table[200];//x
uint16_t triangle_table[200];//y
uint16_t square_table[200];//z
uint16_t array[200];

unsigned char key;
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    uint16_t i =0;
    make_arrays();
    spi_init();
    timerA_init();
    keypad_init();
    make_arrays();
    key = keypad_getkey();

    while(1){
        while(key==13){key = keypad_getkey();}

        if(key==1){
            freq=1;
            key = keypad_getkey();
        }
        if(key==2){
            freq=2;
            key = keypad_getkey();
        }
        if(key==3){
            freq=3;
            key = keypad_getkey();
        }
        if(key==4){
            freq=4;
            key = keypad_getkey();
        }
        if(key==5){
            freq=5;
            key = keypad_getkey();
        }

        if(key==6){//star button
            triangle_table[0]=0;
            for(i=0; i<200; i++){
                array[i] = triangle_table[i];
            }
            key = keypad_getkey();
        }

        if(key==7){
            sin_table[0]=2009;
            for(i=0; i<200; i++){
                array[i] = sin_table[i];
            }
            key = keypad_getkey();
        }

        if(key==8){
            for(i=0; i<200; i++){
                array[i] = square_table[i];
            }
            key = keypad_getkey();
        }

        if(key==9){
            for(i=0; i<200; i++){
                array[i] = sawtooth_table[i];
            }
            key = keypad_getkey();
        }

        if(key==10){//star
            duty +=10;
            if(duty>=90){duty=90;}
            make_square_table(duty);
            for(i=0; i<200; i++){
                array[i] = square_table[i];
            }
            key = keypad_getkey();
        }

        if(key==0){//
            duty =0;
            make_square_table(duty);
            for(i=0; i<200; i++){
                array[i] = square_table[i];
            }
            key = keypad_getkey();
        }

        if(key==12){//hash
            duty -=10;
            if(duty<=-90){duty=-90;}
            make_square_table(duty);
            for(i=0; i<200; i++){
                array[i] = square_table[i];
            }
            key = keypad_getkey();
        }

        while(keypad_getkey()!=13){delay_ms(1);}

    }//while
}//main



// Timer A0_0 interrupt service routine
void TA0_0_IRQHandler(void) {
    static uint16_t j;
    if (j>=200){j =0;}//reset i after 200
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;  // Clear the CCR0 interrupt
    spi_send(array[j]);
    j+=freq; // sampling every j
    P1->OUT ^= BIT0; // toggle led 1

}



