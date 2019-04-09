#include <msp430.h> 
#include "lcd.h"
#include "RTOS.h"
#include <stdio.h>

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

    TA1CTL = 0x0110;    //Set TA0 to up mode, ACLK
    TA1CCR0 = 3000;
    TA1CCTL0 = CCIE;  //Set Output mode to set/reset
    RTOSinitTask(taskA);
    RTOSinitTask(taskB);
    //RTOSinitTask(taskC);
    _BIS_SR(GIE);

	error1=RTOSrun();
	while(1);
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1 (void)
{
    RTOSint();
}

int taskA(void){
    int delaytime=10000;
     int duty=0;
     while(delaytime>=0){
         int delay=0;
         P1OUT &= ~BIT0; // Red LED initially off
         while(delay<=delaytime){
             delay++;
         }
         P1OUT |= BIT0;
         while(delay>=duty){
             delay--;
         }
         delaytime-=50;
         duty+=50;
     }
    }

int taskB(void){
    while(1){
        int delay=0;
        P9OUT &= ~BIT7; // Green LED initially off
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
    printLCD("I'm doing multiple things right now, look at these LEDs blink", 0,0);
}
