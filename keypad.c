#include "msp.h"
#include "keypad.h"


void keypad_init(void){
    //7 pins, 4 rows + 3 cols;
        //set rows input, DIR =0
        P4 -> DIR &= ~(row_mask);//r0,r1,r2,r3
        //cols output, DIR =1
        P6 -> DIR |= (col_mask);//c0,c1,c2
        //enable pulldown resistors on Rows, REN =1, OUT =0
        P4 -> REN |= (row_mask);//r0,r1,r2,r3
        P4 -> OUT &= ~(row_mask);//r0,r1,r2,r3
        //set all cols to 1
        P6 -> OUT |= (col_mask);//c0,c1,c2
        return;
}

uint8_t keypad_getkey (void){
//read cols via polling
    char r= 0;
    char c=0;
    char num=0;
    for (c=0; c<=3; c++){
        P6-> OUT &= ~(col_mask);//mask cols =0
        P6->OUT |= (BIT4<<c);//unmask col 1 at at time
        __delay_cycles(4);
        r = P4->IN & (row_mask);
        if(r!=0){
            break;//button pressed, break out of 4 loop
         }
    }
    if (c >3){
        num = 13;
        return num;
    }
    else{
        c= c<<4;
        uint8_t placeholder = (c|r);
        switch(placeholder){    //cols   rows
        case 0x11: num = 1; break;//0001 0001
        case 0x21: num = 2; break;//0010 0001
        case 0x31: num = 3; break;//0011 0001
        case 0x12: num = 4; break;//0000 0010
        case 0x22: num = 5; break;//0001 0010
        case 0x32: num = 6; break;//0010 0010
        case 0x14: num = 7; break;//0000 0100
        case 0x24: num = 8; break;//0001 0100
        case 0x34: num = 9; break;//0010 0100
        case 0x28: num = 0; break;//0000 1000
        case 0x18: num = 10; break;//0001 1000
        case 0x38: num = 12; break;//0010 1000
        default: num =13;
        }
        P6->OUT &= ~(col_mask);
        return num;
    }
}
