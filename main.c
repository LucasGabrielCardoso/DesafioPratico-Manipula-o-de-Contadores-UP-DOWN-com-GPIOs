/*
 * File:   main.c
 * Author: LucasGabriel
 *
 * Created on December 1, 2022, 10:03 PM
 */

#include <xc.h>
#include <stdbool.h>
#include "device_config.h"

#define BUTTON_INCREASE     PORTBbits.RB6
#define BUTTON_DECREASE     PORTBbits.RB5

#define Increase_Port(x)    x =  ~((~x)<<1)
#define Decrease_Port(x)    x >>= 1

//Function Declarations
//void Increase_Port(volatile unsigned char *const port2change);
//void Decrease_Port(volatile unsigned char *const port2change);
void Delay_ms(unsigned long tempo);

void main(void) 
{
    //Clock Configurations
    OSCCON      =   0x30;
    OSCCON2     =   0x04;
    OSCTUNE     =   0x00;
    
    //Setting Pins as I/O ports
    ANSEL       =   0xFF;
    ANSELH      =   0x07;
    
    //Selecting Input and Output Pins
    TRISA       =   0xFF;
    TRISB       =   0xFF;
    TRISC       =   0x00;
    
    //Setting unused Pins in Tristate mode
    //and PORTC in low state
    LATA        =   0x00;
    LATB        =   0x00;
    LATC        =   0x00;
    
    //Enabling internal Pull-Ups from PORTB
    INTCON2bits.nRABPU    =   0x00;    
    WPUB                  =   0xFF;
    
    enum {ACIONADO, DESACIONADO} SELO_BNT1 = DESACIONADO,
                                 SELO_BNT2 = DESACIONADO;
    
//    __debug_break();
    while(true)
    {
        if((DESACIONADO == SELO_BNT1)&&(0 == BUTTON_INCREASE))
        {
            Delay_ms(50);
            SELO_BNT1        =   ACIONADO;  
        }
        else if((ACIONADO == SELO_BNT1)&&(1 == BUTTON_INCREASE))
        {
            Delay_ms(50);
            SELO_BNT1        =   DESACIONADO;  
            Increase_Port(LATC);
        }
        else if((DESACIONADO == SELO_BNT2)&&(0 == BUTTON_DECREASE))
        {
            Delay_ms(50);
            SELO_BNT2        =   ACIONADO;  
        }
        else if((ACIONADO == SELO_BNT2)&&(1 == BUTTON_DECREASE))
        {
            Delay_ms(50);
            SELO_BNT2        =   DESACIONADO;  
            Decrease_Port(LATC);
        }
    }
    return;
}

void Delay_ms(unsigned long tempo)
{
    while(tempo>0)
    {
        __delay_ms(1);
        --tempo;
    }
}