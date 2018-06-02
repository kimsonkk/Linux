#include <time.h>
#include <stdbool.h>
void option(int argc, char* argv[]);
void optcheck();
void cpfile(char* src,char* Target);
void printh();
void printinfo(char* fname, struct stat statbuf);
char* timeTostr(struct tm *t);
void cpdir(char* src, char* Target);
void cpdirps(char* src, char* Target, int pccount);
