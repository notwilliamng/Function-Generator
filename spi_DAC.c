/*
 * spi_DAC.c
 *
 *  Created on: May 4, 2021
 *      Author: William
 */
#include "msp.h"
#define SPI_CS BIT4
#define SPI_SCLK BIT5
#define SPI_SIMO BIT6

void spi_init(void){
    EUSCI_B0 -> CTLW0 |= EUSCI_B_CTLW0_SWRST;// 1st bit to reset software
    EUSCI_B0 -> CTLW0 = (EUSCI_B_CTLW0_MSB //set MSB
                        |EUSCI_B_CTLW0_MST //set as main device on bus
                        |EUSCI_B_CTLW0_CKPL//
                        |EUSCI_B_CTLW0_MODE_0 //set SPI in 3 pin mode
                        |EUSCI_B_CTLW0_SYNC //synchronous mode
                        |EUSCI_B_CTLW0_SSEL__SMCLK //use SMCLK
                        |EUSCI_B_CTLW0_SWRST); // stay in reset

    EUSCI_B0-> BRW = 0x01; //divide SMCLK by 1


    P1-> SEL0 |= (SPI_SCLK | SPI_SIMO);  //configure EUSC
    P1-> SEL1 &= ~(SPI_SCLK | SPI_SIMO);


    P2-> SEL0 &= ~SPI_CS; //set gpio for chip select
    P2-> SEL1 &= ~SPI_CS;
    P2-> DIR |= SPI_CS;
    P2-> OUT |= SPI_CS; //initialize to high

    EUSCI_B0 -> CTLW0 &= ~EUSCI_B_CTLW0_SWRST; //take EUSCI out of software rest
////////////ready to go ////////////////////////

}

void spi_send(uint16_t spi_data){
    uint8_t hibyte, lobyte;

    lobyte = spi_data & 0xFF; //mask lower byte
    hibyte = (spi_data >>8) & 0x0F; //mask upper byte
    hibyte = (hibyte | 0x30);
    P2-> OUT &= ~SPI_CS; //set chip select low

    //transmit upper byte
    while (!(EUSCI_B0-> IFG & EUSCI_B_IFG_TXIFG));
    EUSCI_B0 -> TXBUF = hibyte; //send high byte to transfer buffer

    //wait for TXIFG to be 1 -> transfer buffer is empty

    //transmit lower byte
    while (!(EUSCI_B0-> IFG & EUSCI_B_IFG_TXIFG));
    EUSCI_B0 -> TXBUF = lobyte; //send high byte to transfer buffer

   while (!(EUSCI_B0-> IFG & EUSCI_B_IFG_RXIFG));
   P2-> OUT |= SPI_CS;

    __delay_cycles(50); //delay before sending next value

}
