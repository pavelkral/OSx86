#include "error.h"

void bsod(int error){
	clear_screen(0x1f);
    ctr_print("**ERROR**",0x1f);
    printf("Needed to stop your computer.",0x1f);
    printf("\n\nCode:",0x1f);
	printInt(error,0x1f);
	for(;;);
}

void bsodmsg(string message){
	clear_screen(0x1f);
    ctr_print("**ERROR**",0x1f);
    printf("Needed to stop your computer.",0x1f);
    printf("\n\nCode: ",0x1f);
	printf(message,0x1f);
	for(;;);
}
