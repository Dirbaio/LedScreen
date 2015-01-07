#include "Screen.hpp"
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

using namespace std;


static int set_interface_attribs(int fd, int speed, int parity)
{
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if(tcgetattr(fd, &tty) != 0)
	{
		printf("error %d from tcgetattr\n", errno);
		return -1;
	}

	cfsetospeed(&tty, speed);
	cfsetispeed(&tty, speed);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK;	 // disable break processing
	tty.c_lflag = 0;		// no signaling chars, no echo,
					// no canonical processing
	tty.c_oflag = 0;		// no remapping, no delays
	tty.c_cc[VMIN]  = 0;	    // read doesn't block
	tty.c_cc[VTIME] = 5;	    // 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
					// enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if(tcsetattr(fd, TCSANOW, &tty) != 0)
	{
		printf("error %d from tcsetattr\n", errno);
		return -1;
	}
	return 0;
}

static void set_blocking(int fd, int should_block)
{
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if(tcgetattr(fd, &tty) != 0)
	{
		printf("error %d from tggetattr", errno);
		return;
	}

	tty.c_cc[VMIN]  = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5;	    // 0.5 seconds read timeout

	if(tcsetattr(fd, TCSANOW, &tty) != 0)
		printf("error %d setting term attributes\n", errno);
}

static void serial_send(int fd, char b) {
	write(fd, &b, 1);
}


Screen::Screen() {
	const char* portname = "/dev/ttyUSB1";
	fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if(fd < 0) {
		printf("error %d opening %s: %s\n", errno, portname, strerror(errno));
		exit(1);
	}

	set_interface_attribs(fd, B115200, 0);
	set_blocking(fd, 0);
}

void Screen::swapBuffers() {
	// Send reset
	serial_send(fd, 0xFF);

	// Send data (oh my god why)
	for(int i = 0; i < 80; i++) {
		int x = i;
		int y = 0;
		int dy = 1;
		if(i >= 40) {
			x = 80-i-1;
			y = 27;
			dy = -1;
		}
		unsigned char r = 0;
		for(int j = 0; j < 7; j++)
			if(screen[x][y+j*dy])
				r |= 1 << j;
		serial_send(fd, r);
		r = 0;
		for(int j = 0; j < 7; j++)
			if(screen[x][y+(13-j)*dy]) r |= 1 << j;
		serial_send(fd, r);
	}
}

void Screen::setPixel(int p, int x, int y) {
	if(x < 0 || x >= width) return;
	if(y < 0 || y >= height) return;
	screen[x][y] = p != 0;
}

int Screen::getPixel(int x, int y) {
	if(x < 0 || x >= width) return 0;
	if(y < 0 || y >= height) return 0;
	return screen[x][y];
}

void Screen::drawRect(int p, int x, int y, int w, int h) {
	for(int xx = 0; xx < w; xx++) {
		setPixel(p, x+xx, y);
		setPixel(p, x+xx, y+h-1);
	}
	for(int yy = 0; yy < h; yy++) {
		setPixel(p, x, y+yy);
		setPixel(p, x+w-1, y+yy);
	}
}

void Screen::fillRect(int p, int x, int y, int w, int h) {
	for(int xx = 0; xx < w; xx++)
		for(int yy = 0; yy < h; yy++)
			setPixel(p, x+xx, y+yy);
}

void Screen::drawLine(int p, int x, int y, int x2, int y2) {

}

void Screen::drawCircle(int p, int x, int y, int r) {

}

void Screen::fillCircle(int p, int x, int y, int r) {

}

void Screen::drawOval(int p, int x, int y, int rx, int ry) {

}

void Screen::fillOval(int p, int x, int y, int rx, int ry) {

}

