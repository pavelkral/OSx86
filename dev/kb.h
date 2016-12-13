#ifndef KB_H
#define KB_H
#include "../sys/isr.h"
#include "../lib/terminal.h"

void keyboard_handler(struct regs *r);
void pause();

#endif
