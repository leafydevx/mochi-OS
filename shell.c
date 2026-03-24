#include "screen.h"
#include "keyboard.h"
#include "string.h"
#include "shell.h"

#define SHELL_INPUT_MAX 128

static char input_buffer[SHELL_INPUT_MAX];

static void shell_print_prompt() {
    puts("mochi> ");
}

static void shell_read_line() {
    int i = 0;

    while (i < SHELL_INPUT_MAX - 1) {
        char c = get_key();
        if (!c) continue;

        // handle backspace
        if (c == '\b') {
            if (i > 0) {
                i--;
                // move cursor back and erase char visually
                putc('\b');
                putc(' ');
                putc('\b');
            }
            continue;
        }

        if (c == '\n') {
            putc('\n');
            break;
        }

        putc(c);
        input_buffer[i++] = c;
    }

    input_buffer[i] = 0;
}

static void shell_cmd_help() {
    puts("Commands:\n");
    puts("  help   - show this help\n");
    puts("  echo X - print X\n");
    puts("  clear  - clear screen\n");
}

static void shell_cmd_clear() {
    // naive clear: print spaces over whole screen
    for (int i = 0; i < 80 * 25; i++) {
        putc(' ');
    }
}

static void shell_execute(const char *cmd) {
    if (cmd[0] == 0)
        return;

    if (strcmp(cmd, "help") == 0) {
        shell_cmd_help();
    }
    else if (strncmp(cmd, "echo ", 5) == 0) {
        puts(cmd + 5);
        putc('\n');
    }
    else if (strcmp(cmd, "clear") == 0) {
        shell_cmd_clear();
    }
    else {
        puts("Unknown command: ");
        puts(cmd);
        putc('\n');
    }
}

void shell_init() {
    puts("Mochi Shell v0.2\n");
}

void shell_run() {
    while (1) {
        shell_print_prompt();
        shell_read_line();
        shell_execute(input_buffer);
    }
}

