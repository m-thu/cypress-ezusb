; toggles port A0

.include "cypress.inc"

; reset vector
.area CODE (ABS)
.org 0h0000

; disable all interrupts
clr EA

; set clock speed
mov dptr, #CPUCS
movx a, @dptr
;anl a, #~(1<<CPUCS.CLKSPD0 | 1<<CPUCS.CLKSPD1)		; 12 MHz (default)
orl a, #(1<<CPUCS.CLKSPD0)				; 24 MHz
movx @dptr, a

; configure port A0 as an output
orl OEA, #1

loop:
	; toggle port A0
	clr IOA.0
	setb IOA.0
	sjmp loop
