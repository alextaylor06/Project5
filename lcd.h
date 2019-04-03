// 2-19-19
// ECE422: Microcontrollers II
// V 2.0

// I have neither given or received, nor have I tolerated,
// others' use of unauthorized aid.
// Madeline Flynn & Alex Taylor

// Project 3: Interfacing to External LCD HEADER FILE
// Header File for LCD Library

// Define Library Header
#ifndef LCD_H_
#define LCD_H_

// Include statements
#include <msp430.h>
#include <string.h>
#include <stdio.h>

// Constant Pins
#define EN      BIT4    // Enable
#define RS      BIT5    // Register Selection
#define DATA    0x0F    // DB7 -> DB4
#define ACLK        0x0100  // Value to set for ACLK as timer source
#define UP          0x0010  // Value to set for UP counting
#define CLEAR_CLK   0x0004  // Value of Clock Clear
#define BY8     0x00C0

// Commands
#define CLEAR   0x01    // Clear Screen


// Functions
void delay(unsigned int time);                              // Delay time in milliseconds
void delayS(unsigned int time);
void initLCD();                                 // Initialize LCD
void lcdTriggerEN();                            // Trigger Enable
void lcdWriteData(unsigned char data);          // Send Data (Characters)
void lcdWriteCmd(unsigned char cmd);            // Send Commands
void clearLCD();                                // Clear LCD
void printLCD(char * text, int x, int y);       // Write string
void printIntLCD(int val, int x, int y);       // Write integer
void setCursorPositionLCD(int x, int y);        // Set Cursor Position on LCD
void printArrowLCD(char direction, int x, int y);       // Write arrows to position
void scrollWordsLCD(char * text);                   // Scrolls words across screen
void getLowNib(char x);                         // Get the lower nibble of x
int  findTextSpace(char * text);                 // Finds the space in a string


#endif /* LCD_H_ */
