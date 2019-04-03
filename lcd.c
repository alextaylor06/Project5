// 2-19-19
// ECE422: Microcontrollers II
// V 2.0

// I have neither given or received, nor have I tolerated,
// others' use of unauthorized aid.
// Madeline Flynn & Alex Taylor

// Project 3: Interfacing to External LCD HEADER FILE
// Header File for LCD Library

// Reference for Pin Numbers
// RS   2.5
// E    2.4
// DB7  2.3 MSB
// DB6  2.2
// DB5  2.1
// DB4  2.0 LSB



#include <msp430.h>
#include "lcd.h"
#include <string.h>

//************************************************************************
// FUNCTION delay
// Parameter: unsigned int time in ms
// Uses TimerA0 in ACLK UP Mode
//************************************************************************
void delay(unsigned int time) {
    TA0CCR0 = 40 * time;
    TA0CTL = ACLK|UP|CLEAR_CLK;     // Set ACLK, UP MODE

    // Wait for timer to finish
    while(!(TA0CTL & 0x0001));

    TA0CTL = TA0CTL & 0xFFFE;   // Clear TAIFG Flag

}

//************************************************************************
// FUNCTION delay
// Parameter: unsigned int time in ms
// Uses TimerA0 in ACLK UP Mode
//************************************************************************
void delayS(unsigned int time) {
    TA0CCR0 = 5000 * time;
    TA0CTL = ACLK|UP|CLEAR_CLK|BY8;     // Set ACLK, UP MODE

    // Wait for timer to finish
    while(!(TA0CTL & 0x0001));

    TA0CTL = TA0CTL & 0xFFFE;   // Clear TAIFG Flag

}


//************************************************************************
// FUNCTION initLCD
// Sets up LCD for 4-bit mode, 2 lines, 5x8 characters
// Turns display on with cursor blinking
//************************************************************************
void initLCD() {
    delay(100);                 // Wait for 100ms after power is applied.

    P2DIR = EN + RS + DATA;     // Make pins 2.0-2.5 outputs
    P2OUT = 0x03;               // Start LCD (send 0x03) DB5 HI DB4 HI

    // Enable / Disable 3 times to send data 3 times
    lcdTriggerEN();
    delay(5);
    lcdTriggerEN();
    delay(5);
    lcdTriggerEN();
    delay(5);

    // Switch to 4-bit mode
    P2OUT = 0x02;
    lcdTriggerEN(); // "lock it in"
    delay(5);

    // Initial Commands for settings and clearing lcd
    lcdWriteCmd(0x28); // 4-bit, 2 line, 5x8
    lcdWriteCmd(CLEAR); // Clear LCD
    lcdWriteCmd(0x06); // Auto-Increment
    lcdWriteCmd(0x0D); // Display On, Blink

}

//************************************************************************
// FUNCTION lcdTriggerEN
// Toggles Enable Pin to "Lock in" (send) data
//************************************************************************
void lcdTriggerEN() {
    P2OUT |= EN;
    P2OUT &= ~EN;
}

//************************************************************************
// FUNCTION lcdWriteData
// Parameter: unsigned char data to write to LCD
// Uses bit mask & shift ascii codes to print characters
//************************************************************************
void lcdWriteData(unsigned char data) {
    P2OUT |= RS; // Set RS to Data
    getLowNib(data >> 4); // Upper nibble
    lcdTriggerEN();
    getLowNib(data); // Lower nibble
    lcdTriggerEN();
    delay(1); // Delay > 47 us
}

//************************************************************************
// FUNCTION lcdWriteData
// Parameter: unsigned char cmd to write LCD settings
//      settings include cursor, line
// Uses bit mask & shift to commands
//************************************************************************
void lcdWriteCmd(unsigned char cmd) {
    P2OUT &= ~RS; // Set RS to Data
    getLowNib(cmd >> 4); // Upper nibble
    lcdTriggerEN();
    getLowNib(cmd); // Lower nibble
    lcdTriggerEN();
    delay(2); // Delay > 1.5ms
}

//************************************************************************
// FUNCTION printLCD
// Parameters: char* text for what to write on screen, int x for column, int y for row
// Prints a word to specified location
// ADD OVERFLOW CODE
//************************************************************************
void printLCD(char* text, int x, int y) {
    // Set the position of the cursor
    setCursorPositionLCD(x,y);

    if(strlen(text) > 32) scrollWordsLCD(text);
    else if(strlen(text) > 16) {
        // Print Data
        int i;
        i = 0;
        while (i != findTextSpace(text)) {
            lcdWriteData(text[i]);
            i++;
        }
        i++;
        setCursorPositionLCD(0,1);
        while (text[i] != '\0') {
            lcdWriteData(text[i]);
            i++;
        }
}
    else {
        // Print Data
        int i;
        i = 0;
        while (text[i] != '\0') {
            lcdWriteData(text[i]);
            i++;
        }
    }

}

//************************************************************************
// FUNCTION printIntLCD
// Parameter: int val to print, int x for column, int y for row
// Prints integer to screen
//************************************************************************
void printIntLCD(int val, int x, int y){
    char number_string[16];
    sprintf(number_string, "%d", val); // Convert the integer to character string
    printLCD(number_string, x, y);
}

//************************************************************************
// FUNCTION clearLCD
// Clears LCD screen
//************************************************************************
void clearLCD() {
    lcdWriteCmd(CLEAR);
}

//************************************************************************
// FUNCTION setCursorPostionLCD
// Parameter: int x for column, int y for row
// Moves cursor to specific location
//************************************************************************
void setCursorPositionLCD(int x, int y) {
    if (x < 16) {
        x |= 0x80; // Set LCD for first line write
        if(y==1) {
            x |= 0x40;  // Set LCD for second line write
        }
        lcdWriteCmd(x);
    }
}

//************************************************************************
// FUNCTION printArrowLCD
// Parameters: char direction for which arrow to write on screen, int x for column, int y for row
// Prints arrow to specific cursor position
//************************************************************************
void printArrowLCD(char direction, int x, int y) {
    setCursorPositionLCD(x,y);
    if(direction == 'r') lcdWriteData(0x7E);    // Arrow Pointing Right
    else lcdWriteData(0x7F); // Arrow Pointing Left

}

//************************************************************************
// FUNCTION scrollWordsLCD
// Parameters: char* text for what to write on screen
// Scrolls words across screen
//************************************************************************
void scrollWordsLCD(char* text) {
    int i,j;

    // print each letter starting at [0,0] one letter forward in the string
    for(i = 0; i < strlen(text)+1; i++) {
        clearLCD();
        j = i;
        while (text[j] != '\0') {
            lcdWriteData(text[j]);
            j++;
            if(j == i+16) break;
        }
        delay(300); // wait .3 seconds
    }

}

//************************************************************************
// FUNCTION getLowNib
// Parameters: char* text for what to write on screen
// Scrolls words across screen
//************************************************************************
void getLowNib(char x) {
    P2OUT = (P2OUT & 0xF0) + (x & 0x0F);
}

//************************************************************************
// FUNCTION findTextSpace
// Parameters: char* text for what to write on screen > 16 characters
// Return: index of space character right before index 16
//************************************************************************
int findTextSpace(char * text) {
    int lcv;
    for(lcv = 15; lcv >= 0; lcv--) {
        if(text[lcv] == 0x20) return lcv;
    }
    return strlen(text);
}

