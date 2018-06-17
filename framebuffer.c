#include "framebuffer.h"

#define FB_BLACK 0
#define FB_GREEN 2
#define FB_RED 4
#define FB_LIGHT_GREY 7
#define FB_DARK_GREY 8
#define FB_WHITE 15

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

unsigned int position = 0;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    char *fb = (char*) 0x000B8000;
    fb[i * 2] = c;
    fb[i * 2 + 1] = ((fg & 0x0F) << 4 | (bg & 0x0F));
}

void clear() {
    for(int i = 0; i < 2000; i ++) {
        fb_write_cell(i, 0, FB_BLACK, FB_LIGHT_GREY);
    }
}

void print(char* string) {
    for (int i = 0; string[i] != 0; i ++) {
        fb_write_cell(position, *(string + i), FB_BLACK, FB_LIGHT_GREY);
        position ++;
    }
    fb_move_cursor(position);
}

void println(char* string) {
    for (int i = 0; string[i] != 0; i ++) {
        fb_write_cell(position, *(string + i), FB_BLACK, FB_LIGHT_GREY);
        position ++;
    }
    unsigned int newline_pos = 0;
    while (newline_pos < position) {
        newline_pos += 80;
    }
    position = newline_pos;
    fb_move_cursor(position);
}

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

unsigned char read_scan_code(void) {
    return inb(0x60);
}

void write(int val) {
    if (val < 10) {
        fb_write_cell(position, val + 48, FB_BLACK, FB_LIGHT_GREY);
        position ++;
    } else if (val < 100) {
        fb_write_cell(position, val / 10 + 48, FB_BLACK, FB_LIGHT_GREY);
        position ++;
        fb_write_cell(position, val % 10 + 48, FB_BLACK, FB_LIGHT_GREY);
        position ++;
    } else if (val < 1000) {
        fb_write_cell(position, val / 100 + 48, FB_BLACK, FB_LIGHT_GREY);
        position ++;
        fb_write_cell(position, val /10 % 10 + 48, FB_BLACK, FB_LIGHT_GREY);
        position ++;
        fb_write_cell(position, val % 10 + 48, FB_BLACK, FB_LIGHT_GREY);
        position ++;
    }
    fb_move_cursor(position);
}