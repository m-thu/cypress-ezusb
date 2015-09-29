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

; 0x80 -- 0x87
DPL0 = 0H82
DPH0 = 0H83
DPL1 = 0H84
DPH1 = 0H85
DPS = 0H86

; 0x87 -- 0x8f
CKCON = 0H8E

; 0x90 -- 0x97
EXIF = 0H91
MPAGE = 0H92

; 0x98 -- 0x9f
SCON0 = 0H98
SBUF0 = 0H99
AUTOPTRH1 = 0H9A
AUTOPTRL1 = 0H9B
AUTOPTRH2 = 0H9D
AUTOPTRL2 = 0H9E

; 0xa0 -- 0xa7
INT2CLR = 0HA1
INT4CLR = 0HA2

; 0xa8 -- 0xaf
EP2468STAT = 0HAA
EP24FIFOFLGS = 0HAB
EP68FIFOFLGS = 0HAC
AUTOPTR_SETUP = 0HAF

; 0xb0 -- 0xb7

; 0xb8 -- 0xbf
EP01STAT = 0HBA
GPIFTRIG = 0HBB
GPIFSGLDATH = 0HBD
GPIFSGLDATLX = 0HBE
GPIFSGLDATLNOX = 0HBF

; 0xc0 -- 0xc7
SCON1 = 0HC0
SBUF1 = 0HC1

; 0xc8 -- 0xcf

; 0xd0 -- 0xd7

; 0xd8 -- 0xdf
EICON = 0HD8

; 0xe0 -- 0xe7

; 0xe8 -- 0xef
EIE = 0HE8

; 0xf0 -- 0xf7

; 0xf8 -- 0xff
EIP = 0HF8

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
