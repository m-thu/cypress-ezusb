; registers specific to Cypress CY7C68013A

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; special function registers (SFR)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; port A (bit addressable)
IOA = 0H80
IOA.0 = 0H80
IOA.1 = 0H81
IOA.2 = 0H82
IOA.3 = 0H83
IOA.4 = 0H84
IOA.5 = 0H85
IOA.6 = 0H86
IOA.7 = 0H87

; port B (bit addressable)
IOB = 0H90
IOB.0 = 0H90
IOB.1 = 0H91
IOB.2 = 0H92
IOB.3 = 0H93
IOB.4 = 0H94
IOB.5 = 0H95
IOB.6 = 0H96
IOB.7 = 0H97

; autopointer 1 address high
AUTOPTRH1 = 0H9A
; autopointer 1 address low
AUTOPTRL1 = 0H9B
; autopointer 2 address high
AUTOPTRH2 = 0H9D
; autopointer 2 address low
AUTOPTRL2 = 0H9E

; port C (bit addressable)
IOC = 0HA0
IOC.0 = 0HA0
IOC.1 = 0HA1
IOC.2 = 0HA2
IOC.3 = 0HA3
IOC.4 = 0HA4
IOC.5 = 0HA5
IOC.6 = 0HA6
IOC.7 = 0HA7

; interrupt 2 clear
INT2CLR = 0HA1
; interrupt 4 clear
INT4CLR = 0HA2
; endpoints 2,4,6,8 status flags
EP2468STAT = 0HAA
; endpoints 2, 4 slave FIFO status flags
EP24FIFOFLGS = 0HAB
; endpoints 6, 8 slave FIFO status flags
EP68FIFOFLGS = 0HAC
; autopointers 1 and 2 setup
AUTOPTRSETUP = 0HAF

; port D (bit addressable)
IOD = 0HB0
IOD.0 = 0HB0
IOD.1 = 0HB1
IOD.2 = 0HB2
IOD.3 = 0HB3
IOD.4 = 0HB4
IOD.5 = 0HB5
IOD.6 = 0HB6
IOD.7 = 0HB7

; port E (not bit addressable!)
IOE = 0HB1

; port A output enable
OEA = 0HB2
; port B output enable
OEB = 0HB3
; port C output enable
OEC = 0HB4
; port D output enable
OED = 0HB5
; port E output enable
OEE = 0HB6

; endpoint 0 and 1 status
EP01STAT = 0HBA
; endpoint 2,4,6,8 GPIF slave FIFO trigger
GPIFTRIG = 0HBB
; GPIF data high (16-bit mode only)
GPIFSGLDATH = 0HBD
; GPIF data low w/trigger
GPIFSGLDATLX = 0HBE
; GPIF data low w/no trigger
GPIFSGLDATLNOX = 0HBF

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; general configuration registers
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; CPU control and status register
CPUCS = 0HE600
CPUCS.8051RES  = 0
CPUCS.CLKOE    = 1
CPUCS.CLKINV   = 2
CPUCS.CLKSPD0  = 3
CPUCS.CLKSPD1  = 4
CPUCS.PORTCSTB = 5

; I2C bus control and status register
I2CS = 0HE678
I2CS.DONE   = 0
I2CS.ACK    = 1
I2CS.BERR   = 2
I2CS.ID0    = 3
I2CS.ID1    = 4
I2CS.LASTRD = 5
I2CS.STOP   = 6
I2CS.START  = 7

; I2C bus data register
I2CDAT = 0HE679

; I2C bus control register
I2CTL = 0HE67A
I2CTL.400KHZ = 0
I2CTL.STOPIE = 1
