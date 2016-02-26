CC:=gcc
CFLAGS:=-Os `pkg-config --cflags libusb-1.0`
# toolchain for 8051: SDCC (http://sdcc.sourceforge.net/)
AS:=sdas8051
ASFLAGS:=-los
LD:=sdld
LDFLAGS:=-b CODE=0x0000 -b DSEG=0x30 -i
MAKEBIN:=makebin

%.rel: %.s
	$(AS) $(ASFLAGS) $<

%.ihx: %.rel
	$(LD) $(LDFLAGS) $<

%.bin: %.ihx
	$(MAKEBIN) -p $< $@

all: loader toggle.bin uart.bin

loader: main.c
	$(CC) $(CFLAGS) main.c `pkg-config --libs libusb-1.0` -pedantic -Wall -Wextra -o loader

toggle.rel: cypress.inc
uart.rel: cypress.inc

clean:
	rm -f loader
	rm -f *.rel *.sym *.lst *.ihx *.bin

.PHONY: all clean
