# Keyboard Hook Program
This program sets up a low-level keyboard hook on Windows to capture and display key press events. It uses the Windows API to intercept keyboard input and print information about the keys pressed to the console.

## Requirements
O/S: Windows
Compiler: A compatible C compiler i.e. gcc or clang

## Compilation
To compile and run the program in your terminal, head to the directory where the Makefile is held and type:
```bash
make run
```
This will run the program and display any keys that are pressed in the console window.

## Cleanup
Before recompiling, it is suggested that you remove all "old" compiled files. This can be done simply through the following command:
```bash
make clean
```