#include <xc.h>

#define _XTAL_FREQ 8000000

// CONFIG BITS for PIC16F877A
#pragma config FOSC = HS        // External crystal (HS)
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

// Interrupt Service Routine
void __interrupt() magic(void)
{
    if (INTCONbits.TMR0IF)      // Timer0 overflow?
    {
        PORTBbits.RB0 ^= 1;    // Toggle LED
        TMR0 = 158;            // Reload Timer0
        INTCONbits.TMR0IF = 0; // Clear flag
    }
}

void main(void)
{
    // PORTB setup
    TRISBbits.TRISB0 = 0;      // RB0 as output
    PORTBbits.RB0 = 0;         // LED OFF initially

    // Timer0 setup
    OPTION_REG = 0b00000111;   // Prescaler 1:256, internal clock
    TMR0 = 158;                // Preload value

    // Enable interrupts
    INTCONbits.TMR0IE = 1;     // Timer0 interrupt enable
    INTCONbits.GIE = 1;        // Global interrupt enable

    while(1)
    {
        // Main loop empty
        // LED blinking handled by interrupt
    }
}
