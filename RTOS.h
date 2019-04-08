/*
 * RTOS.h
 *
 *  Created on: Mar 29, 2019
 *      Author: Alex
 */

#ifndef RTOS_H_
#define RTOS_H_

void RTOSsetup(void);
void RTOSinitTask(void (*pFun)(void));
int RTOSrun(void);


#endif /* RTOS_H_ */
