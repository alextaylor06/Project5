/*
 * RTOS.c
 *
 *  Created on: Mar 29, 2019
 *      Author: Alex
 */

#include <msp430.h>
extern void scheduler(*unsigned, unsigned int, unsigned int);

struct TCB
{
    unsigned int id;    //Task id
    unsigned int address;  //Address of function
    unsigned int prevStack;//Task previous SP position
    unsigned int TCBLoc; //TCB Location
   // enum TaskState state;
};

struct TCB *taskAp;
struct TCB *taskBp;
struct TCB *taskCp;


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
    struct TCB pFunStructA;
    struct TCB pFunStructB;
    struct TCB pFunStructC;
    if(taskId==1) {
        pFunStructA.id=taskId;
        pFunStructA.address = &pFun;
        taskAp= &pFunStructA;
    }
    else if(taskId==2) {
        pFunStructB.id=taskId;
        pFunStructB.address = &pFun;
        taskBp= &pFunStructB;
    }
    else {
        pFunStructC.id=taskId;
        pFunStructC.address = &pFun;
        taskCp= &pFunStructC;
    }

    taskId++;
}
int RTOSrun(void){
    scheduler(stackP,taskAp->address,taskBp->address);
    while(1);

}


