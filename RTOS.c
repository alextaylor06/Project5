/*
 * RTOS.c
 *
 *  Created on: Mar 29, 2019
 *      Author: Alex
 */

#include <msp430.h>

struct TCB
{
    unsigned int id;    //Task id
    unsigned int address;  //Address of function
    unsigned int prevStack;//Task previous SP position
    unsigned int TCBLoc; //TCB Location
   // enum TaskState state;
};
int taskId=1;
void RTOSsetup(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 = 0xFFFE; // Enable pins
    P1DIR=BIT0;
    P9DIR=BIT7;
    P1OUT &= ~BIT0; // Red LED initially off
    P9OUT &= ~BIT7; // Green LED initially off

    TA1CTL = 0x0210;    //Set TA0 to up mode, ACLK
    TA1CCR1 = 3333;
    TA1CCTL1 = 0x00E0;  //Set Output mode to set/reset

}

void RTOSinitTask(void (*pFun)(void)){

    struct TCB pFunStruct;
    pFunStruct.id=taskId;
    pFunStruct.address = &pFun;




    taskId++;
}
void RTOSrun(void){


}


