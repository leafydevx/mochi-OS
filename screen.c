// screen.c
#include "screen.h"

volatile char *video = (volatile char *)0xB8000;
int cursor = 0;

void putc(char c) {
    video[cursor * 2] = c;
    video[cursor * 2 + 1] = 0x0F;
    cursor++;
}

void puts(const char *s) {
    while (*s) {
        putc(*s++);
    }
}

