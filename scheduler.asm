; Alex Taylor
; ECE 422: Embedded Microcontrollers II
; Assignment 3


 ;I have neither given or received, nor have I tolerated
 ;others' use of unauthorized aid. -Alex Taylor */
	.cdecls C,NOLIST, "msp430.h"   ; Processor specific definitions


;============================================================================
; set_port
;============================================================================
      .global scheduler               ; Declare symbol to be exported
      .sect ".text"                  ; Code is relocatable
scheduler:   .asmfunc


reti
.endasmfunc
