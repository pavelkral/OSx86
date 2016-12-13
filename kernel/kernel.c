#include "../sys/system.h"
#include "../dev/kb.h"
#include "../dev/vga.h"
#include "../lib/error.h"
#include "../lib/screen.h"
#include "../sys/gdt.h"
#include "../sys/idt.h"
#include "../sys/isr.h"
#include "../sys/irq.h"
#include "../sys/pit.h"
#include "../lib/terminal.h"

int init(){

    cls();
    gdt_init();
    println("gdt setuped.");
    idt_init();
    println("idt setuped.");
    isrs_init();
    println("isrs setuped.");
	irq_install_handler(0,timer_handler);
	irq_install_handler(1,keyboard_handler);
    println("irq handlers keyboard and timer setuped.");
    irq_init();
    println("irq setuped.");
    bootscreen();
	asm volatile("sti");
    terminal_init();
	return 0xDEADBABA;

}

