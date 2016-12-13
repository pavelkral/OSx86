#include "terminal.h"

string buffer = "\0                                  ";

u8int maincolor = 0x0f;
int cBlock = 0;
int cDirLength = 0;

void terminal_enterpressed(){
	printchar('\n');
    terminal();
}

void terminal_addchar(char c){
	concatc(buffer,c,buffer);
}

void terminal_backspace(){
	remchar(buffer,buffer);
}

int terminal_can_backspace(){
	if(strlen(buffer) > 0)
		return 1;
	return 0;
}

void terminal_init(){

	setcolor(maincolor);
    cBlock = getRoot(0);
	cDirLength = (getRootEntries(0)*32)/512;
    print(":-$");
	println("Commands:");
    println("help: Show commands list:");
    println("clear: Clears the screen.");
    println("who: Print kernel info.");
    println("setcolor 0x##: Set color of the screen.");
    println("ls: List of disk.");
    println("block: Show block length.");
    println("disk: Show disk info.");
    println("exit: Exit.");
}

void terminal(){
    terminal_find_command(buffer);
	buffer[0] = '\0';
	setcolor(maincolor);
	if(getY() == 0)
        print(":-$");
	else
        print("\n:-$");
}

void terminal_find_command(string command){

    if(strcmp(command,"who")){
		setcolor(0xf0);
        print("osx86 0.1");
		setcolor(0x0f);

    }
    else if(strcmp(command,"help")){
        println("Commands:");
        println("help: Show commands list:");
        println("clear: Clears the screen.");
        println("who: Print kernel info.");
        println("setcolor 0x##: Set color of the screen.");
        println("ls: list of disk.");
        println("block: Show block length.");
        println("disk: Show disk info.");
        println("exit: Exit.");
    }
    else if(strcmp(command,"clear")){
		cls();
    }
    else if(startswith(command,"setcolor")){
		int a = toHex(command[11]);
		int b = toHex(command[12]);
		if(startswith(command, "setcolor 0x") && strlen(command) == 13 && a != -1 && b != -1){
			maincolor = (a * 16)+b;
			setcolor(maincolor);
			colorRestOfScreen();
			print("color set to 0x");
			printchar(command[11]);
			printchar(command[12]);
		}else{
			setcolor(0x04);
			print("Please specify a color.");
		}

  //................................................

    }
    else if(strcmp(command,"ls")){
		listFiles(0,cBlock,cDirLength);
    }
    else if(startswith(command,"cd")){
		if(startswith(command, "cd ") && strlen(command) > strlen("cd ")){
			substring(command,command,3);
			if(isDir(0,cBlock,cDirLength,command)){
				int block = getFile(0,cBlock,cDirLength,command);
				if(block == getRoot(0)){
					cDirLength = (getRootEntries(0)*32)/512;
				}else{
					cDirLength = getDirLength(0,block);
				}
				cBlock = block;
			}else if(strcmp("\\",command)){
				cDirLength = (getRootEntries(0)*32)/512;
				cBlock = getRoot(0);
			}else{
				setcolor(0x04);
				print("\"");
				print(command);
				print("\" is not a directory!");
			}
		}else{
			setcolor(0x04);
			print("Please specify a directory.");
		}
    }
    else if(strcmp(command,"block")){

		printnum(getDirLength(0,cBlock));

    }
    else if(strcmp(command,"disk")){
		println("DISK 0:");
		println("  PARTITION 0:");
		print("    LOCATION: ");
		printhex(getFirstPart(0));
		print("\n    ROOT LOCATION: ");
		printhex(getRoot(0));
		print("\n    SECTORS PER CLUSTER: ");
		printhex(getClusterSize(0));
		print("\n    ROOT ENTRIES: ");
		printhex(getRootEntries(0));

     //....................................................

    }
    else if(strcmp(command,"exit")){
        print("Stopping the CPU.\n");
        asm volatile("hlt");

    }
    else{
		int bg = maincolor/16;
		if(bg == 0x4)
			setcolor((bg*16)+0xf);
		else
			setcolor((bg*16)+0x4);
        print("Command not found");
		print(command);
		print(".");
	}
}
