#include "screen.h"
#include "keyboard.h"

void read_line(char *buffer, int max) {
    int i = 0;

    while (i < max - 1) {
        char c = get_key();
        if (!c) continue;

        if (c == '\n') {
            putc('\n');
            buffer[i] = 0;
            return;
        }

        putc(c);
        buffer[i++] = c;
    }

    buffer[i] = 0;
}

