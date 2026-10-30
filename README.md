# mochi-OS

A small hobby operating system kernel written in C with some x86 assembly. It boots through a custom 16-bit boot sector, switches to 32-bit protected mode, and starts a tiny text shell.

This is a learning project. It is not meant for real use.

## What's in the repo

| File | Purpose |
|------|---------|
| `boot.asm` | Boot sector. Loads the kernel from disk and switches to protected mode. |
| `linker.ld` | Linker script. Places the kernel at address `0x100000`. |
| `kernel.c` | Kernel entry point (`kmain`). Starts the shell. |
| `shell.c` / `shell.h` | The shell: reads a line, runs a command, repeats. |
| `keyboard.c` / `keyboard.h` | Keyboard input. |
| `screen.c` / `screen.h` | Text output to the screen. |
| `string.c` / `string.h` | Basic string helpers (`strcmp`, `strncmp`, and similar). |
| `input.c` | Input handling. |

The repo also contains prebuilt files (`boot.bin`, `kernel.o`, `kernel.bin`, `mochios.img`, and others). These are build output and can be regenerated from the source.

## Shell commands

Once the kernel is running, you get a `mochi>` prompt. Commands:

- `help`: list the commands
- `echo X`: print `X`
- `clear`: clear the screen (currently by printing spaces over it)

Anything else prints `Unknown command`.

## Building

TODO: Add the exact build steps and toolchain. The repo has no Makefile or build script yet.

What the source already tells us:

- The boot sector is assembled with NASM as a flat binary:
  ```bash
  nasm -f bin boot.asm -o boot.bin
  ```
- The kernel is linked with `linker.ld`, which expects the entry point `kmain` at `0x100000`.

## Running

TODO: Add how to run the image, for example in QEMU:

```bash
qemu-system-i386 -drive format=raw,file=mochios.img
```

Confirm the command and the image layout before using this.

## Status

Early development. Some parts of the boot process are still being worked out, so the image may not boot yet on every setup.

## License

MIT License. See [LICENSE](LICENSE).
