#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

void fb_write_cell(unsigned int, char, unsigned char, unsigned char);
void clear();
void print(char*);
void println(char*);
void write(int);
void outb(unsigned short, unsigned char);
unsigned char inb(unsigned short);
void fb_move_cursor(unsigned short);
unsigned char read_scan_code(void);
#endif