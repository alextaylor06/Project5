#include <msp430.h> 
#include "lcd.h"
#include "RTOS.h"
/**
 * main.c
 */
extern void scheduler(void);

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
	//RTOSinitTask(taskC);

    TA1CTL = 0x0110;    //Set TA0 to up mode, ACLK
    TA1CCR0 = 3000;
    TA1CCTL0 = CCIE;  //Set Output mode to set/reset

    _BIS_SR(GIE);

	error1=RTOSrun();
	while(1);
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1 (void)
{
    scheduler();
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
