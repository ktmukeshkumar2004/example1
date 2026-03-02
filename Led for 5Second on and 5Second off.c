#include <xc.h>

// CONFIGURATION BITS
#pragma config FOSC = INTRC_NOCLKOUT  // Internal oscillator
#pragma config WDTE = OFF             // Watchdog Timer disabled
#pragma config PWRTE = ON             // Power-up Timer enabled
#pragma config MCLRE = ON             // MCLR pin enabled
#pragma config CP = OFF               // Code Protection off
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 8000000   // 8MHz internal oscillator

void main()
{
    // Set internal oscillator to 8MHz
    OSCCON = 0x70;  

    TRISA0 = 0;     // Set RA0 as output
    ANSEL = 0x00;   // Disable analog inputs
    ANSELH = 0x00;

    while(1)
    {
        RA0 = 1;    // LED ON
        __delay_ms(500);

        RA0 = 0;    // LED OFF
        __delay_ms(500);
    }
}