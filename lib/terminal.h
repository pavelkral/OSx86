#ifndef SHELL_H
#define SHELL_H
#define MAX_COMMANDS 100

#include "../lib/screen.h"
#include "../dev/kb.h"
#include "../fs/fat.h"

void terminal_init();
void terminal();
void terminal_addchar(char c);
void terminal_enterpressed();
void terminal_backspace();
void terminal_find_command(string command);
int terminal_can_backspace();

#endif
