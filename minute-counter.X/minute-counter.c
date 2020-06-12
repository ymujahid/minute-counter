/*
 * File:   minute-counter.c
 * Author: Yunus Mujahid
 *
 * Created on June 12, 2020, 6:30 PM
 */



// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 20000000
// crystal frequency set as 20MHz

#include <xc.h>

unsigned char const SEGMENT_MAP[] = {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};

int count = 1;
void main(void) {
    PORTA = PORTB = PORTC = PORTD = PORTE = 0;
    TRISB = TRISC = TRISD = 0;
    while (1){
        count++;
        PORTD = SEGMENT_MAP[0];
        PORTC = SEGMENT_MAP[count];
        __delay_ms(1000);
        PORTB = SEGMENT_MAP[count++];
    }
    return;
    
}
