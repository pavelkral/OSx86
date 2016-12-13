#ifndef FAT_H
#define FAT_H

#include "../sys/system.h"
#include "../lib/screen.h"
#include "../dev/kb.h"

void listFiles(int disk, int len, int addr);
int getRoot(int disk);
int getFirstPart(int disk);
int isDir(int disk, int addr, int len, string name);
int getClusterSize(int disk);
int getRootEntries(int disk);
int getFile(int disk, int addr, int len, string name);
int getDirLength(int disk, int addr);

#endif
