; simple soft uart (9600 baud, no parity, one stop bit)
; (56 pin package of the CY7C68013A doesn't have the RX, TX pins)
; resends all received characters

UART_TX = IOA.1
UART_RX = IOA.0

; memory map of internal RAM:
; 0x00 -- 0x1f: four register banks [BSEG]
; 0x20 -- 0x2f: bit addressable segment
; 0x30 -- 0x7f: scratch pad area [DSEG]
; 0x80 -- 0xff: SFR (direct addressing)
; 0x80 -- 0xff: RAM (indirect addressing) [ISEG]

.include "cypress.inc"

.area DSEG (REL)

.area CODE (ABS)
; reset vector
.org 0H0000
ljmp reset

; external interrupt 0 vector
.org 0H003
ljmp int0

reset:
	; select register bank 0
	clr RS0
	clr RS1

	; set clock speed to 12 MHz
	mov dptr, #CPUCS
	movx a, @dptr
	anl a, #~(1<<CPUCS.CLKSPD0 | 1<<CPUCS.CLKSPD1)
	movx @dptr, a

	; configure UART_TX as an output
	orl OEA, #2
	; idle = high
	setb UART_TX
	
	; setup stack
	mov SP, #0x80

	; TMOD timer 0 register
	; GATE | C/T | M1 | M0
	;    0 |   0 |  1 |  0
	; 8-bit auto-reload timer
	mov TMOD, #0x02
	; reload value for 9600 Baud
	; 256 - (1s/9600 / 1/1MHz) = 152
	mov TH0, #152

	; stop timer 0
	clr TR0

	; configure PORTA.0 as /INT0 pin
	mov dptr, #PORTACFG
	movx a, @dptr
	orl a, #(1<<PORTACFG.INT0)
	movx @dptr, a
	; configure int0 as level-triggered
	clr IT0
	; enable external interrupt 0
	mov IE, #0h81

loop:
	sjmp loop

; sends character in r0
tx_byte:
	; disable all interrupts
	clr EA

	; get byte to transmit
	mov a, r0

	; reload value for 9600 Baud
	; 256 - (1s/9600 / 1/1MHz) = 152
	mov TL0, #152

	; 8 data bits, 1 start bit, 1 stop bit, LSB first
	mov r1, #10
	; carry contains stop bit
	setb c
	; start bit = 0
	clr UART_TX
	; run timer 0
	setb TR0
	sjmp tx_byte_wait

tx_byte_send_bits:
	rrc a
	mov UART_TX, c

	; wait for 104 us
tx_byte_wait:
	jbc TF0, tx_byte_dec_counter
	sjmp tx_byte_wait

tx_byte_dec_counter:
	djnz r1, tx_byte_send_bits

	; stop timer 0
	clr TR0
	; enable all interrupts
	setb EA
	ret

int0:
	; receive 8 data bits + 1 start bit + 1 stop bit, LSB first
	mov r1, #10

	; reload value for 3/2 * 104 us
	; 256 - (1s/9600 / 1/1MHz) * 3/2 = 100
	mov TL0, #100
	; start timer 0
	setb TR0
	sjmp int0_wait

int0_get_bits:
	mov c, UART_RX
	rrc a

	; wait for 104 us
int0_wait:
	jbc TF0, int0_dec_counter
	sjmp int0_wait

int0_dec_counter:
	djnz r1, int0_get_bits

	; throw away stop bit
	rlc a

	; stop timer 0
	clr TR0

	; echo received character
	mov r0, a
	acall tx_byte

	reti
