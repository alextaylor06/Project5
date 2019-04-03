#include <msp430.h> 
#include "lcd.h"

/**
 * main.c
 */

int taskA(void); //Blink Red LED
int taskB(void); //Blink Green LED
int taskC(void); //Display


int main(void)
{
    char error1;
	RTOSsetup();
	initLCD();

	RTOSinitTask(taskA);
	RTOSinitTask(taskB);
	RTOSinitTask(taskC);

	error1=RTOSrun();
	while(1);
}


int taskA(void){
    while(1){
        int delay=0;
        P1OUT &= ~BIT0; // Red LED initially off
        while(delay<=10000){
            delay++;
        }
        P1OUT |= BIT0;
        while(delay>=0){
            delay--;
        }
    }
}
int taskB(void){
    while(1){
        int delay=0;
        P9OUT &= ~BIT7; // Red LED initially off
        while(delay<=10000){
            delay++;
        }
        P9OUT |= BIT7;
        while(delay>=0){
            delay--;
        }
    }
}
int taskC(void){

}
