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
#define digit1 RB0
#define digit2 RB1
#define digit3 RB2
#define digit4 RB3
#define set_time_button RB4
#define countdown_button RB5

// crystal frequency set as 20MHz

#include <xc.h>






unsigned char const SEGMENT_MAP[] = {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F, 0B00001001};

int count = 0;
int set_second1 = 0;
int set_second2 = 0;
int set_minute1 = 0;
int set_minute2 = 0;

void display_on_first_digit(int digit){
    PORTD = SEGMENT_MAP[digit];
}

void display_on_second_digit(int digit, int i){
    PORTC = SEGMENT_MAP[digit];
    PORTB = 0B00001110;
    for (int n = 0; n<i; n++){
            __delay_ms(1);
    }
    RB0 = 1;
    
}

void display_colon_on_third_digit(int i){
    PORTC = SEGMENT_MAP[10];
    PORTB = 0B00001101;
    for (int n = 0; n<i; n++){
            __delay_ms(1);
    }
    RB1 = 1;
    
}

void display_on_fourth_digit(int digit, int i){
    PORTC = SEGMENT_MAP[digit];
    PORTB = 0B00001011;
    for (int n = 0; n<i; n++){
            __delay_ms(1);
    }
    RB2 = 1;
    
}

void display_on_fifth_digit(int digit, int i){
    PORTC = SEGMENT_MAP[digit];
    PORTB = 0B00000111;
    for (int n = 0; n<i; n++){
            __delay_ms(1);
    }
    RB3 = 1;
    
}

void custom_display_on (int d1, int d2, int d3, int d4, int i) {
        display_on_first_digit(d1);
        display_on_second_digit(d2, i);
        display_colon_on_third_digit(i);
        display_on_fourth_digit(d3, i);
        display_on_fifth_digit(d4, i);
}

void count_to_minutes(int minute) {
    int first_digit, second_digit, third_digit, fourth_digit;
    first_digit = second_digit = third_digit = fourth_digit = 0;
    custom_display_on(first_digit, second_digit, third_digit, fourth_digit, 1000);
    while (first_digit > 0) {
        if (fourth_digit < 9){
            fourth_digit++;
        }
        else {
            fourth_digit = 0;
            third_digit++;
            if (third_digit > 5){
                third_digit = 0;
                second_digit++;
                if (second_digit > 9){
                    second_digit = 0;
                    first_digit++;
                    if (first_digit > minute){
                        first_digit = second_digit = third_digit = fourth_digit = 0;
                    }
                }
            }
        }
    }
        
}

void countdown_to_second (int first_digit, int second_digit, int third_digit, int fourth_digit) {
    RB6 = 1;
        __delay_ms(100);
        RB6 = 0;
        __delay_ms(100);
    custom_display_on(first_digit, second_digit, third_digit, fourth_digit, 10);
    while (first_digit >= 0){
        for (int i = 0; i < 10; i++) {
            custom_display_on(first_digit, second_digit, third_digit, fourth_digit, 10);
        }
        
    
    if (fourth_digit < 0) {
        fourth_digit = 9;
        third_digit--;
        if (third_digit < 0){
            third_digit = 5;
            second_digit--;
            if (second_digit < 0){
                second_digit = 9;
                first_digit--;
                if (first_digit < 0){
                    first_digit = second_digit = third_digit = fourth_digit = 0;
                }
            }
        }
    } else {
       fourth_digit--; 
    }
        
        }
        

}

//void set_time_second_minute() {
//    if (countdown_button == 1) {
//            __delay_ms(10);
//            while (countdown_button == 1){
//                if (set_time_button == 1) {
//                    __delay_ms(10);
//                }
//                    while (set_time_button == 1) {
//                        set_second2++;
//                        display_on_fifth_digit(set_second2);
//                        if (set_second2 > 9) {
//                            set_second1++;
//                            display_on_fourth_digit(set_second1);
//                            set_second2 = 0;
//                            if (set_second1 > 5) {
//                                set_minute2++;
//                                display_on_second_digit(set_minute2);
//                                set_second1 = 0;
//                                if (set_minute2 > 9) {
//                                    set_minute1++;
//                                    display_on_first_digit(set_minute1);
//                                    set_minute2 = 0;
//                                    if (set_minute1 > 9) {
//                                        set_minute1 = 5;
//                                        display_on_first_digit(set_minute1);
//                                        set_minute2 = 9;
//                                        display_on_second_digit(set_minute2);
//                                        set_second1 = 5;
//                                        display_on_fourth_digit(set_second1);
//                                        set_second2 = 9;
//                                        display_on_fifth_digit(set_second2);
//                                    }
//                                }
//                        }
//                }
//            __delay_ms(1000);
//            }
//        }
//        
//    }
//}

void set_time_minute () {
    custom_display_on(set_minute1, set_minute2, set_second1, set_second2, 10);
        if (countdown_button == 1) {
            __delay_ms(10);
            while (countdown_button == 1){ 
                custom_display_on(set_minute1, set_minute2, set_second1, set_second2, 10);
                if (set_time_button == 1) {
                    __delay_ms(10);
                    while (set_time_button == 1) {
                        custom_display_on(set_minute1, set_minute2, set_second1, set_second2, 5);
                        set_second2++;
                        if (set_second2 > 9){
                            set_second1++;
                            set_second2 = 0;
                            if (set_second1 > 5){
                                set_minute2++;
                                set_second1 = 0;
                                if (set_minute2 > 9){
                                    set_minute2 = 0;
                                    set_minute1++;
                                    if (set_minute1 > 5){
                                        set_minute1 = 5;
                                        set_minute2 = 9;
                                        set_second1 = 5;
                                        set_second2 = 9;
                                    }
                                }
                            }
                        }              
        }
        
    }
        
    }
    }
}



void main(void) {
    //  send 0 to all the seven segment displays
//  using  the first, second, third and fourth digit variables
//  then increment the fourth digit variable
// to do that,
// set PORTC to the required digit
// and turn on only digit4
// when fourth digit becomes greater than 9
// include third digit in the display
// by setting PORTC to display 1 and then setting digit3 low to be displayed on the 3rd digit 
// set the multiplex to display ':' on its second digit constant
//    set the time with the two  buttons simultaneously
//    let the counter count from 0 to the preset 
//    FOR THE COUNTDOWN,
//    CREATE A FUNCTION THAT TAKES IN THE VALUES FOR EACH OF THE 7SEGS
//    THEN LET THE COUNTER COUNTDOWN FROM THOSE VALUES TO 0
    PORTA = PORTB = PORTC = PORTD = PORTE = 0;
    TRISB = 0B00110000;
    TRISC = TRISD = 0;
    RB0 = RB1 = RB2 = RB3 = 1;
    while (1){
        custom_display_on(set_minute1, set_minute2, set_second1, set_second2, 10);
        set_time_minute();
        if (set_minute2 != 0) {
            countdown_to_second(set_minute1, set_minute2, set_second1, set_second2);
        }
        
        
    }
    return;
    
}
