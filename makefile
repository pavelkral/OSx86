COMPILER = gcc
LINKER = ld
ASSEMBLER = nasm
CFLAGS = -m32 -c -ffreestanding -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wno-unused-parameter
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T kernel/linker.ld
EMULATOR = qemu-system-i386
EMULATOR_FLAGS = -kernel

SRCS = kernel/kernel.asm kernel/kernel.c sys/idt.c sys/isr.c sys/system.c sys/pit.c sys/gdt.c sys/irq.c dev/kb.c dev/vga.c fs/fat.c lib/screen.c lib/terminal.c lib/error.c sys/irq.c  
OBJS = obj/kerasm.o obj/kerc.o obj/fat.o obj/terminal.o obj/kb.o obj/pit.o obj/irq.o obj/isr.o obj/idt.o obj/gdt.o obj/error.o obj/vga.o obj/system.o obj/screen.o 
OUTPUT = bin/boot/osx86.bin

run: all
	$(EMULATOR) $(EMULATOR_FLAGS) $(OUTPUT)

all:$(OBJS)
	#mkdir bin/boot/ -p
	$(LINKER) $(LDFLAGS) -o $(OUTPUT) $(OBJS)

obj/kerasm.o:kernel/kernel.asm
	$(ASSEMBLER) $(ASFLAGS) -o obj/kerasm.o kernel/kernel.asm
	
obj/kerc.o:kernel/kernel.c
	$(COMPILER) $(CFLAGS) kernel/kernel.c -o obj/kerc.o
	
obj/system.o:sys/system.c
	$(COMPILER) $(CFLAGS) sys/system.c -o obj/system.o
	
obj/idt.o:sys/idt.c
	$(COMPILER) $(CFLAGS) sys/idt.c -o obj/idt.o
	
obj/kb.o:dev/kb.c
	$(COMPILER) $(CFLAGS) dev/kb.c -o obj/kb.o

obj/isr.o:sys/isr.c
	$(COMPILER) $(CFLAGS) sys/isr.c -o obj/isr.o
	
obj/irq.o:sys/irq.c
	$(COMPILER) $(CFLAGS) sys/irq.c -o obj/irq.o
	
obj/screen.o:lib/screen.c
	$(COMPILER) $(CFLAGS) lib/screen.c -o obj/screen.o

obj/gdt.o:sys/gdt.c
	$(COMPILER) $(CFLAGS) sys/gdt.c -o obj/gdt.o

obj/error.o:lib/error.c
	$(COMPILER) $(CFLAGS) lib/error.c -o obj/error.o
	
obj/pit.o:sys/pit.c
	$(COMPILER) $(CFLAGS) sys/pit.c -o obj/pit.o
	
obj/vga.o:dev/vga.c
	$(COMPILER) $(CFLAGS) dev/vga.c -o obj/vga.o
	
obj/fat.o:fs/fat.c
	$(COMPILER) $(CFLAGS) fs/fat.c -o obj/fat.o
	
obj/terminal.o:lib/terminal.c
	$(COMPILER) $(CFLAGS) lib/terminal.c -o obj/terminal.o

build:all
	#Activate the install xorr if you do not have it already installed
	#sudo apt-get install xorriso
	#rm bin/boot/grub/ -r -f
	#mkdir bin/boot/grub/
	#echo set default=0 >> bin/boot/grub/grub.cfg
	#echo set timeout=0 >> bin/boot/grub/grub.cfg
	#echo menuentry "Core Os" { >> bin/boot/grub/grub.cfg
	#echo         set root='(hd96)' >> iknow/boot/grub/grub.cfg
	#echo         multiboot /boot/kernel.bin >> iknow/boot/grub/grub.cfg
	#echo } >> bin/boot/grub/grub.cfg

	grub-mkrescue -o osx86.iso bin/
	
clear:
	rm -f obj/*
	rm -r -f bin/boot/osx86.bin
	
