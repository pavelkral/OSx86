#qemu-system-i386 -kernel bin/boot/osx86.bin
qemu-system-x86_64 -boot d -cdrom osx86.iso -m 512 -hda hdd.img
