/*
 * USB-Uploader for Cypress CY7C68013A
 * Datasheet: http://www.cypress.com/file/138911/download
 * Technical Reference Manual: http://www.cypress.com/file/126446/download
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libusb-1.0/libusb.h>

/* default VID, PID */
#define VID 0x04b4 /* Cypress Semiconductor */
#define PID 0x8613 /* EZ-USB FX2LP */

/* size of "external" RAM 0x0000 - 0x3fff = 16 kiB */
#define RAMSIZE 16*1024

int main(int argc, char *argv[])
{
	libusb_context *ctx;
	libusb_device_handle *handle;
	int ret;
	uint8_t buf[RAMSIZE];/*, ram[RAMSIZE];*/
	int fd, i;

	if (argc != 2) {
		fprintf(stderr, "usage: %s binary\n", argv[0]);
		exit(2);
	}

	if ((ret = libusb_init(&ctx))) {
		fprintf(stderr, "%s: %s\n", libusb_error_name(ret),
		        libusb_strerror(ret));
		libusb_exit(ctx);
		exit(1);
	}

	if (!(handle = libusb_open_device_with_vid_pid(ctx, VID, PID))) {
		fprintf(stderr, "device 0x%x:0x%x not found!\n", VID, PID);
		libusb_exit(ctx);
		exit(1);
	}

	/* claim first interface on device so we can do IO */
	libusb_set_auto_detach_kernel_driver(handle, 1);
	if ((ret = libusb_claim_interface(handle, 0)) != 0) {
		fprintf(stderr, "%s: %s\n", libusb_error_name(ret),
		        libusb_strerror(ret));
		libusb_close(handle);
		libusb_exit(ctx);
		exit(1);
	}

	/* reset 8051
	 * bmRequest: 0x40 (Vendor Request OUT)
	 * bRequest : 0xa0 (Firmware Load)
	 * Adress   : 0xe600 (CPUCS register) */
	buf[0] = 0x01;
	if ((ret = libusb_control_transfer(handle, 0x40, 0xa0, 0xe600, 0x00,
	                                   buf, 1, 1000)) != 1) {
		fprintf(stderr, "%s: %s\n", libusb_error_name(ret),
		        libusb_strerror(ret));
		libusb_release_interface(handle, 0);
		libusb_close(handle);
		libusb_exit(ctx);
		exit(1);
	}

	/* load 8051 binary from given file */
	memset(buf, 0, RAMSIZE);
	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "file '%s' not found!\n", argv[1]);
		libusb_release_interface(handle, 0);
		libusb_close(handle);
		libusb_exit(ctx);
		exit(1);
	}
	read(fd, buf, RAMSIZE);
	close(fd);

	/* upload binary to 8051 RAM */
	for (i = 0; i < 3; ++i) {
		/* maximum data size for control transfer = 4 kiB */
		ret = libusb_control_transfer(handle, 0x40, 0xa0, i*4*1024,
		                              0x00, buf+i*4*1024, 4*1024, 1000);
		if (ret != 4*1024) {
			fprintf(stderr, "upload failed: %s (%s)\n",
		        libusb_error_name(ret),
		        libusb_strerror(ret));
			libusb_release_interface(handle, 0);
			libusb_close(handle);
			libusb_exit(ctx);
			exit(1);
		}
	}

#if 0
	/* verify uploaded code */
	for (i = 0; i < 3; ++i) {
		ret = libusb_control_transfer(handle, 0xc0, 0xa0, i*4*1024,
		                              0x00, ram+i*4*1024, 4*1024, 1000);
		if (ret != 4*1024) {
			fprintf(stderr, "%s: %s\n", libusb_error_name(ret),
			        libusb_strerror(ret));
			libusb_release_interface(handle, 0);
			libusb_close(handle);
			libusb_exit(ctx);
			exit(1);
		}
	}
	for (i = 0; i < RAMSIZE; ++i) {
		if (ram[i] != buf[i]) {
			fprintf(stderr, "verify failed at address 0x%x: "\
			        "expected "\
			        "0x%x instead of 0x%x\n", i, buf[i], ram[i]);
			/*exit(1);*/
		}
	}
#endif

	/* run 8051 */
	buf[0] = 0x00;
	if ((ret = libusb_control_transfer(handle, 0x40, 0xa0, 0xe600, 0x00,
	                                   buf, 1, 1000)) != 1) {
		fprintf(stderr, "%s: %s\n", libusb_error_name(ret),
		        libusb_strerror(ret));
		libusb_release_interface(handle, 0);
		libusb_close(handle);
		libusb_exit(ctx);
		exit(1);
	}

	/* clean up */
	libusb_release_interface(handle, 0);
	libusb_close(handle);
	libusb_exit(ctx);
	return 0;
}
