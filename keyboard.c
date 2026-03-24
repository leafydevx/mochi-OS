#include "keyboard.h"
#include "screen.h"

unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

char get_key() {
    unsigned char scancode;

    // Wait for a key press
    while ((scancode = inb(0x60)) == 0);

    // Very basic US keyboard map
    static char keymap[128] = {
        0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
        'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
        'z','x','c','v','b','n','m',',','.','/', 0,'*', 0,' ',
    };

    if (scancode > 127) return 0; // ignore key releases

    return keymap[scancode];
}

