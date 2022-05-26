#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* KERNEL.C */
extern void outb(int port, int data);
extern int inb(int port);
extern void video_mode();

/* SCREEN.C */
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define DEFAULT_COLOR 0x02
#define VIDEO_START 0xb8000

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GRAY = 7,
	VGA_COLOR_DARK_GRAY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_YELLOW = 14,
	VGA_COLOR_WHITE = 15
};

void update_cursor();
void clr_screen();
int terminal_print(const char* str);
void cursor_enable(int cursor_start, int cursor_end);


#endif
