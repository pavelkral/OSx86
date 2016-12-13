#ifndef ISR_H
#define ISR_H

#include "../lib/screen.h"
#include "idt.h"
#include "../lib/error.h"

struct regs{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

void isrs_init();

void fault_handler(struct regs *r);

#endif
