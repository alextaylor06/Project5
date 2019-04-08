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

unsigned myStack[256];
unsigned* stackP = myStack+256;

int taskId=1;
void RTOSsetup(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 = 0xFFFE; // Enable pins
    P1DIR=BIT0;
    P9DIR=BIT7;
    P1OUT &= ~BIT0; // Red LED initially off
    P9OUT &= ~BIT7; // Green LED initially off


    unsigned myStack=malloc(256*sizeof(unsigned));
    unsigned* stackP = myStack+256;


}

void RTOSinitTask(void (*pFun)(void)){

    struct TCB pFunStruct;
    pFunStruct.id=taskId;
    pFunStruct.address = &pFun;


    taskId++;
}
int RTOSrun(void){


}


